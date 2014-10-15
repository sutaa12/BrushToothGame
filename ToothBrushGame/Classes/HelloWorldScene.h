#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class ToothManager;
class EnemyManager;
class PlaqueManager;

class HelloWorld : public cocos2d::Layer
{
public:
    HelloWorld(){};
    ~HelloWorld(){};
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void update(float fTime);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
private:
    typedef enum
    {
        SWIPE_DIRECTION_NONE = 0,
        SWIPE_DIRECTION_UP,
        SWIPE_DIRECTION_DOWN,
        SWIPE_DIRECTION_LEFT,
        SWIPE_DIRECTION_RIGHT,
        SWIPE_DIRECTION_MAX,
    }SWIPE_DIRECTION;

    Point m_touchPos;
    Point m_oldTouchPos;
    SWIPE_DIRECTION m_swipeDirection;
    SWIPE_DIRECTION m_oldSwipeDirection;
    EventListenerTouchOneByOne* m_pTouchEventOneByOne;

    static const int SWIPE_PERMISSION_DISTANCE = (3);
    
    ToothManager* m_pToothManager;
    EnemyManager* m_pEnemyManager;
    PlaqueManager* m_pPlaqueManager;
    
    Sprite* m_pBubbleSprite;
    Vec2 m_bubblePos;
    
    Sprite* m_pEnemySprite;
    Sprite* m_pPlaqueSprite;
    Sprite* m_pBossSprite;
    
    bool m_bEnemyDie;
    bool m_bPlaqueDie;
    bool m_bMove;
    bool m_bBossDisp;
    
    bool m_bHit;
    
    bool onTouchBegin(Touch* pTouch,Event* pEvent);
    void onTouchMoved(Touch* pTouch,Event* pEvent);
    void onTouchCancelled(Touch* pTouch,Event* pEvent);
    void onTouchEnded(Touch* pTouch,Event* pEvent);

    SWIPE_DIRECTION calcSwipeDirection(float fAngle);
};
#endif // __HELLOWORLD_SCENE_H__
