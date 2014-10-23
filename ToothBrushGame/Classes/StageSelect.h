//********************************************************************************
//  StageSelect.h
//  ToothBrushGame
//
//  Created by 丸山 潤 on 2014/10/21.
//
//********************************************************************************
//********************************************************************************
// インクルードガード
//********************************************************************************
#ifndef __ToothBrushGame__StageSelect__
#define __ToothBrushGame__StageSelect__

//********************************************************************************
// インクルード
//********************************************************************************
#include "cocos2d.h"

//********************************************************************************
// 名前空間の使用
//********************************************************************************
using namespace cocos2d;

//********************************************************************************
// クラス宣言
//********************************************************************************
class StageSelect : public cocos2d::Layer
{
public:
    StageSelect(){};
    ~StageSelect();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    void update(float fTime);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(StageSelect);

    static cocos2d::Layer* createLayer(int nStageNum);

private:
    int m_nStageNum;
    Point m_touchPos;
    EventListenerTouchOneByOne* m_pTouchEventOneByOne;

    Sprite* m_pMaskSprite;
    Sprite** m_ppStageSprites;

    void createStageSprites(void);

    bool onTouchBegin(Touch* pTouch,Event* pEvent);
    void onTouchMoved(Touch* pTouch,Event* pEvent);
    void onTouchCancelled(Touch* pTouch,Event* pEvent);
    void onTouchEnded(Touch* pTouch,Event* pEvent);
};


#endif /* defined(__ToothBrushGame__StageSelect__) */
