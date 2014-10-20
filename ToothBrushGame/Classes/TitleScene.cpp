//
//  TitleScene.cpp
//  ToothBrushGame
//
//  Created by 鈴木愛忠 on 2014/10/20.
//
//

#include "TitleScene.h"
#include "GameMainScene.h"
USING_NS_CC;
//================================================================================
// シーン生成
//================================================================================

Scene* TitleScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TitleScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

//================================================================================
// シーン初期化
//================================================================================
// on "init" you need to initialize your instance
bool TitleScene::init()
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
                                           CC_CALLBACK_1(TitleScene::menuCloseCallback, this));
    
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
    m_pTouchEventOneByOne->onTouchBegan = CC_CALLBACK_2(TitleScene::onTouchBegin,this);
    m_pTouchEventOneByOne->onTouchMoved = CC_CALLBACK_2(TitleScene::onTouchMoved,this);
    m_pTouchEventOneByOne->onTouchCancelled = CC_CALLBACK_2(TitleScene::onTouchCancelled, this);
    m_pTouchEventOneByOne->onTouchEnded = CC_CALLBACK_2(TitleScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithFixedPriority(m_pTouchEventOneByOne, 100);
    return true;
}

//================================================================================
// ゲーム終了処理
//================================================================================

void TitleScene::menuCloseCallback(Ref* pSender)
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
void TitleScene::update(float fTime)
{
 
}

//================================================================================
// タップ開始判定
//================================================================================

bool TitleScene::onTouchBegin(Touch* pTouch,Event* pEvent)
{
    // タッチ座標の取得
    m_touchPos = pTouch->getLocation();

    this->getEventDispatcher()->removeAllEventListeners();
    this->removeAllChildren();
    
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f,GameMainScene::createScene(),Color3B::WHITE));

    return true;
}

//================================================================================
// スワイプ判定
//================================================================================

void TitleScene::onTouchMoved(Touch* pTouch,Event* pEvent)
{
    
    // タッチ座標の取得
    m_oldTouchPos = m_touchPos;
    m_touchPos = pTouch->getLocation();
}

//================================================================================
// タップ離した判定
//================================================================================

void TitleScene::onTouchEnded(Touch* pTouch, Event* pEvent)
{

}

//================================================================================
// タッチ時に割り込み処理
//================================================================================
void TitleScene::onTouchCancelled(Touch* pTouch, Event* pEvent)
{
    
}

