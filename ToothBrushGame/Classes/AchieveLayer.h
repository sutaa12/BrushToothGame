//
//  AchieveLayer.h
//  ToothBrushGame
//
//  Created by 鈴木愛忠 on 2014/10/27.
//
//

#ifndef __ToothBrushGame__AchieveLayer__
#define __ToothBrushGame__AchieveLayer__

#include <cocos2d.h>
#include "common.h"
#include "AchievementDataBase.h"

using namespace cocos2d;

class AchieveLayer : public cocos2d::Layer
{
public:
    AchieveLayer(){};
    ~AchieveLayer(){};
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void update(float fTime);
    
    // implement the "static create()" method manually
    CREATE_FUNC(AchieveLayer);
    
    void setDispAchieveLayer(int nAchieveNum);
    
    void ButtonTitle(void);
    
    void setNextScene(SCENE_LIST sceneList);
    
private:
    Point m_touchPos;
    Point m_oldTouchPos;
    EventListenerTouchOneByOne* m_pTouchEventOneByOne;
    Sprite* m_pAchieve;
    LabelTTF* m_pTitle;
    LabelTTF* m_pMessage;
    
    bool onTouchBegin(Touch* pTouch,Event* pEvent);
    void onTouchMoved(Touch* pTouch,Event* pEvent);
    void onTouchCancelled(Touch* pTouch,Event* pEvent);
    void onTouchEnded(Touch* pTouch,Event* pEvent);
    const int ACHIEVE_LAYER_POS_WIDTH = 300;
};
#endif /* defined(__ToothBrushGame__AchieveLayer__) */
