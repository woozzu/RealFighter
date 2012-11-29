#include "platform/android/jni/JniHelper.h"
#include "SensorHelper.h"

#ifdef __cplusplus
extern "C" {
#endif

using namespace ju6sigan;

/**
 * This is the implementation of SensorHelper's native method.
 * 
 * @param aX (in) x coordinate of acceleration
 * @param aY (in) y coordinate of acceleration
 * @param aZ (in) z coordinate of acceleration
 * @param qX (in) x component of rotation quaternion
 * @param qY (in) y component of rotation quaternion
 * @param qZ (in) z component of rotation quaternion
 * @param qW (in) w component of rotation quaternion
 */
void Java_kr_ac_yonsei_cs_ju6sigan_SensorHelper_onUpdate(
		JNIEnv* env, jobject thisObj,
		jfloat aX, jfloat aY, jfloat aZ,
		jfloat qX, jfloat qY, jfloat qZ, jfloat qW)
{
	// Send this data to SensorHelper class in cocos2d-x
	SensorHelper* pHelper = SensorHelper::getInstance();
	pHelper->onUpdate(aX, aY, aZ, qX, qY, qZ, qW);
}

#ifdef __cplusplus
}
#endif