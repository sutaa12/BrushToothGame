//
//  CountDown.cpp
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/20.
//
//

// インクルード
#include "CountDown.h"
#include "Score.h"
#include "Number.h"
#include "HitChecker.h"
#include "PauseScene.h"

static const int COUNTDOWN_DISPLAY_CENTER_X = (320);

//================================================================================
// コンストラクタ
//================================================================================
CountDown::CountDown(void)
{
    // メンバ変数の初期化
    m_pNumber = nullptr;
}

//================================================================================
// デストラクタ
//================================================================================
CountDown::~CountDown()
{
    delete m_pNumber;
}

//================================================================================
// 初期化処理
//================================================================================
bool CountDown::init(void)
{
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 更新処理の追加
    this->scheduleUpdate();

    // タッチ機能の有効化
    m_pTouchEventOneByOne =  EventListenerTouchOneByOne::create();
    m_pTouchEventOneByOne->setSwallowTouches(false);
    m_pTouchEventOneByOne->onTouchBegan = CC_CALLBACK_2(CountDown::onTouchBegin,this);
    m_pTouchEventOneByOne->onTouchMoved = CC_CALLBACK_2(CountDown::onTouchMoved,this);
    m_pTouchEventOneByOne->onTouchCancelled = CC_CALLBACK_2(CountDown::onTouchCancelled, this);
    m_pTouchEventOneByOne->onTouchEnded = CC_CALLBACK_2(CountDown::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithFixedPriority(m_pTouchEventOneByOne, 10);

    // 薄暗いスプライトを作成
    m_pMaskSprite = Sprite::create();
    m_pMaskSprite->setTextureRect(Rect(0,0,visibleSize.width,visibleSize.height));
    m_pMaskSprite->setColor(Color3B::BLACK);
    m_pMaskSprite->setOpacity(125);
    m_pMaskSprite->setPosition(Vec2(visibleSize.width / 2,visibleSize.height / 2));
    this->addChild(m_pMaskSprite);

    /*  スコアを画像で表示するときに使う
     m_ppNumbers = new Number*[m_nMaxNumber];
     for(int nloop = 0;nloop < m_nMaxNumber;nloop++)
     {
     // 上歯茎生成
     m_ppNumbers[nloop] = Number::create();

     // スプライトサイズ取得
     Rect numgerRect = (m_ppNumbers[nloop]->getSprite()->getBoundingBox());

     // 座標変換(左上を持ってきているため、中心にそろえる処理)
     m_ppNumbers[nloop]->setPos(Vec2(Score_DISPLAY_CENTER_X,
     m_startLeftTopPos.y - (numgerRect.size.height / 2)));

     // スプライトの再配置
     m_ppNumbers[nloop]->refreshSpritePos();

     // スプライトの登録
     m_pLayer->addChild(m_ppNumbers[nloop]->getSprite());
     }
     */

    // SCORE　文字列
    m_pNumLabel = Label::createWithSystemFont("100", "ariel", 128);
    m_pNumLabel->setColor(Color3B::WHITE);
    m_pNumLabel->enableOutline(Color4B::BLACK,5);
    m_pNumLabel->setPosition(visibleSize.width / 2,visibleSize.height / 2);
    this->addChild(m_pNumLabel);

    m_nTimer = 0;
    m_bEnd = false;

    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void CountDown::uninit(void)
{
    this->getEventDispatcher()->removeEventListener(m_pTouchEventOneByOne);
    this->removeAllChildren();
    this->unscheduleUpdate();

    Scene* pParent = static_cast<Scene*>(this->getParent());
    pParent->removeChild(this);
    pParent->resume();
}

//================================================================================
// 更新処理
//================================================================================
void CountDown::update(float fTime)
{
    if(m_nTimer % 15 == 0)
    {
        if(m_bEnd == true)
        {
            uninit();
            return;
        }

        auto pNumString = StringUtils::format("%d", this->m_nNum);
        m_pNumLabel->setString(pNumString.c_str());

        m_nNum--;

        if(m_nNum < 0)
        {
            m_pNumLabel->setString("start!");
            m_bEnd = true;
        }
    }

    m_pTouchEventOneByOne->setSwallowTouches(true);

    m_nTimer++;
}

//================================================================================
// 生成処理
//================================================================================
CountDown* CountDown::create(const Vec2& startLeftTopPos,int nCountDownNum)
{
    // カウントダウンのインスタンス化
    CountDown* pCountDown = new CountDown();

    pCountDown->m_startLeftTopPos = startLeftTopPos;
    pCountDown->m_nNum = nCountDownNum;

    // 初期化
    pCountDown->init();

    return pCountDown;
}

Layer* CountDown::createLayer(int nCountDownNum,HitChecker* pHitChecker)
{
    auto layer = CountDown::create();

    layer->m_nNum = nCountDownNum;
    layer->m_pHitChecker = pHitChecker;

    return layer;
}

//================================================================================
// タップ開始判定
//================================================================================
bool CountDown::onTouchBegin(Touch* pTouch,Event* pEvent)
{
    if(m_pHitChecker->checkTapOnMenuBar(pTouch->getLocation()))
    {
        m_pTouchEventOneByOne->setSwallowTouches(false);
        this->addChild(PauseScene::createLayer());
        this->pause();
        return true;
    }

    return true;
}

//================================================================================
// スワイプ判定
//================================================================================
void CountDown::onTouchMoved(Touch* pTouch,Event* pEvent)
{
}

//================================================================================
// タップ離した判定
//================================================================================
void CountDown::onTouchEnded(Touch* pTouch, Event* pEvent)
{

}

//================================================================================
// タッチ時に割り込み処理
//================================================================================
void CountDown::onTouchCancelled(Touch* pTouch, Event* pEvent)
{
    
}
