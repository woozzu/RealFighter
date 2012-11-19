package kr.ac.yonsei.cs.ju6sigan;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.util.FloatMath;

public class SensorHelper {
	
	private static SensorHelper instance;
	private static SensorManager sensorManager;
	private static boolean isEnabled = false;
	
	public static SensorHelper getInstance(Context context) {
		if (instance == null)
			instance = new SensorHelper(context);
		return instance;
	}
	
	private SensorHelper(Context context) {
		sensorManager = (SensorManager) context.getSystemService(Context.SENSOR_SERVICE);
	}

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
	
	public static void disable() {
		if (instance == null || !isEnabled)
			return;
		
		sensorManager.unregisterListener(instance.listener);
		isEnabled = false;
	}
	
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
				qW = FloatMath.sqrt(1 - (float) (Math.pow(qX, 2) + Math.pow(qY, 2) + Math.pow(qZ, 2)));
				
				rotation = true;
				rotTimestamp = event.timestamp;
			}
			
			if (acceleration && rotation
					&& accelTimestamp == rotTimestamp) {
				onUpdate(accelX, accelY, accelZ, qX, qY, qZ, qW);
				
				acceleration = false;
				rotation = false;
			}
		}
		
	};
	
}
