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
#include "HelloWorldScene.h"

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

        // 当たり判定
        if(plaqueRect.intersectsRect(touchRect))
        {
            if(nDirectionType == HelloWorld::SWIPE_DIRECTION_LEFT || nDirectionType == HelloWorld::SWIPE_DIRECTION_RIGHT)
            {
                ppPlaque[nPlaqueNum]->addDamage(1);
            }

            else if(nDirectionType == HelloWorld::SWIPE_DIRECTION_UP || HelloWorld::SWIPE_DIRECTION_DOWN)
            {
                ppPlaque[nPlaqueNum]->addDamage(3);
            }
            else
            {

            }
        }
    }
}

//================================================================================
// タップ時の当たり判定
//================================================================================
void HitChecker::hitCheckTap(Rect touchRect)
{
    Enemy** ppEnemy = m_pEnemyManager->getEnemysTop();

    for(int nEnemyNum = 0;nEnemyNum < EnemyManager::ENEMY_MAX;nEnemyNum++)
    {
        // 使われていないならスキップ
        if(ppEnemy[nEnemyNum] == nullptr)
        {
            continue;
        }

        // 既に死んでいるならスキップ
        if(ppEnemy[nEnemyNum]->getDisapper())
        {
            continue;
        }

        Rect enemyRect = (ppEnemy[nEnemyNum]->getSprite())->getBoundingBox();

        // 当たり判定
        if(enemyRect.intersectsRect(touchRect))
        {
            ppEnemy[nEnemyNum]->addDamage();
        }
    }
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







