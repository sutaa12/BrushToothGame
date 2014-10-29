//
//  RankObject.cpp
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/21.
//
//

#include "RankObject.h"
#include "common.h"
//================================================================================
// コンストラクタ
//================================================================================
RankObject::RankObject(void)
{
    // メンバ変数の初期化
    m_pLayer = nullptr;
}

//================================================================================
// デストラクタ
//================================================================================
RankObject::~RankObject()
{

}

//================================================================================
// 初期化処理
//================================================================================
bool RankObject::init(void)
{
  
    
    // RankObject　文字列
    m_pRankObjectLabel = LabelTTF::create("らんく", MIKA_FONT, 48);
    //左上の位置に設定
    m_pRankObjectLabel->setPosition(m_startLeftTopPos);
    
    // スコアポイント
    m_pPointLabel = LabelTTF::create("0",MIKA_FONT, 96);
    String* points = String::createWithFormat( "%s", this->m_cRankObjectRank);
    
    //RankObject文字の一番後ろの位置にセット
    m_pPointLabel->setPosition(Vec2(m_startLeftTopPos.x + m_pRankObjectLabel->getContentSize().width - 10, m_startLeftTopPos.y));
    m_pPointLabel->setString(points->getCString());
    
    m_pLayer->addChild(m_pPointLabel);
    m_pLayer->addChild(m_pRankObjectLabel);
    m_pPointLabel->enableStroke(Color3B::BLACK, 8.0f);
    m_pRankObjectLabel->enableStroke(Color3B::BLACK, 8.0f);
    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void RankObject::uninit(void)
{
    
}

//================================================================================
// 更新処理
//================================================================================
void RankObject::update(void)
{
}

//================================================================================
// 生成処理
//================================================================================
RankObject* RankObject::create(const Vec2& startLeftTopPos,char* cRank,Layer* layer)
{
    // 歯マネージャーのインスタンス化
    RankObject* pRankObject = new RankObject();
    
    // メンバー変数の代入
    pRankObject->m_startLeftTopPos = startLeftTopPos;
    pRankObject->m_pLayer = layer;
    pRankObject->m_cRankObjectRank = cRank;
    // 初期化
    pRankObject->init();
    
    return pRankObject;
}