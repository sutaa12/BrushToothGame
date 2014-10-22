//
//  GameMainScene.h
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/17.
//
//

#ifndef __ToothBrushGame__GameMainScene__
#define __ToothBrushGame__GameMainScene__
#include "cocos2d.h"

using namespace cocos2d;

class ToothManager;
class EnemyManager;
class PlaqueManager;
class HitChecker;
class UIManager;
class LifeBar;
class EffectManager;
class CountDown;
class ToothPowder;

class GameMainScene : public cocos2d::Layer
{
public:
    GameMainScene(){};
    ~GameMainScene();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void update(float fTime);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameMainScene);

    void createCountDown(float fTime);
    
    typedef enum
    {
        SWIPE_DIRECTION_NONE = 0,
        SWIPE_DIRECTION_UP,
        SWIPE_DIRECTION_DOWN,
        SWIPE_DIRECTION_LEFT,
        SWIPE_DIRECTION_RIGHT,
        SWIPE_DIRECTION_MAX,
    }SWIPE_DIRECTION;
    
private:
    Point m_touchPos;
    Point m_oldTouchPos;
    SWIPE_DIRECTION m_swipeDirection;
    SWIPE_DIRECTION m_oldSwipeDirection;
    EventListenerTouchOneByOne* m_pTouchEventOneByOne;
    
    static const int SWIPE_PERMISSION_DISTANCE = (3);
    
    ToothManager* m_pToothManager;
    EnemyManager* m_pEnemyManager;
    PlaqueManager* m_pPlaqueManager;
    HitChecker* m_pHitChecker;
    UIManager* m_pUIManager;
    EffectManager* m_EffectManager;
    
    Sprite* m_pBubbleSprite;
    Vec2 m_bubblePos;
    
    int m_nTimer;
    
    bool m_bMove;
    
    bool m_bHit;
    
    void setResultScene(bool bGameOverFlag = false);
    
    bool onTouchBegin(Touch* pTouch,Event* pEvent);
    void onTouchMoved(Touch* pTouch,Event* pEvent);
    void onTouchCancelled(Touch* pTouch,Event* pEvent);
    void onTouchEnded(Touch* pTouch,Event* pEvent);
    
    SWIPE_DIRECTION calcSwipeDirection(float fAngle);

    Layer* m_pPauseLayer;
    Layer* m_pCountDown;
    bool m_bCountDownEnd;
    ToothPowder* m_pToothPowder;
};
#endif /* defined(__ToothBrushGame__GameMainScene__) */
