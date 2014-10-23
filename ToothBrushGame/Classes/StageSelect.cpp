//********************************************************************************
//  StageSelect.cpp
//  ToothBrushGame
//
//  Created by 丸山 潤 on 2014/10/21.
//
//********************************************************************************
//********************************************************************************
// インクルード
//********************************************************************************
#include "StageSelect.h"
#include "GameMainScene.h"

//********************************************************************************
// 名前空間の使用
//********************************************************************************
USING_NS_CC;

//================================================================================
// デストラクタ
//================================================================================
StageSelect::~StageSelect()
{
    for(int nCnt = 0;nCnt < m_nStageNum;nCnt++)
    {
        //delete m_ppStageSprites[nCnt];
    }

    delete[] m_ppStageSprites;

}

//================================================================================
// レイヤー生成
//================================================================================
Layer* StageSelect::createLayer(int nStageMax)
{
    auto layer = StageSelect::create();
    layer->m_nStageNum = nStageMax;

    layer->createStageSprites();

    return layer;
}

//================================================================================
// シーン初期化
//================================================================================
bool StageSelect::init()
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
                                           CC_CALLBACK_1(StageSelect::menuCloseCallback, this));

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
    m_pTouchEventOneByOne->onTouchBegan = CC_CALLBACK_2(StageSelect::onTouchBegin,this);
    m_pTouchEventOneByOne->onTouchMoved = CC_CALLBACK_2(StageSelect::onTouchMoved,this);
    m_pTouchEventOneByOne->onTouchCancelled = CC_CALLBACK_2(StageSelect::onTouchCancelled, this);
    m_pTouchEventOneByOne->onTouchEnded = CC_CALLBACK_2(StageSelect::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithFixedPriority(m_pTouchEventOneByOne, 10);

    // 薄暗いスプライトを作成
    m_pMaskSprite = Sprite::create();
    m_pMaskSprite->setTextureRect(Rect(0,0,visibleSize.width,visibleSize.height));
    m_pMaskSprite->setColor(Color3B::BLACK);
    m_pMaskSprite->setOpacity(125);
    m_pMaskSprite->setPosition(Vec2(visibleSize.width / 2,visibleSize.height / 2));
    this->addChild(m_pMaskSprite);

    return true;
}

//================================================================================
// ゲーム終了処理
//================================================================================
void StageSelect::menuCloseCallback(Ref* pSender)
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
void StageSelect::update(float fTime)
{

}

void StageSelect::createStageSprites(void)
{
    m_ppStageSprites = new Sprite*[m_nStageNum];

    for(int nCnt = 0;nCnt < m_nStageNum;nCnt++)
    {
        m_ppStageSprites[nCnt] = Sprite::create();
    }
}

//================================================================================
// タップ開始判定
//================================================================================
bool StageSelect::onTouchBegin(Touch* pTouch,Event* pEvent)
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
void StageSelect::onTouchMoved(Touch* pTouch,Event* pEvent)
{

    // タッチ座標の取得
    m_touchPos = pTouch->getLocation();


}

//================================================================================
// タップ離した判定
//================================================================================
void StageSelect::onTouchEnded(Touch* pTouch, Event* pEvent)
{

}

//================================================================================
// タッチ時に割り込み処理
//================================================================================
void StageSelect::onTouchCancelled(Touch* pTouch, Event* pEvent)
{
    
}