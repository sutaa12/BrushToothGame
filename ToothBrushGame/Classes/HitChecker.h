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
class UIManager;

//********************************************************************************
// クラス宣言
//********************************************************************************
class HitChecker
{
public:
    HitChecker();
    ~HitChecker();

    static HitChecker* create(EnemyManager* pEnemyManager,ToothManager* pToothManager,PlaqueManager* pPlaqueManager,UIManager* pUIManager);

    void hitCheckSwipe(Rect touchRect,int nDirectionType,bool bToothPowder);
    void hitCheckTap(Rect touchRect);
    void hitCheckTouchEnded(Rect touchRect,bool bTouchPowder);

    void checkEnemyFollowPowder(Point touchPoint,bool bToothPowder);
    void checkEnemyDown(void);
    bool checkTapOnMenuBar(Point touchPoint);
    bool hitCheckPointCharacter(Point touchPoint,Sprite* pCheckSprite);

private:
    EnemyManager* m_pEnemyManager;
    ToothManager* m_pToothManager;
    PlaqueManager* m_pPlaqueManager;
    UIManager* m_pUIManager;
};

#endif /* defined(__ToothBrushGame__HitChecker__) */
