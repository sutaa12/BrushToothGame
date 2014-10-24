//
//  LifeBar.cpp
//  LifeBarBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/15.
//
//
//********************************************************************************
// インクルード
//********************************************************************************
#include "TextureFile.h"
#include "Sound.h"
#include "LifeBar.h"
#include "GameMainScene.h"
float LifeBar::m_nLife = 0;
//================================================================================
// コンストラクタ
//================================================================================
LifeBar::LifeBar(void)
{
    // メンバ変数の初期化
    m_pSprite = nullptr;
    m_pBackLifeBar = nullptr;
    m_pProgressTimer = nullptr;
    m_nLife = 100.0f;
}

//================================================================================
// デストラクタ
//================================================================================
LifeBar::~LifeBar()
{
    
}

//================================================================================
// 初期化処理
//================================================================================
bool LifeBar::init(void)
{

    m_nStartTimer = m_nCurrentTime = m_nTimer = 0;
    m_nStartTimer = m_nCurrentTime = GAME_TIME_MAX;
    // スプライトの作成
    m_pSprite = Sprite::create(TEX_HP_BAR);
    m_pBackLifeBar = Sprite::create(TEX_HP_BAR);
    
    // エラーチェック
    if(m_pSprite == nullptr)
    {
        // スプライト生成エラー
        return false;
    }
    
    // スプライトの座標設定
    m_pSprite->setPosition(m_pos);
    m_pBackLifeBar->setPosition(m_pos);
    m_pBackLifeBar->setColor(Color3B(100, 100, 100));
    m_nLife = 100;

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

    //パーセント表示用テキスト
    m_pPercentTxt = LabelTTF::create("0%", "Arial", 35);
    m_pPercentTxt->setPosition(ccp(m_pProgressTimer->getPositionX(), m_pProgressTimer->getPositionY()+50));
    m_pPercentTxt->setTag(200);
    m_pLayer->addChild(m_pPercentTxt);
    
    m_pLayer->addChild(m_pProgressTimer);
    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void LifeBar::uninit(void)
{
    
}

//================================================================================
// 更新処理
//================================================================================
void LifeBar::update(void)
{
    m_nTimer ++;
    if(m_nTimer % 60 == 0){
        m_nCurrentTime --;
    }
    m_nLife =( (float)m_nCurrentTime / m_nStartTimer) * 100.0f;

    m_pProgressTimer->setPercentage(m_nLife);

    //0になったら停止
    if(m_nLife < 0)
    {
        m_nLife = 0;
    }
    String* points = String::createWithFormat( "%d秒", (int)m_nCurrentTime);

    // スコアポイントの表示を更新
    m_pPercentTxt->setString(points->getCString());

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
LifeBar* LifeBar::create(Layer* layer,const Vec2& pos)
{
    // インスタンスの生成
    LifeBar* pLifeBar = new LifeBar();
    pLifeBar->m_pLayer = layer;
    // メンバ変数の代入
    pLifeBar->m_pos = pos;
    
    // 初期化
    pLifeBar->init();
    
    return pLifeBar;
}