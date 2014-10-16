//********************************************************************************
//  PlaqueManager.h
//  ToothBrushGame
//
//  Created by 丸山 潤 on 2014/10/15.
//
//********************************************************************************
//********************************************************************************
// インクルードガード
//********************************************************************************
#ifndef __ToothBrushGame__PlaqueManager__
#define __ToothBrushGame__PlaqueManager__

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
class Plaque;

//********************************************************************************
// クラス宣言
//********************************************************************************
class PlaqueManager
{
public:
    PlaqueManager();
    ~PlaqueManager();

    bool init(void);
    void uninit(void);
    void update(void);

    static PlaqueManager* create(int nPlaqueMaxNum,Layer* pLayer);


    Plaque** getPlaqueTop(void){return &m_ppPlaque[0];}
    int getPlaqueNum(void){return m_nPlaqueNum;}
    void setPlaqueNum(int nNum){m_nPlaqueNum = nNum;}
    void addPlaqueNum(int nNum){m_nPlaqueNum += nNum;}

    int getPlaqueMaxNum(void){return m_nPlaqueMaxNum;}
private:
    Plaque** m_ppPlaque;
    int m_nPlaqueNum;
    int m_nPlaqueMaxNum;
    Layer* m_pLayer;

    void createPlaque(void);
};

#endif /* defined(__ToothBrushGame__PlaqueManager__) */
