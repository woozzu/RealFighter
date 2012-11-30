#include "MotionManager.h"

namespace ju6sigan
{
	MotionManager *MotionManager::m_pInstance;
	
	MotionManager* MotionManager::getInstance()
	{
		if (m_pInstance == NULL)
			m_pInstance = new MotionManager();
		return m_pInstance;
	}
	
	MotionManager::MotionManager()
	{
		m_pSensorHelper = SensorHelper::getInstance();
	}
	
	void MotionManager::enableSensor()
	{
		m_pSensorHelper->enable();
	}
	
	void MotionManager::disableSensor()
	{
		m_pSensorHelper->disable();
	}
	
	void MotionManager::startCapture()
	{
		m_pSensorHelper->start();
	}
	
	Motion MotionManager::stopCapture()
	{
		// Stop capturing sensor data, and get captured data.
		vector<kmVecPair> data;
		m_pSensorHelper->stop(data);
		
		// Recognize and return
		return m_motionRecognizer.recognize(data);
	}
	
	void MotionManager::loadData()
	{
		m_motionRecognizer.load();
	}
}