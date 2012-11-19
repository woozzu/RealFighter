#ifndef _MOTION_MANAGER_H_
#define _MOTION_MANAGER_H_

#include "Common.h"
#include "SensorHelper.h"
#include "MotionRecognizer.h"

namespace ju6sigan
{
	class MotionManager
	{
	public:
		MotionManager();
		~MotionManager() {}
		
		void loadData();
		void enableSensor();
		void disableSensor();
		void startCapture();
		Motion stopCapture();
		
	private:
		SensorHelper *m_pSensorHelper;
		MotionRecognizer m_motionRecognizer;
	};
}

#endif