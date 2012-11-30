package kr.ac.yonsei.cs.ju6sigan;

public class MotionManager {
	
	public static final int MOTION_HORIZONTAL = 0;
	public static final int MOTION_DIAGONAL = 1;
	public static final int MOTION_CIRCLE = 2;
	public static final int MOTION_UNKNOWN = 4;

	/**
	 * Enable device's sensor.
	 */
	public native void enableSensor();
	
	/**
	 * Disable device's sensor.
	 */
	public native void disableSensor();
	
	/**
	 * Start capturing sensor data.
	 */
	public native void startCapture();
	
	/**
	 * Stop capturing sensor data and recognize.
	 * Types of motion are defined constants.
	 * @return A type of motion
	 */
	public native int stopCapture();
	
}
