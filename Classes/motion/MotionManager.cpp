#include "MotionManager.h"

namespace ju6sigan
{
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
		vector<kmVecPair> data;
		m_pSensorHelper->stop(data);
		return m_motionRecognizer.recognize(data);
	}
	
	void MotionManager::loadData()
	{
		m_motionRecognizer.load();
	}
}