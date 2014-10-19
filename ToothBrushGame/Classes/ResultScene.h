//
//  ResultScene.h
//  ToothBrushGame
//
//  Created by 鈴木愛忠 on 2014/10/20.
//
//

#ifndef __ToothBrushGame__ResultScene__
#define __ToothBrushGame__ResultScene__
#include "cocos2d.h"

using namespace cocos2d;

class ResultScene : public cocos2d::Layer
{
public:
    ResultScene(){};
    ~ResultScene(){};
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void update(float fTime);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(ResultScene);
    
private:
    Point m_touchPos;
    Point m_oldTouchPos;
    EventListenerTouchOneByOne* m_pTouchEventOneByOne;
    
    bool onTouchBegin(Touch* pTouch,Event* pEvent);
    void onTouchMoved(Touch* pTouch,Event* pEvent);
    void onTouchCancelled(Touch* pTouch,Event* pEvent);
    void onTouchEnded(Touch* pTouch,Event* pEvent);
    
};
#endif /* defined(__ToothBrushGame__ResultScene__) */
