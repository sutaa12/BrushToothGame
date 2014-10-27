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
#include "ToothPowder.h"
#include "Sound.h"
#include "SoundManager.h"

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
void HitChecker::hitCheckSwipe(Rect touchRect,int nDirectionType,bool bToothPowder)
{
    // 歯磨き粉と敵の当たり判定
    if(bToothPowder == false)
    {
        return;
    }

    Enemy** ppEnemy = m_pEnemyManager->getEnemysTop();
    Rect powderSprite = m_pUIManager->getToothPowder()->getItemIconSprite()->getBoundingBox();
    Vec2 powderSpritePos = powderSprite.origin + powderSprite.size / 2;

    for(int nEnemyNum = EnemyManager::ENEMY_MAX - 1;nEnemyNum >= 0;nEnemyNum--)
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
        if(enemyRect.intersectsRect(touchRect) && ppEnemy[nEnemyNum]->getFollowPowder() == false)
        {
            ppEnemy[nEnemyNum]->setFollowPowder(true);
            //敵がくっついたら　SE
            SimpleAudioEngine::getInstance()->playEffect(SE_SWIPE_1);
        }

        if(ppEnemy[nEnemyNum]->getFollowPowder())
        {
            ppEnemy[nEnemyNum]->setPos(powderSpritePos);
        }
    }
}

//================================================================================
// タップ時の当たり判定
//================================================================================
void HitChecker::hitCheckTap(Rect touchRect)
{
    Enemy** ppEnemy = m_pEnemyManager->getEnemysTop();
    Point point = touchRect.origin;
    point += touchRect.size / 2;

    for(int nEnemyNum = EnemyManager::ENEMY_MAX - 1;nEnemyNum >= 0;nEnemyNum--)
    {
        // 使われていないならスキップ
        if(ppEnemy[nEnemyNum] == nullptr)
        {
            continue;
        }

        // 既に消えているならスキップ
        if(ppEnemy[nEnemyNum]->getEnemyDownFlag())
        {
            continue;
        }

        Rect enemyRect = (ppEnemy[nEnemyNum]->getSprite())->getBoundingBox();

        // 当たっていなかったらスキップ
        if(!enemyRect.containsPoint(point))
        {
            continue;
        }

        // 既に死んでいるなら当たり判定を終了する
        if(ppEnemy[nEnemyNum]->getDisapper())
        {
            return;
        }

        ppEnemy[nEnemyNum]->addDamage();

        return;
    }
}

//================================================================================
// タッチ終了時当たり判定
//================================================================================
void HitChecker::hitCheckTouchEnded(Rect touchRect,bool bToothPowder)
{
    // 歯磨き粉と敵の当たり判定
    if(bToothPowder == false)
    {
        return;
    }

    //歯磨き粉ボムはなしたらSE止める
    SoundManager::stopSoundID(ID_SE_POWDER_2);

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
        if(enemyRect.intersectsRect(m_pUIManager->getToothPowder()->getItemIconSprite()->getBoundingBox()))
        {
            ppEnemy[nEnemyNum]->addDamage(100);
        }

        ppEnemy[nEnemyNum]->setFollowPowder(false);
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
// エネミー歯磨き粉追従チェック処理
//================================================================================
void HitChecker::checkEnemyFollowPowder(Point touchPoint,bool bToothPowder)
{
    // 歯磨き粉が出ていないなら処理をしない
    if(bToothPowder == false)
    {
        return;
    }

    Enemy** ppEnemy = m_pEnemyManager->getEnemysTop();
    Rect powderSprite = m_pUIManager->getToothPowder()->getItemIconSprite()->getBoundingBox();
    Vec2 powderSpritePos = powderSprite.origin + powderSprite.size / 2;

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

        if(ppEnemy[nEnemyNum]->getFollowPowder())
        {
            ppEnemy[nEnemyNum]->setPos(powderSpritePos);
        }
    }
}

//================================================================================
// エネミー死亡チェック処理
//================================================================================
void HitChecker::checkEnemyDown(void)
{
    Enemy** ppEnemy = m_pEnemyManager->getEnemysTop();

    for(int nEnemyNum = 0;nEnemyNum < EnemyManager::ENEMY_MAX;nEnemyNum++)
    {
        // 使われていないならスキップ
        if(ppEnemy[nEnemyNum] == nullptr)
        {
            continue;
        }

        //敵死んでいてなおかつ消えてなかったら
        if(ppEnemy[nEnemyNum]->getDisapper() && !ppEnemy[nEnemyNum]->getEnemyDownFlag())
        {
            ppEnemy[nEnemyNum]->setEnemyDown();
        }
    }
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