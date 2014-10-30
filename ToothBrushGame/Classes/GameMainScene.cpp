//
//  GameMainScene.cpp
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/17.
//
//
#include "TextureFile.h"
#include "common.h"
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
#include "PauseScene.h"
#include "Score.h"
#include "Sound.h"
#include "CountDown.h"
#include "ToothPowder.h"
#include "GameDifficult.h"
#include "CharacterStatus.h"
#include "VirusToothManager.h"
#include "VirusTooth.h"
#include "Clock.h"
#include "UgaiEffect.h"
#include "ConfigScene.h"
#include "Clock.h"
#include "MenuBar.h"
USING_NS_CC;


static const GAME_PASE_DATA GamePhaseData[PHASE_MAX] =
{
    {Enemy::ENEMY_KIND_NORMAL_ONE,3,0,Point(150,600)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,1,0,Point(150,600)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,1,0,Point(150,600)},
    {Enemy::ENEMY_KIND_NORMAL_TWO,3,5,Point(200,300)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,5,10,Point(300,400)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,5,10,Point(300,400)},
    {Enemy::ENEMY_KIND_LAIR_ONE,2,15,Point(150,400)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,5,20,Point(300,400)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,5,20,Point(300,400)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,5,20,Point(300,400)},
    {Enemy::ENEMY_KIND_NORMAL_TWO,5,25,Point(300,350)},
    {Enemy::ENEMY_KIND_NORMAL_TWO,5,25,Point(300,350)},
    {Enemy::ENEMY_KIND_LAIR_TWO,2,30,Point(150,400)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,8,35,Point(300,400)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,8,35,Point(300,400)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,8,35,Point(300,400)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,8,35,Point(300,400)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,8,35,Point(300,400)},
    {Enemy::ENEMY_KIND_NORMAL_TWO,3,40,Point(150,400)},
    {Enemy::ENEMY_KIND_NORMAL_TWO,3,40,Point(150,400)},
    {Enemy::ENEMY_KIND_LAIR_TREE,2,45,Point(150,400)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,8,45,Point(300,400)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,8,45,Point(300,400)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,8,45,Point(300,400)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,8,45,Point(300,400)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,8,45,Point(300,400)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,8,45,Point(300,400)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,8,45,Point(300,400)},
    {Enemy::ENEMY_KIND_NORMAL_TWO,8,45,Point(300,350)},
    {Enemy::ENEMY_KIND_NORMAL_TWO,8,45,Point(300,350)},
    {Enemy::ENEMY_KIND_NORMAL_TREE,3,50,Point(150,400)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,6,55,Point(300,400)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,6,55,Point(300,400)},
    {Enemy::ENEMY_KIND_NORMAL_TWO,6,55,Point(300,350)},
    {Enemy::ENEMY_KIND_NORMAL_TWO,6,55,Point(300,350)},
    {Enemy::ENEMY_KIND_NORMAL_TREE,6,55,Point(150,400)},
};
//================================================================================
// デストラクタ
//================================================================================
GameMainScene::~GameMainScene()
{
    SAFE_DELETE(m_pEnemyManager);
    SAFE_DELETE(m_pToothManager);
    SAFE_DELETE(m_pPlaqueManager);
    SAFE_DELETE(m_pUIManager);
    SAFE_DELETE(m_pHitChecker);
    SAFE_DELETE(m_EffectManager);
    SAFE_DELETE(m_pVirusToothManager);
    SAFE_DELETE(m_pUgaiEffect);
    //すべてのSEを止める
    SimpleAudioEngine::getInstance()->stopAllEffects();
}

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
    
    Size visibleSize = Director::getInstance()->getVisibleSize() / 2 + SCREEN_CENTER;
    Vec2 origin = Director::getInstance()->getVisibleSize() / 2 - SCREEN_CENTER;
    
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
    
    Enemy::initEnemyDownNum();
    
    //始めるフェーズから
    m_nGamePhase = PHASE_ONE;

    m_nGameTime = GamePhaseData[m_nGamePhase].spawnTime;//終わりの時間になるまで加算
    
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

    // 加速度センサーの有効化
    Device::setAccelerometerEnabled(true);
    auto pAccelerometerEventListener = EventListenerAcceleration::create(CC_CALLBACK_2(GameMainScene::onAcceleration, this));
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pAccelerometerEventListener, this);
    
    // 歯マネージャーのインスタンス化
    m_pToothManager = ToothManager::create(Vec2(visibleSize.width / 2,visibleSize.height - 64),this);
    m_bHit = false;
    m_pPlaqueManager = PlaqueManager::create(0,m_pToothManager->getToothSprite(), this);

    // タッチ時の判定生成
    m_pBubbleSprite = Sprite::create(TEX_BUBBLE_02);
    m_bubblePos = Vec2(0.0f,0.0f);
    m_pBubbleSprite->setPosition(m_bubblePos);
    m_pBubbleSprite->setOpacity(0);
    this->addChild(m_pBubbleSprite);

    m_acc = Vec3(0,0,0);
    m_acc = m_oldAcc;
    m_nShakeCnt = 0;
    m_pVirusToothManager = VirusToothManager::create(this,m_pToothManager->getTongerSprite());
    m_pEnemyManager = EnemyManager::create(this,0);
    //================================================================================
    //敵関係はこれより前に生成
    
    //エフェクト生成
    m_EffectManager = EffectManager::create(this, 0);
    
    //うがい初期か
    m_pUgaiEffect = UgaiEffect::create(this,m_pToothManager->getTongerSprite()->getPosition());
    //フラグ初期化
    m_bMove = false;
    m_touchPos = Point(0.0f,0.0f);
    m_oldTouchPos = m_touchPos;
    m_swipeDirection = SWIPE_DIRECTION_NONE;
    m_oldSwipeDirection = m_swipeDirection;
    
    //UI生成
    m_pUIManager = UIManager::create(this);

    m_pHitChecker = HitChecker::create(m_pEnemyManager, m_pToothManager, m_pPlaqueManager,m_pUIManager);

    m_nTimer = 0;
    

    // 生成が終わった後にカウントダウンを生成する
    //this->scheduleOnce(schedule_selector(GameMainScene::createCountDown), 0.0f);

    
    //今、BGMが流れているかどうか
    if(SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()){
        
        //音楽を止める
        SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
        
    }
    
        //音量調整
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(BGM_GAMESCENE_VOLUME_3);
    //タイトル画面BGMをループ再生 第二引数がループするかどうか判定
    SimpleAudioEngine::getInstance()->playBackgroundMusic(BGM_ENEMY_SCENE_5, true);
        
    m_nUgaiCounter = 0;
    m_nGameEndtTime = 0;

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
    
    //終了時は判定止める
    if(m_nGameEndtTime <= 0)
    {

        //敵の更新
        m_pEnemyManager->update();
    }
    //UI更新
    m_pUIManager->update();
    //エフェクト更新
    m_EffectManager->update();

    m_pHitChecker->checkEnemyFollowPowder(m_touchPos, m_pUIManager->getToothPowder()->getPowderTouchFlag());
    
    updateGamePhase();
}

