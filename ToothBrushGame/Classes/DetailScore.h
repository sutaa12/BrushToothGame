//
//  DetailScore.h
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/27.
//
//

#ifndef __ToothBrushGame__DetailScore__
#define __ToothBrushGame__DetailScore__
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
class DetailScore
{
public:
    DetailScore();
    ~DetailScore();
    
    bool init(void);
    void uninit(void);
    void update(void);
    LabelTTF* getDetailName(void){return m_pDetailScoreLabel;}
    
    static DetailScore* create(const Vec2& startLeftTopPos,char* DetailName,int nPoint,Layer* layer);
    
private:
    int m_nPoint;
    Layer* m_pLayer;
    Vec2 m_startLeftTopPos;
    LabelTTF* m_pDetailScoreLabel;
    LabelTTF* m_pPointLabel;
};


#endif /* defined(__ToothBrushGame__DetailScore__) */
