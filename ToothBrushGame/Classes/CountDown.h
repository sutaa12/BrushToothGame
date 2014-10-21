//
//  CountDown.h
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/20.
//
//

#ifndef __ToothBrushGame__CountDown__
#define __ToothBrushGame__CountDown__

//********************************************************************************
// インクルード
//********************************************************************************
#include "cocos2d.h"

//********************************************************************************
// 名前空間の使用
//********************************************************************************
using namespace cocos2d;

//********************************************************************************
// 前方クラス宣言
//********************************************************************************
class Number;
class HitChecker;

//********************************************************************************
// クラス宣言
//********************************************************************************
class CountDown : public Layer
{
public:
    CountDown();
    ~CountDown();

    bool init(void);
    void uninit(void);
    void update(float fTime);

    static CountDown* create(const Vec2& startLeftTopPos,int nCountDownNum);
    static cocos2d::Layer* createLayer(int nCountDownNum,HitChecker* pHitChecker);

    Number* getNumber(void){return m_pNumber;}
    Label* getLabel(){return m_pNumLabel ;}

    void refreshLabelPos(void);

    CREATE_FUNC(CountDown);

private:
    Vec2 m_startLeftTopPos;
    EventListenerTouchOneByOne* m_pTouchEventOneByOne;
    HitChecker* m_pHitChecker;

    Number* m_pNumber;
    Layer* m_pParentLayer;
    Label* m_pNumLabel;
    Sprite* m_pMaskSprite;

    bool onTouchBegin(Touch* pTouch,Event* pEvent);
    void onTouchMoved(Touch* pTouch,Event* pEvent);
    void onTouchCancelled(Touch* pTouch,Event* pEvent);
    void onTouchEnded(Touch* pTouch,Event* pEvent);

    int m_nNum;
    int m_nTimer;
    bool m_bEnd;
};

#endif /* defined(__ToothBrushGame__CountDown__) */