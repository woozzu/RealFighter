#ifndef _SENSOR_HELPER_H_
#define _SENSOR_HELPER_H_

#include "Common.h"

namespace ju6sigan
{
	class SensorHelper
	{
	public:
		void enable();
		void disable();
		void start();
		void stop(vector<kmVecPair> &data);
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