//
//  RankManager.h
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/21.
//
//

#ifndef __ToothBrushGame__RankManager__
#define __ToothBrushGame__RankManager__

#include <stdio.h>
//********************************************************************************
// インクルード
//********************************************************************************
#include "cocos2d.h"

//********************************************************************************
// 名前空間の使用
//********************************************************************************
using namespace cocos2d;
class RankObject;
class Score;
//********************************************************************************
// クラス宣言
//********************************************************************************
class RankManager
{
public:
    enum RANK_MODE{
        RANK_S = 0,
        RANK_A,
        RANK_B,
        RANK_C,
        RANK_D,
        RANK_MAX
    };
    
    const int SCORE_RANK_S = 1000;
    const int SCORE_RANK_A = 800;
    const int SCORE_RANK_B = 600;
    const int SCORE_RANK_C = 500;
    const int SCORE_RANK_D = 400;
    
    RankManager();
    ~RankManager();
    
    bool init(void);
    void uninit(void);
    void update(void);
    
    static RankManager* create(const Vec2& startLeftTopPos,int nNumber,Layer* layer);
    
    void addRankManager(int num){m_nRankManagerPoint += num;}
    
    
private:
    Vec2 m_startLeftTopPos;
    RankObject* m_pRankObject;
    Score* m_pScore;
    Layer* m_pLayer;
    int m_nRankManagerPoint;
};
#endif /* defined(__ToothBrushGame__RankManager__) */