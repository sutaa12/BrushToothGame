//
//  GameMainScene.cpp
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/17.
//
//

#include "GameMainScene.h"
#include "Tooth.h"
#include "ToothManager.h"
#include "Plaque.h"
#include "PlaqueManager.h"
#include "EnemyManager.h"
#include "Boss.h"
#include "HitChecker.h"
#include "LifeBar.h"
#include "UIManager.h"
#include "EffectManager.h"
#include "ResultScene.h"
#include "TitleScene.h"
USING_NS_CC;
//================================================================================
// シーン生成
//================================================================================

Scene* GameMainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameMainScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

//================================================================================
// シーン初期化
//================================================================================
// on "init" you need to initialize your instance
bool GameMainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //終了ボタン生成
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameMainScene::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    // 更新処理の追加
    this->scheduleUpdate();
    
    // タッチ機能の有効化
    m_pTouchEventOneByOne =  EventListenerTouchOneByOne::create();
    m_pTouchEventOneByOne->setSwallowTouches(true);
    m_pTouchEventOneByOne->onTouchBegan = CC_CALLBACK_2(GameMainScene::onTouchBegin,this);
    m_pTouchEventOneByOne->onTouchMoved = CC_CALLBACK_2(GameMainScene::onTouchMoved,this);
    m_pTouchEventOneByOne->onTouchCancelled = CC_CALLBACK_2(GameMainScene::onTouchCancelled, this);
    m_pTouchEventOneByOne->onTouchEnded = CC_CALLBACK_2(GameMainScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithFixedPriority(m_pTouchEventOneByOne, 100);
    
    // 歯マネージャーのインスタンス化
    m_pToothManager = ToothManager::create(Vec2(0.0f,visibleSize.height - 64),this);
    m_bHit = false;
    m_pPlaqueManager = PlaqueManager::create(200, this);

    
    m_pBoss = Boss::create(m_pEnemyManager,Vec2(350,500));
    this->addChild(m_pBoss->getSprite());
    m_pBoss->disappear();
    
    // タッチ時の判定生成
    m_pBubbleSprite = Sprite::create("bubble_01.png");
    m_bubblePos = Vec2(0.0f,0.0f);
    m_pBubbleSprite->setPosition(m_bubblePos);
    m_pBubbleSprite->setOpacity(0);
    this->addChild(m_pBubbleSprite);

    m_pEnemyManager = EnemyManager::create(this,50);

    //================================================================================
    //敵関係はこれより前に生成
    
    //エフェクト生成
    m_EffectManager = EffectManager::create(this, 0);
    
    //フラグ初期化
    m_bBossDisp = false;
    m_bMove = false;
    m_touchPos = Point(0.0f,0.0f);
    m_oldTouchPos = m_touchPos;
    m_swipeDirection = SWIPE_DIRECTION_NONE;
    m_oldSwipeDirection = m_swipeDirection;
    
    this->addChild(Plaque::create(Vec2(64, 64))->getSprite());
    
    m_pHitChecker = HitChecker::create(m_pEnemyManager, m_pToothManager, m_pPlaqueManager);
    
    //UI生成
    m_pUIManager = UIManager::create(this);
    
    m_nTimer = 0;
    
    return true;
}

//================================================================================
// ゲーム終了処理
//================================================================================
void GameMainScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//================================================================================
// ゲーム更新
//================================================================================
void GameMainScene::update(float fTime)
{
    
    // 歯の更新
    m_pToothManager->update();
    // 歯垢の更新
    m_pPlaqueManager->update();
    
    // 歯を動かすか判定
    //歯垢が０になったら
    int nPlaqur = m_pPlaqueManager->getPlaqueNum();
    Plaque** ppPlaque = m_pPlaqueManager->getPlaqueTop();
    int nPlaqurNum = 0;
    for(int nloop = 0;nloop < nPlaqur;nloop++)
    {
        //生きていたらカウント
        if(!ppPlaque[nloop]->getDisappear())
        {
            nPlaqurNum++;
        }
    }
    if(!m_bBossDisp && nPlaqurNum <= 0)
    {
        m_bMove = true;
        
        m_pToothManager->moveToothAndGum(1.0f, Vec2(0, 120));
        
        // ボス出現判定
        if(!m_bBossDisp)
        {
            //敵を消す
            m_pEnemyManager->setEnemyClear();
            // ボスの生成
            m_bBossDisp = true;
            m_pBoss->setSpawn(Vec2(350,500));
        }
    }
    //敵の更新
    m_pEnemyManager->update();
    
    
    
    //ボスの更新
    if(m_bBossDisp && !m_pBoss->getDisapper())
    {
        m_pBoss->update();
    }
    
    //UI更新
    m_pUIManager->update();
    //エフェクト更新
    m_EffectManager->update();
    /*
    //しばらくタッチしていると次のシーンにしたかった（できていない）
    if(m_nTimer != 0)
    {
        m_nTimer++;
        if(m_nTimer > 120)
        {
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f,ResultScene::createScene(),Color3B::WHITE));
            this->getEventDispatcher()->removeAllEventListeners();
            this->removeAllChildren();
            
        }

    }
     */
}

