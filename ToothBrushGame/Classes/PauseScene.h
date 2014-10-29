//
//  PauseScene.h
//  ToothBrushGame
//
//  Created by 丸山 潤 on 2014/10/20.
//
//

#ifndef __ToothBrushGame__PauseScene__
#define __ToothBrushGame__PauseScene__

#include "cocos2d.h"

using namespace cocos2d;

class PauseScene : public cocos2d::Layer
{
public:
    PauseScene(){};
    ~PauseScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    void update(float fTime);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(PauseScene);

    static cocos2d::Layer* createLayer(void);

private:
    Point m_touchPos;
    EventListenerTouchOneByOne* m_pTouchEventOneByOne;
    bool m_bConfig;

    void returnGame(void);
    void retryGame(void);
    void returnTitle(void);
    void openConfig(void);

    Sprite* m_pMaskSprite;
    Sprite* m_pRetryGameSprite;
    Sprite* m_pReturnGameSprite;
    Sprite* m_pReturnTitleSprite;
    Sprite* m_pConfigSprite;

    bool onTouchBegin(Touch* pTouch,Event* pEvent);
    void onTouchMoved(Touch* pTouch,Event* pEvent);
    void onTouchCancelled(Touch* pTouch,Event* pEvent);
    void onTouchEnded(Touch* pTouch,Event* pEvent);
};


#endif /* defined(__ToothBrushGame__PauseScene__) */
