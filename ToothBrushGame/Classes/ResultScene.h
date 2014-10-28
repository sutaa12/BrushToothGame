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
#include "common.h"

using namespace cocos2d;

class RankManager;

class ResultScene : public cocos2d::Layer
{
public:
    ResultScene(){};
    ~ResultScene(){};
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(bool bGameOverFlag = false,int nTimeBornus = 0);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void update(float fTime);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(ResultScene);
    
    void initGameOver(void);
    void initGameClear(void);
    
    void updateGameOver(void);
    void updateGameClear(void);
    
    void ButtonRetry(void);
    void ButtonTitle(void);
    
    void setNextScene(SCENE_LIST sceneList);
    
private:
    Point m_touchPos;
    Point m_oldTouchPos;
    EventListenerTouchOneByOne* m_pTouchEventOneByOne;
    //残り時間ボーナス
    static int m_nTimeBornus;
    static bool m_bGameOverFlag;
    //クリア時のランク表示
    RankManager* m_pRankManager;
    
    //各分岐に使用するアップデート用関数ポインタ
    void (ResultScene::*m_pFuncUpdate)();
    
    bool onTouchBegin(Touch* pTouch,Event* pEvent);
    void onTouchMoved(Touch* pTouch,Event* pEvent);
    void onTouchCancelled(Touch* pTouch,Event* pEvent);
    void onTouchEnded(Touch* pTouch,Event* pEvent);
    
};
#endif /* defined(__ToothBrushGame__ResultScene__) */
