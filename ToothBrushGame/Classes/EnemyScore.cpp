//
//  EnemyScore.cpp
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/29.
//
//
// インクルード
#include "EnemyScore.h"
#include "Number.h"
#include "TextureFile.h"
#include "Enemy.h"
int EnemyScore::m_nEnemyScorePoint = 0;

//================================================================================
// コンストラクタ
//================================================================================
EnemyScore::EnemyScore(void)
{
    // メンバ変数の初期化
    m_ppNumbers = nullptr;
    m_pLayer = nullptr;
}

//================================================================================
// デストラクタ
//================================================================================
EnemyScore::~EnemyScore()
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
bool EnemyScore::init(void)
{
    m_pEnemyIcon = Sprite::create(m_pTexName);
    m_pEnemyIcon->setScale(0.5f, 0.5f);
    //左上の位置に設定
    m_pEnemyIcon->setPosition(m_startLeftTopPos);
    
    // スコアポイント
    m_pPointLabel = LabelTTF::create("0", "ariel", 48);
    //SCORE文字の一番後ろの位置にセット
    m_pPointLabel->setPosition(Vec2(m_startLeftTopPos.x + m_pEnemyIcon->getContentSize().width, m_startLeftTopPos.y));
    String* points = String::createWithFormat( " × %d", this->m_nEnemyScorePoint);
    
    // スコアポイントの表示を更新
    m_pPointLabel->setString(points->getCString());
    m_pPointLabel->setColor(Color3B::BLACK);
    m_pLayer->addChild(m_pPointLabel);
    m_pLayer->addChild(m_pEnemyIcon);
    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void EnemyScore::uninit(void)
{
    
}

//================================================================================
// 更新処理
//================================================================================
void EnemyScore::update(void)
{
    String* points = String::createWithFormat( " × %d",Enemy::getEnemyAllDownNum());
    
    // スコアポイントの表示を更新
    m_pPointLabel->setString(points->getCString());
    
}

//================================================================================
// 生成処理
//================================================================================
EnemyScore* EnemyScore::create(const Vec2& startLeftTopPos,char* pTexName,Layer* layer,int nEnemyScore)
{
    // 歯マネージャーのインスタンス化
    EnemyScore* pEnemyScore = new EnemyScore();
    
    // メンバー変数の代入
    pEnemyScore->m_startLeftTopPos = startLeftTopPos;
    pEnemyScore->m_pLayer = layer;
    pEnemyScore->m_pTexName = pTexName;
    m_nEnemyScorePoint = nEnemyScore;
    // 初期化
    pEnemyScore->init();
    
    return pEnemyScore;
}