//================================================================================
// タップ開始判定
//================================================================================

bool GameMainScene::onTouchBegin(Touch* pTouch,Event* pEvent)
{
    
    // タッチ座標の取得
    m_touchPos = pTouch->getLocation();

    // 泡スプライトの追従
    m_bubblePos = m_touchPos;
    m_pBubbleSprite->setPosition(m_bubblePos);
    m_pBubbleSprite->setOpacity(10);

    m_EffectManager->spawn(40,m_touchPos);
    
    //終了時は判定止める
    if(m_nGameEndtTime <= 0)
    {
        AchievementDataBaseList::addAchievement(ACHIEVEMENT_TYPE_USE_TOUP);
        m_pHitChecker->hitCheckTap(m_pBubbleSprite->getBoundingBox());
    }
    m_pUIManager->getToothPowder()->chkPowderTouchFlag(m_touchPos);
    
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
    if(m_pUIManager->getToothPowder()->getPowderTouchFlag())
    {
        m_EffectManager->spawn(10,m_touchPos,Color3B(220,220,255));
    }
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


    // 歯磨き粉スプライト座標調整
    if(m_pUIManager->getToothPowder()->getPowderTouchFlag())
    {
        Rect gameTopRect = m_pUIManager->getGameTopBackSprite()->getBoundingBox();
        Rect gameBottomRect = m_pUIManager->getGameBottomBackSprite()->getBoundingBox();
        Rect toothPowderRect = m_pUIManager->getToothPowder()->getSprite()->getBoundingBox();
        Point workPoint = m_touchPos;

        // ゲーム上部UIに引っかかるなら戻す
        if(gameTopRect.origin.y < workPoint.y + toothPowderRect.size.height / 2)
        {
            workPoint.y = gameTopRect.origin.y - toothPowderRect.size.height / 2;
        }

        // ゲーム下部UIに引っかかるなら戻す
        if(gameBottomRect.origin.y + gameBottomRect.size.height > workPoint.y - toothPowderRect.size.height / 2)
        {
            workPoint.y = gameBottomRect.origin.y + gameBottomRect.size.height + toothPowderRect.size.height / 2;
        }

        m_pUIManager->getToothPowder()->setPos(workPoint);
    }
    //終了時は判定止める
    if(m_nGameEndtTime <= 0)
    {
        // スワイプ時の当たり判定
        m_pHitChecker->hitCheckSwipe(swipeRect, m_swipeDirection,m_pUIManager->getToothPowder()->getPowderTouchFlag());
    }
    //幼女を下方向にスワイプしたときにうがい
    if( m_swipeDirection == SWIPE_DIRECTION_DOWN &&
       m_pUIManager->getCharacterStatus()->getPattern() != CharacterStatus::CHARACTERSTATUS_PATTERN_GIDDY &&VirusToothManager::collideAtPoint(m_pUIManager->getCharacterStatus()->getSprite(), swipeRect.origin)
       )
    {
        m_pUgaiEffect->setSpawn();
        AchievementDataBaseList::addAchievement(ACHIEVEMENT_TYPE_USE_UGAI);
        m_pUIManager->getCharacterStatus()->setPattern(CharacterStatus::CHARACTERSTATUS_PATTERN_GIDDY);
        if(m_nGameEndtTime <= 0)
        {
            m_pHitChecker->checkEnemyDown();
        }
        //SE
        SimpleAudioEngine::getInstance()->setEffectsVolume(SE_VOLUME_MAX);
        SimpleAudioEngine::getInstance()->playEffect(SE_SHAKE_1);
        m_nUgaiCounter = 1;
    }
}

