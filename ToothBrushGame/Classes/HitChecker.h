//********************************************************************************
//  HitChecker.h
//  ToothBrushGame
//
//  Created by 丸山 潤 on 2014/10/15.
//
//********************************************************************************
//********************************************************************************
// インクルードガード
//********************************************************************************
#ifndef __ToothBrushGame__HitChecker__
#define __ToothBrushGame__HitChecker__

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
class EnemyManager;
class ToothManager;
class PlaqueManager;

//********************************************************************************
// クラス宣言
//********************************************************************************
class HitChecker
{
public:
    HitChecker();
    ~HitChecker();

    static HitChecker* create(EnemyManager* pEnemyManager,ToothManager* pToothManager,PlaqueManager* pPlaqueManager);

    void hitCheckSwipe(Rect touchRect,int nDirectionType);
    void hitCheckTap(Rect touchRect);

private:
    EnemyManager* m_pEnemyManager;
    ToothManager* m_pToothManager;
    PlaqueManager* m_pPlaqueManager;

};

#endif /* defined(__ToothBrushGame__HitChecker__) */
