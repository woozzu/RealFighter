#ifndef _JU6SIGAN_MOTION_MANAGER_H_
#define _JU6SIGAN_MOTION_MANAGER_H_

#include "Common.h"
#include "SensorHelper.h"
#include "MotionRecognizer.h"

namespace ju6sigan
{
	/**
	 * User class of motion recognizer module
	 * User can take advantage of the module by using this class.
	 */
	class MotionManager
	{
	public:
		static MotionManager* getInstance();
		~MotionManager() {}
		
		/**
		 * Load data files to initializing motion recognizer.
		 * The files should be named 'motion_e_N.dat', 'motion_t_N.dat' (N is integer >= 0),
		 * and be placed in your application's resource directory.
		 * 
		 * You must call this at first.
		 */
		void loadData();
		
		/**
		 * Device starts get sensor data.
		 */
		void enableSensor();
		
		/**
		 * Device stops getting sensor data.
		 */
		void disableSensor();
		
		/**
		 * Start capture sensor data.
		 */
		void startCapture();
		
		/**
		 * Stop capturing sensor data and recognize captured sensor data.
		 * @return A type of motion recognized
		 */
		Motion stopCapture();
		
	private:
		MotionManager();
		
		SensorHelper *m_pSensorHelper;
		MotionRecognizer m_motionRecognizer;
		static MotionManager *m_pInstance;
	};
}

#endif