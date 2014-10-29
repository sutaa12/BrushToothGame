//
//  EnemyScore.h
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/29.
//
//

#ifndef __ToothBrushGame__EnemyEnemyScore__
#define __ToothBrushGame__EnemyEnemyScore__

//
//  EnemyScore.h
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/15.
//
//

#ifndef __ToothBrushGame__EnemyScore__
#define __ToothBrushGame__EnemyScore__

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
class EnemyScore
{
public:
    EnemyScore();
    ~EnemyScore();
    
    bool init(void);
    void uninit(void);
    void update(void);
    
    static EnemyScore* create(const Vec2& startLeftTopPos,char* pTexName,Layer* layer,int nEnemyScore = 0);
    
    Number** getNumber(void){return &m_ppNumbers[0];}
    LabelTTF* getPoint(){return m_pPointLabel ;}
    
    static void addEnemyScore(int num){m_nEnemyScorePoint += num;}
    static int getEnemyScoreNum(void){return m_nEnemyScorePoint;}
    
private:
    Vec2 m_startLeftTopPos;
    
    Number** m_ppNumbers;
    
    Layer* m_pLayer;
    
    char* m_pTexName;
    Sprite* m_pEnemyIcon;
    LabelTTF* m_pPointLabel;
    static int m_nEnemyScorePoint;
};

#endif /* defined(__ToothBrushGame__EnemyScore__) */
#endif /* defined(__ToothBrushGame__EnemyEnemyScore__) */
