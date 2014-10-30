//
//  Clock.cpp
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/28.
//
//

//********************************************************************************
// インクルード
//********************************************************************************
#include "TextureFile.h"
#include "Sound.h"
//#include "LifeBar.h"
#include "Clock.h"
#include "GameMainScene.h"

float m_nClock = 0;
//================================================================================
// コンストラクタ
//================================================================================
Clock::Clock(void)
{
    // メンバ変数の初期化
    m_pSprite = nullptr;
    m_pBackLifeBar = nullptr;
    m_pProgressTimer = nullptr;
    m_nClock = 100.0f;
    m_bStop = false;
}

//================================================================================
// デストラクタ
//================================================================================
Clock::~Clock()
{

}

//================================================================================
// 初期化処理
//================================================================================
bool Clock::init(void)
{

    m_nStartTimer = m_nCurrentTime = m_nTimer = 0;
    m_nStartTimer = m_nCurrentTime = GAME_TIME_MAX;
    // スプライトの作成
//    m_pSprite = Sprite::create(TEX_HP_BAR);
 //   m_pBackLifeBar = Sprite::create(TEX_HP_BAR);

    m_bSudden = false;

    // スプライトの座標設定
    m_pSprite = Sprite::create(TEX_CLOCK_2);
    m_pSprite->setPosition(m_pos);
    m_pLayer->addChild(m_pSprite);
  //  m_pBackLifeBar->setPosition(m_pos);
  //  m_pBackLifeBar->setColor(Color3B(100, 100, 100));
    m_nClock = 100;

    /*
    m_pLayer->addChild(m_pBackLifeBar);
    //タイマー作成
    m_pProgressTimer = ProgressTimer::create(m_pSprite);

    //最初は0パーセント
    m_pProgressTimer->setPercentage(0);

    //タイマーの形（棒状に設定）
    m_pProgressTimer->setType(ProgressTimer::Type::BAR);

    //バーの伸びる方向（x方向に設定）
    m_pProgressTimer->setBarChangeRate(Point(1, 0));

    //タイマーの基準点（左側に設定）
    m_pProgressTimer->setMidpoint(Point(0, 0));

    //タイマーを配置
    m_pProgressTimer->setPosition(m_pos);
    m_pProgressTimer->setTag(100);
*/
    //パーセント表示用テキスト
    m_pPercentTxt = LabelTTF::create("0秒", "Arial", 35);
    m_pPercentTxt->setPosition(Vec2(m_pSprite->getPosition().x + m_pSprite->getContentSize().width, m_pSprite->getPosition().y));
    m_pPercentTxt->setTag(200);
    m_pLayer->addChild(m_pPercentTxt);

    //m_pLayer->addChild(m_pProgressTimer);
    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void Clock::uninit(void)
{

}

//================================================================================
// 更新処理
//================================================================================
void Clock::update(void)
{
    if(!m_bStop)
    {
        m_nTimer ++;
        if(m_nTimer % 60 == 0){
            m_nCurrentTime --;
        }
        //m_nClock =( (float)m_nCurrentTime / m_nStartTimer) * 100.0f;

        //m_pProgressTimer->setPercentage(m_nClock);

        //残り１０秒になったらサドンデス
        if (getColockNow() == 10 && m_bSudden == false)
        {

            //画像をきり替え
            m_pSprite->setColor(Color3B::RED);
    //        m_pSprite->setTexture(TEX_CLOCK_2_RED);


      //      m_pLayer->addChild(m_pSprite);

            SimpleAudioEngine::getInstance()->setEffectsVolume(SE_VOLUME_HALF);
            SimpleAudioEngine::getInstance()->playEffect(SE_TIME_REMAIND_1);
            m_bSudden = true;
        }

        if (getColockNow() <= 10)
        {
            if (getColockNow() %2 == 0)
            {
                m_pSprite->setColor(Color3B::RED);
                m_pPercentTxt->setColor(Color3B::RED);
            } else {
                m_pSprite->setColor(Color3B::WHITE);
                m_pPercentTxt->setColor(Color3B::WHITE);
            }
        }

        //0になったら停止
        if(m_nClock < 0)
        {
            m_nClock = 0;
        }

        String* points = String::createWithFormat( "%d秒", (int)m_nCurrentTime);

        // スコアポイントの表示を更新
        m_pPercentTxt->setString(points->getCString());
    }

}


/*
 //================================================================================
 // HP変更処理
 //================================================================================
 void LifeBar::addLife(int num)
 {
 m_nLife += num;
 if(m_nLife > 100)
 {
 m_nLife = 100;
 }else
 if(m_nLife < 0)
 {
 m_nLife = 0;
 }
 }*/

//================================================================================
// 生成処理
//================================================================================
Clock* Clock::create(Layer* layer,const Vec2& pos)
{
    // インスタンスの生成
    Clock* pClock = new Clock();
    pClock->m_pLayer = layer;
    // メンバ変数の代入
    pClock->m_pos = pos;

    // 初期化
    pClock->init();

    return pClock;
}