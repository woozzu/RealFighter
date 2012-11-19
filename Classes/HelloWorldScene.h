#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "motion/SensorHelper.h"
#include "motion/MotionRecognizer.h"

using namespace ju6sigan;

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent* event);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent* event);
    
private:
    SensorHelper* sensorHelper;
    MotionRecognizer motionRecognizer;
};

#endif // __HELLOWORLD_SCENE_H__