//================================================================================
// タップ離した判定
//================================================================================

void GameMainScene::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    if(m_nGameEndtTime <= 0)
    {

        m_pHitChecker->hitCheckTouchEnded(m_pBubbleSprite->getBoundingBox(),m_pUIManager->getToothPowder()->getPowderTouchFlag());
    }
    // タッチしていないので泡スプライトを透明に
    m_pBubbleSprite->setOpacity(0);
    
    m_swipeDirection = SWIPE_DIRECTION_NONE;
    
    m_pUIManager->getToothPowder()->disappear();
    
    m_bHit = false;
}

//================================================================================
// タッチ時に割り込み処理
//================================================================================
void GameMainScene::onTouchCancelled(Touch* pTouch, Event* pEvent)
{
    m_pHitChecker->hitCheckTouchEnded(m_pBubbleSprite->getBoundingBox(),m_pUIManager->getToothPowder()->getPowderTouchFlag());
    
    m_nTimer = 0;
    m_pUIManager->getToothPowder()->disappear();
    
}

//================================================================================
// 加速度センサー割り込み処理
//================================================================================
void GameMainScene::onAcceleration(Acceleration *acc,Event *unused_event)
{
    m_oldAcc = m_acc;
    m_acc = Vec3(acc->x,acc->y,acc->z);

    Vec3 work = m_acc - m_oldAcc;
    float fDistance = (work.x * work.x + work.y * work.y + work.z * work.z);

    if(fDistance > ConfigScene::getShakePermissionDistance())
    {
        m_nShakeCnt++;
    }

    //シェイク３回でうがい処理
    if(m_nShakeCnt > 3)
    {
        if(m_pUIManager->getCharacterStatus()->getPattern() != CharacterStatus::CHARACTERSTATUS_PATTERN_GIDDY)
        {
            m_pUgaiEffect->setSpawn();
            AchievementDataBaseList::addAchievement(ACHIEVEMENT_TYPE_USE_UGAI);
            m_pUIManager->getCharacterStatus()->setPattern(CharacterStatus::CHARACTERSTATUS_PATTERN_GIDDY);
            if(m_nGameEndtTime <= 0)
            {
                m_pHitChecker->checkEnemyDown();
            }
        //SE
        SimpleAudioEngine::getInstance()->setEffectsVolume(SE_VOLUME_MAX);
        SimpleAudioEngine::getInstance()->playEffect(SE_SHAKE_1);
            m_nUgaiCounter = 1;
        }
        m_nShakeCnt = 0;

    }
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
//================================================================================
// 結果へ移行
//================================================================================
void GameMainScene::setResultScene(bool bGameOverFlag)
{
    m_pUIManager->getClock()->stopTime();
    if(m_nGameEndtTime <= 0)
    {
        Size visibleSize = Director::getInstance()->getVisibleSize() / 2 + SCREEN_CENTER;
        Vec2 origin = Director::getInstance()->getVisibleSize() / 2 - SCREEN_CENTER;
        m_nGameEndtTime = 1;

        // ゲームが終了しているのでポーズを不許可に
        m_pUIManager->getMenuBar()->setPausePermission(false);
        
        Sprite* pBack = Sprite::create();
        Sprite* pToothSize = m_pToothManager->getTongerSprite();
        pBack->setTextureRect(Rect(0,0,pToothSize->getContentSize().width,pToothSize->getContentSize().height));
        pBack->setColor(Color3B::BLACK);
        pBack->setOpacity(80);
        pBack->setPosition(pToothSize->getPosition());
        addChild(pBack);

        
        LabelTTF* pEndGameMessage = LabelTTF::create("はみがきせいこう！","Arrial",42);
        pEndGameMessage->setPosition(Vec2(visibleSize.width / 2,visibleSize.height - 50));
        pEndGameMessage->setColor(Color3B::WHITE);
        pEndGameMessage->enableStroke(Color3B::BLACK,6);
        pEndGameMessage->setOpacity(0);
        if(bGameOverFlag)
        {
            
            String* Message = String::createWithFormat( "はみがきしっぱい！");
            pEndGameMessage->setString(Message->getCString());
            pEndGameMessage->setColor(Color3B::RED);

            //ゲームオーバー音
            SimpleAudioEngine::getInstance()->setEffectsVolume(SE_VOLUME_HALF);
            SimpleAudioEngine::getInstance()->playEffect(SE_GAME_OVER_2);
        }else{

            Sprite* ToothShine = Sprite::create(TEX_KIRAKIRA_01);
            ToothShine->setPosition(visibleSize.width - 300, visibleSize.height - 150);
            ToothShine->setOpacity(0);
            ToothShine->setScale(0.6f);
            Sequence* pSequence = Sequence::create(FadeIn::create(0.1f),ScaleTo::create(1.0,1.5f),ScaleTo::create(1.0,0.6f),FadeOut::create(0.1f),NULL);
            
            Sprite* ToothShine2 = Sprite::create(TEX_KIRA_01);
            ToothShine2->setPosition(origin.x + 200, origin.y + 350);
            ToothShine2->setOpacity(0);
            ToothShine2->setScale(0.6f);
            Sequence* pSequence2 = Sequence::create(FadeIn::create(0.1f),ScaleTo::create(0.8,1.5f),ScaleTo::create(0.8,0.6f),FadeOut::create(0.1f),NULL);
            
            Sprite* ToothShine3 = Sprite::create(TEX_KIRA_01);
            ToothShine3->setPosition(visibleSize.width - 200, origin.y + 350);
            ToothShine3->setOpacity(0);
            ToothShine3->setScale(0.3f);
            Sequence* pSequence3 = Sequence::create(FadeIn::create(0.1f),ScaleTo::create(0.8,1.5f),ScaleTo::create(0.8,0.6f),FadeOut::create(0.1f),NULL);

            ToothShine->runAction(RepeatForever::create(pSequence));
            addChild(ToothShine);
            ToothShine2->runAction(RepeatForever::create(pSequence2));
            addChild(ToothShine2);
            ToothShine3->runAction(RepeatForever::create(pSequence2));
            addChild(ToothShine3);

            //ゲームクリア　キラキラ音
            SimpleAudioEngine::getInstance()->setEffectsVolume(SE_VOLUME_HALF);
            SimpleAudioEngine::getInstance()->playEffect(SE_SHINE_1);

        }

        addChild(pEndGameMessage);
        pEndGameMessage->runAction(Spawn::create(FadeIn::create(1),MoveBy::create(1.0, Vec2(0,-300)), NULL));
    }
    if(m_nGameEndtTime > GAME_END_TIME)
    {
        this->getEventDispatcher()->removeAllEventListeners();
        this->removeAllChildren();
        this->unscheduleUpdate();
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f,ResultScene::createScene(bGameOverFlag,m_pUIManager->getClock()->getColockNow()),Color3B::WHITE));
    }
}
//================================================================================
// カウントダウン生成処理
//================================================================================
void GameMainScene::createCountDown(float fTime)
{
    m_pCountDown = CountDown::createLayer(5,m_pHitChecker);
    this->addChild(m_pCountDown);
    this->pause();

    m_bCountDownEnd = false;
}

