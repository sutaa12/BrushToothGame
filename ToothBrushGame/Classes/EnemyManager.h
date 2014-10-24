//
//  EnemyManager.h
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/15.
//
//

#ifndef __ToothBrushGame__EnemyManager__
#define __ToothBrushGame__EnemyManager__

//********************************************************************************
// インクルード
//********************************************************************************
#include "cocos2d.h"
#include "Enemy.h"
//********************************************************************************
// 名前空間の使用
//********************************************************************************
using namespace cocos2d;

//********************************************************************************
// 前方クラス宣言
//********************************************************************************

//********************************************************************************
// クラス宣言
//********************************************************************************
class EnemyManager
{
public:
    //最初に出す敵の数
    EnemyManager(int numEnemy);
    ~EnemyManager();

    bool init(void);
    void uninit(void);
    void update(void);

    static EnemyManager* create(Layer* layer,int numEnemy);

    //敵の先頭取得
    Enemy** getEnemysTop(void){return &m_pEnemy[0];}
    
    //敵の数取得
    int getEnemyNum(void);
    
    //すべての敵を消す
    void setEnemyClear(void);
    
    void spawn(Enemy::ENEMY_KIND nEnemyKind = Enemy::ENEMY_KIND_NORMAL_ONE,int nSpawnNum = ENEMY_MAX,Vec2 pos = Vec2(-1, -1));
    
public:
    //敵の最大数
    static const int ENEMY_MAX = 100;
    //開始する時間感覚
    static const int TIME_SPAN = 100;
private:

    //敵の配列
    Enemy* m_pEnemy[ENEMY_MAX];
    
    Layer* m_pLayer;
    int m_numEnemy;
    
    int m_nTime;
    
    int m_nTimeSpan;
    
    int m_nSpriteMax;
    int m_nSpriteMin;

};

#endif /* defined(__ToothBrushGame__EnemyManager__) */
