//
//  DetailScore.cpp
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/27.
//
//

#include "DetailScore.h"
#include "AchievementDataBase.h"
//================================================================================
// コンストラクタ
//================================================================================
DetailScore::DetailScore(void)
{
    // メンバ変数の初期化
    m_pLayer = nullptr;
}

//================================================================================
// デストラクタ
//================================================================================
DetailScore::~DetailScore()
{
    
}

//================================================================================
// 初期化処理
//================================================================================
bool DetailScore::init(void)
{
    
    
    //左上の位置に設定
    m_pDetailScoreLabel->setPosition(m_startLeftTopPos);
    
    // スコアポイント
    m_pPointLabel = LabelTTF::create("0", "ariel", 24);
    String* points = String::createWithFormat( "%d", m_nPoint);
    
    //DetailScore文字の一番後ろの位置にセット
    m_pPointLabel->setPosition(Vec2(m_startLeftTopPos.x + m_pDetailScoreLabel->getContentSize().width, m_startLeftTopPos.y));
    m_pPointLabel->setString(points->getCString());
    
    
    m_pLayer->addChild(m_pPointLabel);
    m_pLayer->addChild(m_pDetailScoreLabel);
    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void DetailScore::uninit(void)
{
    
}

//================================================================================
// 更新処理
//================================================================================
void DetailScore::update(void)
{
}

//================================================================================
// 生成処理
//================================================================================
DetailScore* DetailScore::create(const Vec2& startLeftTopPos,char* DetailName,int m_nPoint,Layer* layer)
{
    // 歯マネージャーのインスタンス化
    DetailScore* pDetailScore = new DetailScore();
    
    // メンバー変数の代入
    pDetailScore->m_startLeftTopPos = startLeftTopPos;
    pDetailScore->m_pLayer = layer;
    pDetailScore->m_nPoint = m_nPoint;
    // DetailScore　文字列
    pDetailScore->m_pDetailScoreLabel = LabelTTF::create(DetailName, "ariel", 24);

    // 初期化
    pDetailScore->init();
    
    return pDetailScore;
}