//================================================================================
// ゲームフェーズ更新
//================================================================================
void GameMainScene::updateGamePhase(void)
{
    m_nTimer++;
    if(m_nUgaiCounter != 0)
    {
    m_nUgaiCounter++;
        if(m_nUgaiCounter > UGAI_DELAY)
        {
            m_nUgaiCounter = 0;
        }
    }
    if(m_nTimer % 60 == 0)
    {
        m_nGameTime++;
        AchievementDataBaseList::saveAchievement();
        //１以上ないと加算しない
        if(m_nGameEndtTime > 0)
        {
            m_nGameEndtTime++;
        }
    }
    chkGamePhase();
}
//================================================================================
// ゲームフェーズチェック
//================================================================================
void GameMainScene::chkGamePhase(void)
{
    //終了時は止める
    if(m_nGameEndtTime <= 0)
    {

        if(m_nGamePhase < PHASE_MAX && (m_nGameTime >= GamePhaseData[m_nGamePhase].spawnTime || m_pEnemyManager->getEnemyNum() < 2))
        {
            
            m_pEnemyManager->spawn(GamePhaseData[m_nGamePhase].enemykind,GamePhaseData[m_nGamePhase].spawn,m_pVirusToothManager->getVirusToothsTop(m_nGamePhase)->getSprite()->getPosition());
            m_pVirusToothManager->getVirusToothsTop(m_nGamePhase)->disappear();
            if(m_nGamePhase <= PHASE_MAX)
            {
                m_nGamePhase++;
            }

            while(GamePhaseData[m_nGamePhase].spawnTime == GamePhaseData[m_nGamePhase - 1].spawnTime)
            {
                m_pEnemyManager->spawn(GamePhaseData[m_nGamePhase].enemykind,GamePhaseData[m_nGamePhase].spawn,m_pVirusToothManager->getVirusToothsTop(m_nGamePhase)->getSprite()->getPosition());
                m_pVirusToothManager->getVirusToothsTop(m_nGamePhase)->disappear();
                if(m_nGamePhase <= PHASE_MAX)
                {
                    m_nGamePhase++;
                }
            }
        }
    }
    int nEnemyDown = 0;

    for(int nloop = 0; nloop < PHASE_MAX;nloop++)
    {
        if(GamePhaseData[nloop].enemykind < Enemy::ENEMY_KIND_LAIR_ONE)
        {
            nEnemyDown += GamePhaseData[nloop].spawn;
        }
    }
    int EnemyAll = 0;
    for(int nloop = 0 ; nloop < Enemy::ENEMY_KIND_LAIR_ONE;nloop++)
    {
        EnemyAll += Enemy::getEnemyKindDownNum(nloop);
    }
    if(  EnemyAll >= nEnemyDown)
    {
        setResultScene(false);
    }else
    if(m_pUIManager->getClock()->getColockNow() <= 0)
    {
        setResultScene(true);
    }

    m_pUIManager->getCharacterStatus()->checkChangePattern(nEnemyDown,EnemyAll );
}
