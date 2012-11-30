#include "platform/android/jni/JniHelper.h"
#include "MotionManager.h"

#ifdef __cplusplus
extern "C" {
#endif

using namespace ju6sigan;

/**
 * These are the implementations of android MotionManager's native method.
 */

void Java_kr_ac_yonsei_cs_ju6sigan_MotionManager_loadData(JNIEnv* env, jobject thisObj)
{
	MotionManager *mm = MotionManager::getInstance();
	mm->loadData();
}

void Java_kr_ac_yonsei_cs_ju6sigan_MotionManager_enableSensor(JNIEnv* env, jobject thisObj)
{
	MotionManager *mm = MotionManager::getInstance();
	mm->enableSensor();
}

void Java_kr_ac_yonsei_cs_ju6sigan_MotionManager_disableSensor(JNIEnv* env, jobject thisObj)
{
	MotionManager *mm = MotionManager::getInstance();
	mm->disableSensor();
}

void Java_kr_ac_yonsei_cs_ju6sigan_MotionManager_startCapture(JNIEnv* env, jobject thisObj)
{
	MotionManager *mm = MotionManager::getInstance();
	mm->startCapture();
}

jint Java_kr_ac_yonsei_cs_ju6sigan_MotionManager_stopCapture(JNIEnv* env, jobject thisObj)
{
	MotionManager *mm = MotionManager::getInstance();
	return (jint)mm->stopCapture();
}

#ifdef __cplusplus
}
#endif