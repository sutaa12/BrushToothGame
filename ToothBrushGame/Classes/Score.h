//
//  Score.h
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/15.
//
//

#ifndef __ToothBrushGame__Score__
#define __ToothBrushGame__Score__

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
class Score
{
public:
    Score();
    ~Score();
    
    bool init(void);
    void uninit(void);
    void update(void);
    
    static Score* create(const Vec2& startLeftTopPos,int nNumber,Layer* layer);
    
    Number** getNumber(void){return &m_ppNumbers[0];}
        
private:
    Vec2 m_startLeftTopPos;
    
    Number** m_ppNumbers;
    
    Layer* m_pLayer;
    
    int m_nMaxNumber;//数字の桁数
};

#endif /* defined(__ToothBrushGame__Score__) */
