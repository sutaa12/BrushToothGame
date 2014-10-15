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
    EnemyManager();
    ~EnemyManager();

    bool init(void);
    void uninit(void);
    void update(void);

    static EnemyManager* create(const Vec2& startLeftTopPos,Layer* layer);

    Enemy* getTopTooth(void){return m_pTopTooth;}
    Enemy* getBootomTooth(void){return m_pBottomTooth;}

    void disappear(const Vec2& vec);
    void action(const Vec2& vec);
    void attack(const Vec2& vec);
    void move(const Vec2& vec);
    void spawn(const Vec2& vec);
    void checkDamage(const Vec2& vec);


private:
    Vec2 m_startLeftTopPos;

    Enemy* m_pTopTooth;
    Enemy* m_pBottomTooth;

    Layer* m_pLayer;
};

#endif /* defined(__ToothBrushGame__EnemyManager__) */
