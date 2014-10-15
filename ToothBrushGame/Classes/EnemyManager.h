//
//  EnemyManager.h
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/15.
//
//

#ifndef __ToothBrushGame__EnemyManager__
#define __ToothBrushGame__EnemyManager__

#include <stdio.h>

//********************************************************************************
// インクルード
//********************************************************************************
#include "cocos2d.h"

//********************************************************************************
// 名前空間の使用
//********************************************************************************
using namespace cocos2d;

//********************************************************************************
// 前方クラス宣言
//********************************************************************************
class Enemy;

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

    Enemy* getTopTooth(void){return m_pEnemy[0];}

    void disappear(const Vec2& vec);
    void action(const Vec2& vec);
    void attack(const Vec2& vec);
    void move(const Vec2& vec);
    void spawn(const Vec2& vec);
    void checkDamage(const Vec2& vec);


private:
    //敵の最大数
    static const int ENEMY_MAX = 10;
    //敵の配列
    Enemy* m_pEnemy[ENEMY_MAX];

    Layer* m_pLayer;
    int m_numEnemy;
};

#endif /* defined(__ToothBrushGame__EnemyManager__) */