//================================================================================
// タップ開始判定
//================================================================================

bool GameMainScene::onTouchBegin(Touch* pTouch,Event* pEvent)
{
    m_nTimer++;
    // タッチ座標の取得
    m_touchPos = pTouch->getLocation();
    
    // 泡スプライトの追従
    m_bubblePos = m_touchPos;
    m_pBubbleSprite->setPosition(m_bubblePos);
    m_pBubbleSprite->setOpacity(10);
    
    m_EffectManager->spawn(40,m_touchPos);
    
    m_pHitChecker->hitCheckTap(m_pBubbleSprite->getBoundingBox());
    
    // ボスが出現しているとき
    if(m_bBossDisp)
    {
        // ボススプライトのサイズ取得
        Rect bossSpriteRect = m_pBoss->getSprite()->getBoundingBox();
        
        // ボス当たり判定
        if(bossSpriteRect.containsPoint(m_touchPos) && !m_pBoss->getDisapper())
        {
            // ボスにダメージ
            m_pBoss->addDamage();
        }
    }
    return true;
}

//================================================================================
// スワイプ判定
//================================================================================

void GameMainScene::onTouchMoved(Touch* pTouch,Event* pEvent)
{
    Point swipVec = Point(0,0);
    
    // タッチ座標の取得
    m_oldTouchPos = m_touchPos;
    m_touchPos = pTouch->getLocation();
    
    // 泡スプライトの追従
    m_bubblePos = m_touchPos;
    m_pBubbleSprite->setPosition(m_bubblePos);
    
    m_EffectManager->spawn(10,m_touchPos,Color3B(220,220,255));
    
    
    CCLOG("現タッチ位置(%f,%f)",m_touchPos.x,m_touchPos.y);
    CCLOG("旧タッチ位置(%f,%f)",m_oldTouchPos.x,m_oldTouchPos.y);
    
    float fDistance = m_touchPos.distance(m_oldTouchPos);
    
    CCLOG("距離(%f)",fDistance);
    
    // スワイプされているならスワイプ方向の取得
    if(fDistance > SWIPE_PERMISSION_DISTANCE)
    {
        Point::subtract(m_touchPos, m_oldTouchPos, &swipVec);
        float fAngle = atan2f(swipVec.x,swipVec.y);
        CCLOG("角度(%f)",fAngle);
        
        m_oldSwipeDirection = m_swipeDirection;
        m_swipeDirection = calcSwipeDirection(fAngle);
    }
    else
    {
        m_swipeDirection = SWIPE_DIRECTION_NONE;
    }
    
    // スワイプされていないorスワイプしていても異常な角度
    if(m_swipeDirection == SWIPE_DIRECTION_NONE)
    {
        return;
    }
    
    // 当たり判定領域の算出
    Rect bubbleRect = m_pBubbleSprite->getBoundingBox();
    Rect swipeRect;
    swipeRect.setRect(m_touchPos.x - swipVec.x - bubbleRect.size.width / 2 ,m_touchPos.y - swipVec.y  - bubbleRect.size.height / 2,
                      swipVec.x + bubbleRect.size.width, swipVec.y + bubbleRect.size.height);
    
    // スワイプ時の当たり判定
    m_pHitChecker->hitCheckSwipe(swipeRect, m_swipeDirection);
}

//================================================================================
// タップ離した判定
//================================================================================

void GameMainScene::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    // タッチしていないので泡スプライトを透明に
    m_pBubbleSprite->setOpacity(0);
    
    m_swipeDirection = SWIPE_DIRECTION_NONE;
    
    m_bHit = false;
    m_nTimer = 0;
}

//================================================================================
// タッチ時に割り込み処理
//================================================================================
void GameMainScene::onTouchCancelled(Touch* pTouch, Event* pEvent)
{
    m_nTimer = 0;
}

//================================================================================
// スワイプ方向
//================================================================================
GameMainScene::SWIPE_DIRECTION GameMainScene::calcSwipeDirection(float fAngle)
{
    fAngle = fAngle * 180 / M_PI;
    
    if(fAngle <= 45 && fAngle >= -45)
    {
        CCLOG("上方向");
        return SWIPE_DIRECTION_UP;
    }
    
    if(fAngle <= 135 && fAngle >= 45)
    {
        CCLOG("右方向");
        return SWIPE_DIRECTION_RIGHT;
    }
    
    if(fAngle <= -45 && fAngle >= -135)
    {
        CCLOG("左方向");
        return SWIPE_DIRECTION_LEFT;
    }
    
    if((fAngle <= -135 && fAngle >= -180) || (fAngle <= 180 && fAngle >= 135))
    {
        CCLOG("下方向");
        return SWIPE_DIRECTION_DOWN;
    }
    
    return SWIPE_DIRECTION_NONE;
}