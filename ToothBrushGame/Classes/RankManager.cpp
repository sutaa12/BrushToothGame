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
#include "Enemy.h"
#include "AchievementDataBase.h"
//================================================================================
// コンストラクタ
//================================================================================
RankManager::RankManager(void)
{
    // メンバ変数の初期化
    m_pLayer = nullptr;
    //スコア数字初期化
    m_nRankManagerPoint = 0;
    m_nTimeBornus = 0;
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
    const int nEnemyBounus[Enemy::ENEMY_KIND_MAX] =
    {
      2,4,6,
        10,15,30
    };
    char* sEnemy[Enemy::ENEMY_KIND_MAX + 1] =
    {
      "ばいばいしたよわいばいきん　",
      "ばいばいしたばいきん　　　　",
      "ばいばいしたつよいばいきん　",
      "ばいばいしたれあばいきん　　",
      "ばいばいしたれあばいきん２　",
      "ばいばいしたれあばいきん３　",
      "ばいばいしたぜんぶのばいきん"
    };
    Size visibleSize = Director::getInstance()->getVisibleSize() / 2 + SCREEN_CENTER;
    Vec2 origin = Director::getInstance()->getVisibleSize() / 2 - SCREEN_CENTER;
    
    m_pEndingBack = Sprite::create(TEX_RESULT_ENDING_NORMAL_BACK);
    m_pEndingBack->setPosition(Vec2(visibleSize.width / 2,origin.y + m_pEndingBack->getContentSize().height / 2));
    m_pLayer->addChild(m_pEndingBack);
    int time = m_nTimeBornus;
    if(time < 0)
    {
        time = 0;
    }
    m_pTimeScore = DetailScore::create(Vec2(origin.x + 200,origin.y + 930),"たいむぼぉなすぅ　　　　　　　",time,m_pLayer);
    for(int nloop = 0;nloop < Enemy::ENEMY_KIND_MAX;nloop++)
    {
        m_pEnemyScore[nloop] = DetailScore::create(Vec2(origin.x + 200,origin.y - 50 + m_pTimeScore->getDetailName()->getPosition().y - (nloop *50)),sEnemy[nloop],Enemy::getEnemyKindDownNum(nloop),m_pLayer);
        m_nRankManagerPoint += Enemy::getEnemyKindDownNum(nloop) * nEnemyBounus[nloop];
    }
    m_pEnemyScore[Enemy::ENEMY_KIND_MAX] = DetailScore::create(Vec2(origin.x + 200,origin.y + m_pEnemyScore[Enemy::ENEMY_KIND_MAX - 1]->getDetailName()->getPosition().y - 50),sEnemy[Enemy::ENEMY_KIND_MAX],Enemy::getEnemyAllDownNum(),m_pLayer);
    time *= TIME_BORNUS;
    m_nRankManagerPoint += time;
    const char cRank[RANK_MAX]=
    {
        'S','A','B','C','D'
    };
    m_pScore = Score::create(Vec2(m_startLeftTopPos.x,m_startLeftTopPos.y - 100), m_nRankManagerPoint,m_pLayer,m_nRankManagerPoint);
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
    if(m_nTimeBornus < 0)
    {
        nNum = RANK_D;
    }
    m_pRankObject = RankObject::create(Vec2(m_pScore->getPoint()->getPosition().x +m_pScore->getPoint()->getContentSize().width + 100,m_startLeftTopPos.y - 100), cRank[nNum], m_pLayer);
    
    AchievementDataBaseList::setAchievementMax(ACHIEVEMENT_TYPE_GAME_TOP_SCORE, m_nRankManagerPoint);
    
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
RankManager* RankManager::create(const Vec2& startLeftTopPos,int nTimeBornus,Layer* layer)
{
    RankManager* pRankManager = new RankManager();
    
    // メンバー変数の代入
    pRankManager->m_startLeftTopPos = startLeftTopPos;
    pRankManager->m_nRankManagerPoint = 0;
    pRankManager->m_pLayer = layer;
    pRankManager->m_nTimeBornus = nTimeBornus;
    
    // 初期化
    pRankManager->init();
    
    return pRankManager;
}
