//
//  EffectManager.h
//  ToothBrushGame
//
//  Created by 鈴木愛忠 on 2014/10/17.
//
//

#ifndef __ToothBrushGame__EffectManager__
#define __ToothBrushGame__EffectManager__

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
class Bubble;

//********************************************************************************
// クラス宣言
//********************************************************************************
class EffectManager
{
public:
    //最初に出す敵の数
    EffectManager(int numEffect);
    ~EffectManager();
    
    bool init(void);
    void uninit(void);
    void update(void);
    
    static EffectManager* create(Layer* layer,int numEffect);
    
    //敵の先頭取得
    Bubble** getEffectsTop(void){return &m_pEffect[0];}
    
    //敵の数取得
    int getEffectNum(void);
    
    //すべての敵を消す
    void setEffectClear(void);
    
    void spawn(int nSpawnNum = Effect_MAX,Vec2 pos = Vec2(0,0),Color3B col = Color3B(255,255,255));
public:
    //敵の最大数
    static const int Effect_MAX = 150;
    //開始する時間感覚
    static const int TIME_SPAN = 100;
private:
    
    //敵の配列
    Bubble* m_pEffect[Effect_MAX];
    
    Layer* m_pLayer;
    
    int m_nTime;
    
    int m_nTimeSpan;
};

#endif /* defined(__ToothBrushGame__EffectManager__) */
