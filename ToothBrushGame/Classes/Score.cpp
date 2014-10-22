//
//  Score.cpp
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/15.
//
//

//********************************************************************************
// インクルード
#include "Score.h"
#include "Number.h"

int Score::m_nScorePoint = 0;

//================================================================================
// コンストラクタ
//================================================================================
Score::Score(void)
{
    // メンバ変数の初期化
    m_ppNumbers = nullptr;
    m_pLayer = nullptr;
    m_nMaxNumber = 0;
}

//================================================================================
// デストラクタ
//================================================================================
Score::~Score()
{
    if(m_ppNumbers)
    {
        delete[] m_ppNumbers;
        m_ppNumbers = nullptr;
    }
}

//================================================================================
// 初期化処理
//================================================================================
bool Score::init(void)
{
    // SCORE　文字列
    m_pScoreLabel = LabelTTF::create("SCORE", "ariel", 48);
    //左上の位置に設定
    m_pScoreLabel->setPosition(m_startLeftTopPos);

    // スコアポイント
    m_pPointLabel = LabelTTF::create("0", "ariel", 48);
    //SCORE文字の一番後ろの位置にセット
    m_pPointLabel->setPosition(Vec2(m_startLeftTopPos.x + m_pScoreLabel->getContentSize().width, m_startLeftTopPos.y));
    String* points = String::createWithFormat( "%d", this->m_nScorePoint);
    
    // スコアポイントの表示を更新
    m_pPointLabel->setString(points->getCString());

    m_pLayer->addChild(m_pPointLabel);
    m_pLayer->addChild(m_pScoreLabel);
    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void Score::uninit(void)
{
    
}

//================================================================================
// 更新処理
//================================================================================
void Score::update(void)
{

    String* points = String::createWithFormat( "%d", this->m_nScorePoint);

    // スコアポイントの表示を更新
    m_pPointLabel->setString(points->getCString());

}

//================================================================================
// 生成処理
//================================================================================
Score* Score::create(const Vec2& startLeftTopPos,int nMaxNumber,Layer* layer,int nScore)
{
    // 歯マネージャーのインスタンス化
    Score* pScore = new Score();
    
    // メンバー変数の代入
    pScore->m_startLeftTopPos = startLeftTopPos;
    pScore->m_pLayer = layer;
    pScore->m_nMaxNumber = nMaxNumber;
    m_nScorePoint = nScore;
    // 初期化
    pScore->init();
    
    return pScore;
}
