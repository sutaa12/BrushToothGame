//
//  TitleScene.h
//  ToothBrushGame
//
//  Created by 鈴木愛忠 on 2014/10/20.
//
//

#ifndef __ToothBrushGame__TitleScene__
#define __ToothBrushGame__TitleScene__

#include "cocos2d.h"
#include "common.h"
#include "NendModule.h"
using namespace cocos2d;

class TitleScene : public cocos2d::Layer
{
public:
    TitleScene(){};
    ~TitleScene(){};
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void update(float fTime);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(TitleScene);
    
    void menuButtonAchievements(void);
    void menuButtonGame(void);
    void menuButtonHelp(void);

    
private:
    Point m_touchPos;
    Point m_oldTouchPos;
    EventListenerTouchOneByOne* m_pTouchEventOneByOne;
    
    Sprite* m_pTitleLogo;
    Sprite* m_pTitleBack;
    Sprite* m_pTitleCharacter;
    Sprite* m_pButton0;
    Sprite* m_pHelpWindow;
    Sprite* m_pHelpButton;
    
    bool m_bHelpMode;
    
    bool onTouchBegin(Touch* pTouch,Event* pEvent);
    void onTouchMoved(Touch* pTouch,Event* pEvent);
    void onTouchCancelled(Touch* pTouch,Event* pEvent);
    void onTouchEnded(Touch* pTouch,Event* pEvent);

};
#endif /* defined(__ToothBrushGame__TitleScene__) */
