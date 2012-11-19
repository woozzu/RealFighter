#include "platform/android/jni/JniHelper.h"
#include "SensorHelper.h"

#ifdef __cplusplus
extern "C" {
#endif

using namespace ju6sigan;

void Java_kr_ac_yonsei_cs_ju6sigan_SensorHelper_onUpdate(
		JNIEnv* env, jobject thisObj,
		jfloat aX, jfloat aY, jfloat aZ,
		jfloat qX, jfloat qY, jfloat qZ, jfloat qW)
{
	SensorHelper* pHelper = SensorHelper::getInstance();
	pHelper->onUpdate(aX, aY, aZ, qX, qY, qZ, qW);
}

#ifdef __cplusplus
}
#endif