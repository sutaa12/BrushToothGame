//
//  CountDown.h
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/20.
//
//

#ifndef __ToothBrushGame__CountDown__
#define __ToothBrushGame__CountDown__

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
class CountDown
{
     public:
        CountDown();
        ~CountDown();

        bool init(void);
        void uninit(void);
        void update(void);

        static CountDown* create(const Vec2& startLeftTopPos,int nNumber,Layer* layer);

        Number** getNumber(void){return &m_ppNumbers[0];}
        LabelTTF* getScore(){return m_pCountDownLabel ;}
       // LabelTTF* getPoint(){return m_pPointLabel ;}

        static void addScore(int num){m_nScorePoint += num;}


    private:
        Vec2 m_startLeftTopPos;

        Number** m_ppNumbers;
        
        Layer* m_pLayer;
        
        int m_nMaxNumber;//数字の桁数
        
        LabelTTF* m_pCountDownLabel;
        //LabelTTF* m_pPointLabel;
        static int m_nScorePoint;
    };
    


#endif /* defined(__ToothBrushGame__CountDown__) */
