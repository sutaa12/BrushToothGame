//
//  RankObject.h
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/21.
//
//

#ifndef __ToothBrushGame__RankObject__
#define __ToothBrushGame__RankObject__

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
class Number;

//********************************************************************************
// クラス宣言
//********************************************************************************
class RankObject
{
public:
    RankObject();
    ~RankObject();
    
    bool init(void);
    void uninit(void);
    void update(void);
    
    static RankObject* create(const Vec2& startLeftTopPos,char* cRank,Layer* layer);
    
private:
    Layer* m_pLayer;
    Vec2 m_startLeftTopPos;
    LabelTTF* m_pRankObjectLabel;
    LabelTTF* m_pPointLabel;
    char* m_cRankObjectRank;
};

#endif /* defined(__ToothBrushGame__RankObject__) */
