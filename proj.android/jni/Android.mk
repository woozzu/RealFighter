LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/motion/SensorHelper.cpp \
                   ../../Classes/motion/Java_kr_ac_yonsei_cs_ju6sigan_SensorHelper.cpp \
                   ../../Classes/motion/MotionRecognizer.cpp \
                   ../../Classes/motion/MotionManager.cpp \
                   ../../Classes/motion/hmm/hmm.cpp \
                   ../../Classes/motion/hmm/logprobs.cpp \
                   ../../Classes/motion/hmm/tables.cpp
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
