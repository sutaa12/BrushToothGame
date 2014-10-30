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
#include "EnemyScore.h"
#include "AchievementDataBase.h"
#include "ToothPowder.h"

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
    SAFE_DELETE(m_pEnemysScore);
    for(int nloop = 0;nloop < Enemy::ENEMY_KIND_MAX;nloop++)
    {
        SAFE_DELETE(m_pEnemyScore[nloop]);
    }
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
    char* sEnemy[Enemy::ENEMY_KIND_MAX] =
    {
            TEX_ENEMY_NORMAL_WAIT_00,
            TEX_ENEMY_BLUE_WAIT_01,
            TEX_ENEMY_TOUGH_WAIT_01,
            TEX_ENEMY_LAIR_WAIT_00,
            TEX_ENEMY_LAIR_LITTLE_WAIT_01,
            TEX_ENEMY_LITTLE_WAIT_01,
    };
    Size visibleSize = Director::getInstance()->getVisibleSize() / 2 + SCREEN_CENTER;
    Vec2 origin = Director::getInstance()->getVisibleSize() / 2 - SCREEN_CENTER;
    
    
   
    Sprite* pBack = Sprite::create();
    pBack->setTextureRect(Rect(0,0,visibleSize.width,visibleSize.height / 2 + 40));
    pBack->setColor(Color3B::BLACK);
    pBack->setOpacity(100);
    pBack->setAnchorPoint(Vec2(0,0));
    pBack->setPosition(Vec2(origin.x,visibleSize.height / 2 - 40));
    m_pLayer->addChild(pBack);

    m_pEndingBack = Sprite::create(TEX_RESULT_ENDING_NORMAL_BACK);
    m_pEndingBack->setPosition(Vec2(visibleSize.width / 2,origin.y + m_pEndingBack->getContentSize().height / 2));
    m_pLayer->addChild(m_pEndingBack);
    
    LabelTTF* pResultName = LabelTTF::create("はみがきのせいか",MIKA_FONT,24);
    
    pResultName->setPosition(Vec2(visibleSize.width / 2,origin.y + 920));
    pResultName->enableStroke(Color3B::BLACK, 3);
    m_pLayer->addChild(pResultName);
    
    int time = m_nTimeBornus;
    if(time < 0)
    {
        time = 0;
    }
    const int SCORE_POS_Y = 860;
    for(int nloop = 0;nloop < Enemy::ENEMY_KIND_MAX;nloop++)
    {

        if(nloop >= Enemy::ENEMY_KIND_MAX /2)
        {
            m_pEnemyScore[nloop] = EnemyScore::create(Vec2(origin.x + 350,origin.y + origin.y + SCORE_POS_Y  - ((nloop - Enemy::ENEMY_KIND_MAX / 2) *90)),sEnemy[nloop],m_pLayer,Enemy::getEnemyKindDownNum(nloop));
            m_nRankManagerPoint += Enemy::getEnemyKindDownNum(nloop) * nEnemyBounus[nloop];
        }else{
            m_pEnemyScore[nloop] = EnemyScore::create(Vec2(origin.x + 100,origin.y + origin.y + SCORE_POS_Y - (nloop *90)),sEnemy[nloop],m_pLayer,Enemy::getEnemyKindDownNum(nloop));
            m_nRankManagerPoint += Enemy::getEnemyKindDownNum(nloop) * nEnemyBounus[nloop];
        }
        m_pEnemyScore[nloop]->getPoint()->setColor(Color3B::WHITE);
        m_pEnemyScore[nloop]->getPoint()->enableStroke(Color3B::BLACK, 3);
    }
    AchievementDataBaseList::setAchievementMax(ACHIEVEMENT_TYPE_GAME_TOP_ENEMY_DOWN, Enemy::getEnemyAllDownNum());

    time *= TIME_BORNUS;
    m_pEnemysScore = DetailScore::create(Vec2(origin.x + 180,origin.y  + origin.y + SCORE_POS_Y - 10 - (Enemy::ENEMY_KIND_MAX *50) + 80),"ばいきんごうけい",Enemy::getEnemyAllDownNum(),m_pLayer);
    m_pTimeScore = DetailScore::create(Vec2(origin.x + 180,origin.y + m_pEnemysScore->getDetailName()->getPosition().y
                                             - 50),"たいむぼぉなすぅ",time,m_pLayer);
    
    m_pToothPowderScore = DetailScore::create(Vec2(origin.x + 220,m_pTimeScore->getDetailName()->getPosition().y - 50),"たっぷおんりーぼーなす",0,m_pLayer);

    m_nRankManagerPoint += time;
    char* cRank[RANK_MAX]=
    {
        "Ｓ","Ａ","Ｂ","Ｃ","Ｄ"
    };
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
    }else
        AchievementDataBaseList::setAchievementMax(ACHIEVEMENT_TYPE_GAME_MAX_USE_BOM, ToothPowder::getToothPowderCount());
        AchievementDataBaseList::setAchievementMin(ACHIEVEMENT_TYPE_GAME_MIN_USE_BOM, ToothPowder::getToothPowderCount());
        if(ToothPowder::getToothPowderCount() == 0)
        {
            m_nRankManagerPoint += 1000;
            m_pToothPowderScore->setDetailPoint(1000);
            nNum = RANK_S;
        }
    m_pScore = DetailScore::create(Vec2(origin.x + 110,m_pToothPowderScore->getDetailName()->getPosition().y - 50), "すこあ",m_nRankManagerPoint,m_pLayer);

    m_pRankObject = RankObject::create(Vec2(m_pScore->getDetailName()->getPosition().x + 50 ,m_pScore->getDetailName()->getPosition().y - 50), cRank[nNum], m_pLayer);
    
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
