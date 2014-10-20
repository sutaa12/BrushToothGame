//
//  EnemyManager.cpp
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/15.
//
//


//********************************************************************************
// インクルード
//********************************************************************************
#include "EnemyManager.h"
#include "Enemy.h"
#include "Random.h"
//================================================================================
// コンストラクタ
//================================================================================
EnemyManager::EnemyManager(int numEnemy)
{
    // メンバ変数の初期化
    if(numEnemy >= ENEMY_MAX)
    {
        numEnemy = ENEMY_MAX - 1;
    }
    m_numEnemy = numEnemy;
    m_pLayer = nullptr;
    for(int nloop = 0;nloop < ENEMY_MAX;nloop++)
    {
        m_pEnemy[nloop] = nullptr;
    }
    m_nTime = 0;
    m_nTimeSpan = TIME_SPAN;
}

//================================================================================
// デストラクタ
//================================================================================
EnemyManager::~EnemyManager()
{
    for(int nloop = 0;nloop < ENEMY_MAX;nloop++)
    {
        if(m_pEnemy[nloop])
        {
            delete m_pEnemy[nloop];
            m_pEnemy[nloop] = nullptr;
        }
    }
}

//================================================================================
// 初期化処理
//================================================================================
bool EnemyManager::init(void)
{
    for(int nloop = 0;nloop < ENEMY_MAX;nloop++)
    {
        m_pEnemy[nloop] = Enemy::create(Vec2(0,0));
        m_pLayer->addChild(m_pEnemy[nloop]->getSprite());
        
    }
    for(int nloop = 0;nloop < m_numEnemy;nloop++)
    {
        m_pEnemy[nloop]->setSpawn(Vec2(RandomMT::getRandom(Enemy::MIN_X, Enemy::MAX_X),RandomMT::getRandom(Enemy::MIN_Y,Enemy::MAX_Y)));
    }
    
    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void EnemyManager::uninit(void)
{

}

//================================================================================
// 更新処理
//================================================================================
void EnemyManager::update(void)
{
    m_nTime++;

    for(int nloop = 0;nloop < EnemyManager::ENEMY_MAX;nloop++)
    {
        if(m_pEnemy[nloop])
        {
           m_pEnemy[nloop]->update();
        }
    }
    
}

//================================================================================
// 生成処理
//================================================================================
EnemyManager* EnemyManager::create(Layer* layer,int numEnemy)
{
    // 歯マネージャーのインスタンス化
    EnemyManager* pEnemyManager = new EnemyManager(numEnemy);

    // メンバー変数の代入
    pEnemyManager->m_pLayer = layer;

    // 初期化
    pEnemyManager->init();

    return pEnemyManager;
}

//================================================================================
// 敵生成処理
//================================================================================
void EnemyManager::spawn(int nSpawnNum)
{
    clampf(nSpawnNum, 0, ENEMY_MAX);
    int nEnemyNum = 0;
    for(int nloop = 0;nloop < ENEMY_MAX;nloop++)
    {
        if(m_pEnemy[nloop] && m_pEnemy[nloop]->getDisapper())
        {
            m_pEnemy[nloop]->setSpawn(Vec2(RandomMT::getRandom(Enemy::MIN_X, Enemy::MAX_X),RandomMT::getRandom(Enemy::MIN_Y,Enemy::MAX_Y)));
            nEnemyNum++;
        }
        if(nEnemyNum >= nSpawnNum)
        {
            return;
        }
    }
}
//================================================================================
// 敵の数取得
//================================================================================
int EnemyManager::getEnemyNum(void)
{
    int numEnemy = 0;
    for(int nloop = 0;nloop < ENEMY_MAX;nloop++)
    {
        if(m_pEnemy[nloop] && !m_pEnemy[nloop]->getDisapper())
        {
            numEnemy++;
        }
    }
    return numEnemy;
}
//================================================================================
// 敵をすべて消滅
//================================================================================
void EnemyManager::setEnemyClear(void)
{
    for(int nloop = 0;nloop < ENEMY_MAX;nloop++)
    {
        if(m_pEnemy[nloop] && !m_pEnemy[nloop]->getDisapper())
        {
            m_pEnemy[nloop]->disappear();
        }
    }
}


