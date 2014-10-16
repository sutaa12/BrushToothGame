//********************************************************************************
//  HitChecker.cpp
//  ToothBrushGame
//
//  Created by 丸山 潤 on 2014/10/15.
//
//********************************************************************************
//********************************************************************************
// インクルード
//********************************************************************************
#include "HitChecker.h"
#include "ToothManager.h"
#include "EnemyManager.h"
#include "PlaqueManager.h"
#include "Tooth.h"
#include "Enemy.h"
#include "Plaque.h"

//================================================================================
// コンストラクタ
//================================================================================
HitChecker::HitChecker()
{

}

//================================================================================
// デストラクタ
//================================================================================
HitChecker::~HitChecker()
{

}

//================================================================================
// スワイプ時の当たり判定
//================================================================================
void HitChecker::hitCheckSwipe(Rect touchRect,int nDirectionType)
{
    Plaque** ppPlaque = m_pPlaqueManager->getPlaqueTop();

    for(int nPlaqueNum = 0;nPlaqueNum < m_pPlaqueManager->getPlaqueMaxNum();nPlaqueNum++)
    {
        // 使われていないならスキップ
        if (ppPlaque[nPlaqueNum] == nullptr)
        {
            continue;
        }

        // 既に死んでいるならスキップ
        if (ppPlaque[nPlaqueNum]->getDisappear())
        {
            continue;
        }

        Rect plaqueRect = (ppPlaque[nPlaqueNum]->getSprite())->getBoundingBox();

        if(plaqueRect.intersectsRect(touchRect))
        {
            ppPlaque[nPlaqueNum]->setDisappear(true);
            (ppPlaque[nPlaqueNum]->getSprite())->setOpacity(0);
        }
    }
}

//================================================================================
// タップ時の当たり判定
//================================================================================
void HitChecker::hitCheckTap(Point touchPoint)
{
    
}

//================================================================================
// 生成処理
//================================================================================
HitChecker* HitChecker::create(EnemyManager* pEnemyManager, ToothManager* pToothManager, PlaqueManager* pPlaqueManager)
{
    HitChecker* pHitChecker = new HitChecker();

    pHitChecker->m_pEnemyManager = pEnemyManager;
    pHitChecker->m_pToothManager = pToothManager;
    pHitChecker->m_pPlaqueManager = pPlaqueManager;

    return pHitChecker;
}







