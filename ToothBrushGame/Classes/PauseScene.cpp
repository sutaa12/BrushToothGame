//
//  PauseScene.cpp
//  ToothBrushGame
//
//  Created by 丸山 潤 on 2014/10/20.
//
//

#include "PauseScene.h"
#include "GameMainScene.h"
#include "TitleScene.h"

USING_NS_CC;
//================================================================================
// デストラクタ
//================================================================================
PauseScene::~PauseScene()
{
    //this->getEventDispatcher()->removeEventListener(m_pTouchEventOneByOne);
}

//================================================================================
// レイヤー生成
//================================================================================
Layer* PauseScene::createLayer(void)
{
    auto layer = PauseScene::create();

    return layer;
}

//================================================================================
// シーン初期化
//================================================================================
bool PauseScene::init()
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
                                           CC_CALLBACK_1(PauseScene::menuCloseCallback, this));

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
    m_pTouchEventOneByOne->onTouchBegan = CC_CALLBACK_2(PauseScene::onTouchBegin,this);
    m_pTouchEventOneByOne->onTouchMoved = CC_CALLBACK_2(PauseScene::onTouchMoved,this);
    m_pTouchEventOneByOne->onTouchCancelled = CC_CALLBACK_2(PauseScene::onTouchCancelled, this);
    m_pTouchEventOneByOne->onTouchEnded = CC_CALLBACK_2(PauseScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithFixedPriority(m_pTouchEventOneByOne, 10);

    // 薄暗いスプライトを作成
    m_pMaskSprite = Sprite::create();
    m_pMaskSprite->setTextureRect(Rect(0,0,visibleSize.width,visibleSize.height));
    m_pMaskSprite->setColor(Color3B::BLACK);
    m_pMaskSprite->setOpacity(125);
    m_pMaskSprite->setPosition(Vec2(visibleSize.width / 2,visibleSize.height / 2));
    this->addChild(m_pMaskSprite);

    m_pRetryGameSprite = Sprite::create();
    m_pRetryGameSprite->setTextureRect(Rect(0,0,100,100));
    m_pRetryGameSprite->setColor(Color3B::GREEN);
    m_pRetryGameSprite->setPosition(Vec2(400,600));
    this->addChild(m_pRetryGameSprite);

    m_pReturnTitleSprite = Sprite::create();
    m_pReturnTitleSprite->setTextureRect(Rect(0,0,100,100));
    m_pReturnTitleSprite->setColor(Color3B::RED);
    m_pReturnTitleSprite->setPosition(Vec2(400,400));
    this->addChild(m_pReturnTitleSprite);

    m_pReturnGameSprite = Sprite::create();
    m_pReturnGameSprite->setTextureRect(Rect(0,0,100,100));
    m_pReturnGameSprite->setColor(Color3B::BLUE);
    m_pReturnGameSprite->setPosition(Vec2(400,800));
    this->addChild(m_pReturnGameSprite);

    return true;
}

//================================================================================
// ゲーム終了処理
//================================================================================
void PauseScene::menuCloseCallback(Ref* pSender)
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
// ポーズ更新
//================================================================================
void PauseScene::update(float fTime)
{

}

//================================================================================
// タップ開始判定
//================================================================================
bool PauseScene::onTouchBegin(Touch* pTouch,Event* pEvent)
{
    // タッチ座標の取得
    m_touchPos = pTouch->getLocation();

    Rect returnGameSpriteRect = m_pReturnGameSprite->getBoundingBox();
    if(returnGameSpriteRect.containsPoint(m_touchPos))
    {
        returnGame();
        return true;
    }

    Rect retryGameSpriteRect = m_pRetryGameSprite->getBoundingBox();
    if(retryGameSpriteRect.containsPoint(m_touchPos))
    {
        retryGame();
        return true;
    }

    Rect returnTitleSpriteRect = m_pReturnTitleSprite->getBoundingBox();
    if(returnTitleSpriteRect.containsPoint(m_touchPos))
    {
        returnTitle();
        return true;
    }

    return true;
}

//================================================================================
// スワイプ判定
//================================================================================
void PauseScene::onTouchMoved(Touch* pTouch,Event* pEvent)
{

    // タッチ座標の取得
    m_touchPos = pTouch->getLocation();


}

//================================================================================
// タップ離した判定
//================================================================================
void PauseScene::onTouchEnded(Touch* pTouch, Event* pEvent)
{

}

//================================================================================
// タッチ時に割り込み処理
//================================================================================
void PauseScene::onTouchCancelled(Touch* pTouch, Event* pEvent)
{
    
}

//================================================================================
// ゲームやり直し処理
//================================================================================
void PauseScene::retryGame(void)
{
    this->getEventDispatcher()->removeAllEventListeners();
    this->removeAllChildren();
    this->unscheduleUpdate();

    Director::getInstance()->replaceScene(TransitionFade::create(1.0f,GameMainScene::createScene(),Color3B::WHITE));
}

//================================================================================
// ゲーム再開処理
//================================================================================
void PauseScene::returnGame(void)
{
    this->getEventDispatcher()->removeEventListener(m_pTouchEventOneByOne);
    this->removeAllChildren();
    this->unscheduleUpdate();

    Node* pParent = static_cast<Node*>(this->getParent());
    pParent->removeChild(this);
    pParent->resume();
}

//================================================================================
// タイトルバック処理
//================================================================================
void PauseScene::returnTitle(void)
{
    this->getEventDispatcher()->removeAllEventListeners();
    this->removeAllChildren();
    this->unscheduleUpdate();

    Director::getInstance()->replaceScene(TransitionFade::create(1.0f,TitleScene::createScene(),Color3B::WHITE));
}
