//********************************************************************************
//  ConfigScene.cpp
//  ToothBrushGame
//
//  Created by 丸山 潤 on 2014/10/27.
//
//********************************************************************************
//********************************************************************************
// インクルード
//********************************************************************************
#include "ConfigScene.h"
#include "common.h"
#include "TextureFile.h"

//********************************************************************************
// 静的メンバ変数宣言
//********************************************************************************
float ConfigScene::m_fShakePermissionDistance = 5.0f;

//================================================================================
// コンストラクタ
//================================================================================
ConfigScene::ConfigScene()
{
}

//================================================================================
// デストラクタ
//================================================================================
ConfigScene::~ConfigScene()
{
}

//================================================================================
// シーン生成
//================================================================================
Scene* ConfigScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = ConfigScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

//================================================================================
// 初期化処理
//================================================================================
bool ConfigScene::init(void)
{
    if( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize() / 2 + SCREEN_CENTER;
    Vec2 origin = Director::getInstance()->getVisibleSize() / 2 - SCREEN_CENTER;

    //終了ボタン生成
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(ConfigScene::menuCloseCallback, this));

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
    m_pTouchEventOneByOne->onTouchBegan = CC_CALLBACK_2(ConfigScene::onTouchBegin,this);
    m_pTouchEventOneByOne->onTouchMoved = CC_CALLBACK_2(ConfigScene::onTouchMoved,this);
    m_pTouchEventOneByOne->onTouchCancelled = CC_CALLBACK_2(ConfigScene::onTouchCancelled, this);
    m_pTouchEventOneByOne->onTouchEnded = CC_CALLBACK_2(ConfigScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithFixedPriority(m_pTouchEventOneByOne, 1);

    // シェイク感度のラベル生成
    m_pShakeStatementLabel = Label::createWithSystemFont("シェイクの感度 低1~10高", "ariel", 16);
    m_pShakeStatementLabel->setColor(Color3B::WHITE);
    m_pShakeStatementLabel->enableOutline(Color4B::BLACK,5);
    m_pShakeStatementLabel->setPosition(visibleSize.width / 2,visibleSize.height / 2);
    this->addChild(m_pShakeStatementLabel);

    // シェイク感度数値のラベル生成
    auto pNumString = StringUtils::format("%.2f", this->m_fShakePermissionDistance);
    m_pShakeNumLabel = Label::createWithSystemFont(pNumString.c_str(), "ariel", 16);
    m_pShakeNumLabel->setColor(Color3B::WHITE);
    m_pShakeNumLabel->enableOutline(Color4B::BLACK,5);
    m_pShakeNumLabel->setPosition(visibleSize.width / 2,visibleSize.height / 2 - 100);
    this->addChild(m_pShakeNumLabel);

    // シェイク感度上昇矢印の生成
    Vec2 workPos = visibleSize / 2;
    m_pShakeUpArrowImage = MenuItemImage::create(TEX_PLAQUE_WAIT_01,TEX_PLAQUE_WAIT_01,
                                                 CC_CALLBACK_0(ConfigScene::shakeUpArrowCallback,this));
    m_pShakeUpArrowImage->setPosition(visibleSize.width / 2 + 100,visibleSize.height / 2 - 100);

    // シェイク感度低下矢印の生成
    Rect arrowImageRect = m_pShakeUpArrowImage->getBoundingBox();
    workPos += arrowImageRect.size / 2;
    m_pShakeDownArrowImage = MenuItemImage::create(TEX_PLAQUE_WAIT_01,TEX_PLAQUE_WAIT_01,
                                                   CC_CALLBACK_0(ConfigScene::shakeDownArrowCallback,this));
    m_pShakeDownArrowImage->setPosition(visibleSize.width / 2 - 100,visibleSize.height / 2 - 100);

    // シェイク感度変更矢印のメニュー登録
    Menu* pShakeArrowMenu = Menu::create(m_pShakeUpArrowImage,m_pShakeDownArrowImage, NULL);
    pShakeArrowMenu->setPosition(Vec2::ZERO);
    this->addChild(pShakeArrowMenu);

    // コンフィグ終了ボタンの生成
    m_pConfigCloseImage = MenuItemImage::create("ButtonReturnGame.png","ButtonReturnGame.png",
                                                CC_CALLBACK_0(ConfigScene::configCloseCallback, this));
    m_pConfigCloseImage->setPosition(Vec2(visibleSize.width / 2,origin.y));

    // コンフィグ終了メニュー登録
    Menu* pConfigCloseMenu = Menu::create(m_pConfigCloseImage,NULL);
    pConfigCloseMenu->setPosition(Vec2::ZERO);
    this->addChild(pConfigCloseMenu);

    return true;
}

//================================================================================
// 更新処理
//================================================================================
void ConfigScene::update(float fTime)
{
}

//================================================================================
// ゲーム終了処理
//================================================================================
void ConfigScene::menuCloseCallback(Ref* pSender)
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
// タップ開始判定
//================================================================================
bool ConfigScene::onTouchBegin(Touch* pTouch,Event* pEvent)
{
    // タッチ座標の取得
    m_touchPos = pTouch->getLocation();

    return true;
}

//================================================================================
// スワイプ判定
//================================================================================
void ConfigScene::onTouchMoved(Touch* pTouch,Event* pEvent)
{
    // タッチ座標の取得
    m_oldTouchPos = m_touchPos;
    m_touchPos = pTouch->getLocation();
}

//================================================================================
// タップ離した判定
//================================================================================
void ConfigScene::onTouchEnded(Touch* pTouch, Event* pEvent)
{

}

//================================================================================
// タッチ時に割り込み処理
//================================================================================
void ConfigScene::onTouchCancelled(Touch* pTouch, Event* pEvent)
{
    
}

//================================================================================
// シェイク感度上昇コールバック
//================================================================================
void ConfigScene::shakeUpArrowCallback(void)
{
    m_fShakePermissionDistance += 0.1f;
    shakeNumlabelRefresh();
}

//================================================================================
// シェイク感度低下コールバック
//================================================================================
void ConfigScene::shakeDownArrowCallback(void)
{
    if(m_fShakePermissionDistance <= 0.1f)
    {
        return;
    }
    m_fShakePermissionDistance -= 0.1f;
    shakeNumlabelRefresh();
}

//================================================================================
// シェイク数値ラベルリフレッシュ処理
//================================================================================
void ConfigScene::shakeNumlabelRefresh(void)
{
    auto pNumString = StringUtils::format("%.2f", this->m_fShakePermissionDistance);
    m_pShakeNumLabel->setString(pNumString.c_str());
}

//================================================================================
// コンフィグ終了コールバック
//================================================================================
void ConfigScene::configCloseCallback(void)
{
    this->getEventDispatcher()->removeEventListener(m_pTouchEventOneByOne);
    this->removeAllChildren();
    this->unscheduleUpdate();
    
    Director::getInstance()->popScene();
}
