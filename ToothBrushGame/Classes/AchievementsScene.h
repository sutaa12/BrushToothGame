//
//  AchievementsScene.h
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/23.
//
//

#ifndef __ToothBrushGame__AchievementsScene__
#define __ToothBrushGame__AchievementsScene__

#include <cocos2d.h>
#include <common.h>
#include "NendInterstitialModule.h"
#include "NendIconModule.h"
#include "NendModule.h"

using namespace cocos2d;
class AchievementList;
class GameStatusList;

class AchievementsScene : public cocos2d::Layer
{
public:
    AchievementsScene(){};
    ~AchievementsScene();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void update(float fTime);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(AchievementsScene);
    
    void ButtonTitle(void);
    
    void setNextScene(SCENE_LIST sceneList);
    
private:
    Point m_touchPos;
    Point m_oldTouchPos;
    EventListenerTouchOneByOne* m_pTouchEventOneByOne;
    
    AchievementList* m_pAchievementList;

    bool onTouchBegin(Touch* pTouch,Event* pEvent);
    void onTouchMoved(Touch* pTouch,Event* pEvent);
    void onTouchCancelled(Touch* pTouch,Event* pEvent);
    void onTouchEnded(Touch* pTouch,Event* pEvent);
    
};
#endif /* defined(__ToothBrushGame__AchievementsScene__) */
