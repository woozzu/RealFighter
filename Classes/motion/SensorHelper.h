#ifndef _JU6SIGAN_SENSOR_HELPER_H_
#define _JU6SIGAN_SENSOR_HELPER_H_

#include "Common.h"

namespace ju6sigan
{
	/**
	 * Helper class to utilize device's sensor and sensor data.
	 * It needs each platform's helper modules.
	 */
	class SensorHelper
	{
	public:
		/**
		 * Enable device's sensor.
		 */
		void enable();
		
		/**
		 * Disable device's sensor.
		 */
		void disable();
		
		/**
		 * Start capture sensor data.
		 * Sensor data is buffered before calling stop().
		 */
		void start();
		
		/**
		 * Stop capturing sensor data and get it.
		 * 
		 * @param data (out) Captured sensor data
		 */
		void stop(vector<kmVecPair> &data);
		
		/**
		 * Called by each platform's helper module.
		 * 
		 * @param aX (in) x coordinate of acceleration
		 * @param aY (in) y coordinate of acceleration
		 * @param aZ (in) z coordinate of acceleration
		 * @param qX (in) x component of rotation quaternion
		 * @param qY (in) y component of rotation quaternion
		 * @param qZ (in) z component of rotation quaternion
		 * @param qW (in) w component of rotation quaternion
		 */
		void onUpdate(float aX, float aY, float aZ, float qX, float qY, float qZ, float qW);
		
		~SensorHelper() { disable(); }
		
		static SensorHelper* getInstance();
		
	private:
		SensorHelper() { m_isStarted = false; }
		
		vector<kmVecPair> m_data;
		bool m_isStarted;
		static SensorHelper *m_pInstance;
	};
};

#endif