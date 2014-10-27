//
//  RankManager.cpp
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/21.
//
//

//********************************************************************************
// インクルード
#include "common.h"
#include "RankManager.h"
#include "RankObject.h"
#include "Score.h"
#include "DetailScore.h"

//================================================================================
// コンストラクタ
//================================================================================
RankManager::RankManager(void)
{
    // メンバ変数の初期化
    m_pLayer = nullptr;
    //スコア数字初期化
    m_nRankManagerPoint = 0;

}

//================================================================================
// デストラクタ
//================================================================================
RankManager::~RankManager()
{
    SAFE_DELETE(m_pScore);
    SAFE_DELETE(m_pRankObject);
}

//================================================================================
// 初期化処理
//================================================================================
bool RankManager::init(void)
{
    m_pTimeScore = DetailScore::create(Vec2(0,0),0,0,0);
    const char cRank[RANK_MAX]=
    {
        'S','A','B','C','D'
    };
    m_pScore = Score::create(Vec2(m_startLeftTopPos.x,m_startLeftTopPos.y), m_nRankManagerPoint,m_pLayer,m_nRankManagerPoint);
    int nNum = RANK_D;
    if(m_nRankManagerPoint <= SCORE_RANK_D)
    {
        nNum = RANK_D;
    }else
        if(m_nRankManagerPoint <= SCORE_RANK_C)
        {
            nNum = RANK_C;
        }else
            if(m_nRankManagerPoint <= SCORE_RANK_B)
            {
                nNum = RANK_B;
            }else
                if(m_nRankManagerPoint <= SCORE_RANK_A)
                {
                    nNum = RANK_A;
                }else{
                    nNum = RANK_S;
                }
    m_pRankObject = RankObject::create(Vec2(m_pScore->getPoint()->getPosition().x +m_pScore->getPoint()->getContentSize().width + 100,m_startLeftTopPos.y), cRank[nNum], m_pLayer);
    
    
    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void RankManager::uninit(void)
{
    
}

//================================================================================
// 更新処理
//================================================================================
void RankManager::update(void)
{
}

//================================================================================
// 生成処理
//================================================================================
RankManager* RankManager::create(const Vec2& startLeftTopPos,int nRankScore,Layer* layer)
{
    RankManager* pRankManager = new RankManager();
    
    // メンバー変数の代入
    pRankManager->m_startLeftTopPos = startLeftTopPos;
    pRankManager->m_nRankManagerPoint = nRankScore;
    pRankManager->m_pLayer = layer;
    // 初期化
    pRankManager->init();
    
    return pRankManager;
}
