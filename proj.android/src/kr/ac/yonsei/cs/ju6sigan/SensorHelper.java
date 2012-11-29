package kr.ac.yonsei.cs.ju6sigan;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.util.FloatMath;

/**
 * Helper class that cocos2d-x accesses sensor data through.
 * Before cocos2d-x gets the data, SensorHelper's instance should be created.
 * You should call SensorHelper.getInstance(this) in your app's main activity.
 */
public class SensorHelper {
	
	private static SensorHelper instance;
	private static SensorManager sensorManager;
	private static boolean isEnabled = false;
	
	/**
	 * As a singleton class, get the only one instance of this.
	 * If there is no instance, create the instance.
	 * @param context Android context instance
	 * @return An instance of this
	 */
	public static SensorHelper getInstance(Context context) {
		if (instance == null)
			instance = new SensorHelper(context);
		return instance;
	}
	
	private SensorHelper(Context context) {
		sensorManager = (SensorManager) context.getSystemService(Context.SENSOR_SERVICE);
	}

	/**
	 * Enable sensors, which are linear acceleration and rotation vector sensor.
	 * cocos2d-x should call this by jni interface before start capture.
	 */
	public static void enable() {
		if (instance == null || isEnabled)
			return;
		
		sensorManager.registerListener(instance.listener
				, sensorManager.getDefaultSensor(Sensor.TYPE_LINEAR_ACCELERATION)
				, SensorManager.SENSOR_DELAY_GAME);
		sensorManager.registerListener(instance.listener
				, sensorManager.getDefaultSensor(Sensor.TYPE_ROTATION_VECTOR)
				, SensorManager.SENSOR_DELAY_GAME);
		isEnabled = true;
	}
	
	/**
	 * Disable sensors.
	 * cocos2d-x can call this by jni interface.
	 */
	public static void disable() {
		if (instance == null || !isEnabled)
			return;
		
		sensorManager.unregisterListener(instance.listener);
		isEnabled = false;
	}
	
	/**
	 * Send sensor data to cocos2d-x.
	 * It is implemented in jni native function.
	 * See, Java_kr_ac_yonsei_cs_ju6sigan_SensorHelper.cpp
	 * @param aX x coordinate of acceleration
	 * @param aY y coordinate of acceleration
	 * @param aZ z coordinate of acceleration
	 * @param qX x component of rotation quaternion
	 * @param qY y component of rotation quaternion
	 * @param qZ z component of rotation quaternion
	 * @param qW w component of rotation quaternion
	 */
	private native void onUpdate(float aX, float aY, float aZ, float qX, float qY, float qZ, float qW);
	
	private SensorEventListener listener = new SensorEventListener() {
		
		private boolean acceleration = false;
		private boolean rotation = false;
		private long accelTimestamp = 0;
		private long rotTimestamp = 0;
		private float accelX, accelY, accelZ;
		private float qX, qY, qZ, qW;

		public void onAccuracyChanged(Sensor sensor, int accuracy) {
		}

		public void onSensorChanged(SensorEvent event) {
			// Copy two sensor data into buffer.
			if (event.sensor.getType() == Sensor.TYPE_LINEAR_ACCELERATION) {
				accelX = event.values[0];
				accelY = event.values[1];
				accelZ = event.values[2];
				
				acceleration = true;
				accelTimestamp = event.timestamp;
			} else if (event.sensor.getType() == Sensor.TYPE_ROTATION_VECTOR) {
				qX = event.values[0];
				qY = event.values[1];
				qZ = event.values[2];
				// w component is inferred
				qW = FloatMath.sqrt(1 - (float) (Math.pow(qX, 2) + Math.pow(qY, 2) + Math.pow(qZ, 2)));
				
				rotation = true;
				rotTimestamp = event.timestamp;
			}
			
			// If two sensor data were all collected, send them to cocos2d-x
			if (acceleration && rotation
					&& accelTimestamp == rotTimestamp) {
				onUpdate(accelX, accelY, accelZ, qX, qY, qZ, qW);
				
				acceleration = false;
				rotation = false;
			}
		}
		
	};
	
}
