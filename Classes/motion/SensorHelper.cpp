#include "SensorHelper.h"
#include "platform/android/jni/JniHelper.h"

// Class name of android's helper module
#define CLASS_NAME "kr/ac/yonsei/cs/ju6sigan/SensorHelper"

namespace ju6sigan
{
	SensorHelper *SensorHelper::m_pInstance;
	
	SensorHelper* SensorHelper::getInstance()
	{
		if (m_pInstance == NULL)
			m_pInstance = new SensorHelper();
		return m_pInstance;
	}
	
	void SensorHelper::enable()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		// Under android platform, call java method through jni helper.
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "enable", "()V")) {
			t.env->CallStaticVoidMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
#endif
		
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#endif
	}
	
	void SensorHelper::disable()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		// Under android platform, call java method through jni helper.
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "disable", "()V")) {
			t.env->CallStaticVoidMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
#endif
		
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#endif
	}
	
	void SensorHelper::onUpdate(float aX, float aY, float aZ, float qX, float qY, float qZ, float qW)
	{
		// If capturing was started, save the data in buffer.
		if (m_isStarted) {
			kmVecPair vecPair = {{aX, aY, aZ}, {qX, qY, qZ, qW}};
			m_data.push_back(vecPair);
		}
	}
	
	void SensorHelper::start()
	{
		m_data.clear();
		m_isStarted = true;
	}
	
	void SensorHelper::stop(vector<kmVecPair> &data)
	{
		m_isStarted = false;
		
		vector<kmVecPair>::iterator iter;
		for (iter = m_data.begin(); iter != m_data.end(); iter++)
			data.push_back(*iter);
	}
}