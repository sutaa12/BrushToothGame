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
#include "Gum.h"
#include "Enemy.h"
#include "Plaque.h"
#include "GameMainScene.h"
#include "LifeBar.h"
#include "UIManager.h"
#include "MenuBar.h"

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

    // 歯垢との当たり判定
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
            if(nDirectionType == GameMainScene::SWIPE_DIRECTION_LEFT || nDirectionType == GameMainScene::SWIPE_DIRECTION_RIGHT)
            {
                ppPlaque[nPlaqueNum]->addDamage(1);
            }

            else if(nDirectionType == GameMainScene::SWIPE_DIRECTION_UP || GameMainScene::SWIPE_DIRECTION_DOWN)
            {
                ppPlaque[nPlaqueNum]->addDamage(3);
            }
            else
            {

            }
        }
    }

    // 上歯茎との当たり判定
    Rect gumRect = ((m_pToothManager->getTopGum())->getSprite())->getBoundingBox();

    if (gumRect.intersectsRect(touchRect))
    {
        if(nDirectionType == GameMainScene::SWIPE_DIRECTION_LEFT || nDirectionType == GameMainScene::SWIPE_DIRECTION_RIGHT)
        {
            (m_pToothManager->getTopGum())->addDamage(1);
        }

        else if(nDirectionType == GameMainScene::SWIPE_DIRECTION_UP || GameMainScene::SWIPE_DIRECTION_DOWN)
        {
            (m_pToothManager->getTopGum())->addDamage(3);
        }
        else
        {

        }
    }

    // 下歯茎との当たり判定
    gumRect = ((m_pToothManager->getBottomGum())->getSprite())->getBoundingBox();

    if (gumRect.intersectsRect(touchRect))
    {
        if(nDirectionType == GameMainScene::SWIPE_DIRECTION_LEFT || nDirectionType == GameMainScene::SWIPE_DIRECTION_RIGHT)
        {
            (m_pToothManager->getBottomGum())->addDamage(1);
        }

        else if(nDirectionType == GameMainScene::SWIPE_DIRECTION_UP || GameMainScene::SWIPE_DIRECTION_DOWN)
        {
            (m_pToothManager->getBottomGum())->addDamage(3);
        }
        else
        {

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
// メニューバータップチェック処理
//================================================================================
bool HitChecker::checkTapOnMenuBar(Point touchPoint)
{
    MenuBar* pMenuBar = m_pUIManager->getMenuBar();

    Rect menuBarRect = (pMenuBar->getSprite())->getBoundingBox();

    if(menuBarRect.containsPoint(touchPoint))
    {
        return true;
    }

    return false;
}

//================================================================================
// 生成処理
//================================================================================
HitChecker* HitChecker::create(EnemyManager* pEnemyManager, ToothManager* pToothManager, PlaqueManager* pPlaqueManager,UIManager* pUIManager)
{
    HitChecker* pHitChecker = new HitChecker();

    pHitChecker->m_pEnemyManager = pEnemyManager;
    pHitChecker->m_pToothManager = pToothManager;
    pHitChecker->m_pPlaqueManager = pPlaqueManager;
    pHitChecker->m_pUIManager = pUIManager;

    return pHitChecker;
}