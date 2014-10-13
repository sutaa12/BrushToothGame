//
//  ToothManager.h
//  test
//
//  Created by 丸山 潤 on 2014/10/08.
//
//

#ifndef __test__ToothManager__
#define __test__ToothManager__

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
class Tooth;

//********************************************************************************
// クラス宣言
//********************************************************************************
class ToothManager
{
public:
    ToothManager();
    ~ToothManager();
    
    bool init(void);
    void uninit(void);
    void update(void);
    
    static ToothManager* Create(const Vec2& startLeftTopPos,const int& nTopToothNum,
                                const int& nBottomToothNum,const float& fDistance,Layer* layer);
    
    int getTopToothNum(void){return m_nTopToothNum;}
    int getBottomToothNum(void){return m_nBottomToothNum;}
    
    Tooth* getTopTooth(void){return m_pTopTooth;}
    Tooth* getBootomTooth(void){return m_pBottomTooth;}
    
    void AddTopGumPosAndTopToothPos(const Vec2& vec);
    void AddBottomGumPosAndBottomToothPos(const Vec2& vec);
    
private:
    int m_nTopToothNum;
    int m_nBottomToothNum;
    float m_fDistance;
    Vec2 m_startLeftTopPos;
    Vec2 m_topToothPos;
    Vec2 m_bottomToothPos;
    Vec2 m_topGumPos;
    Vec2 m_bottomGumPos;
    
    Tooth* m_pTopTooth;
    Tooth* m_pBottomTooth;
    Sprite* m_pTopToothSprite;
    Sprite* m_pBottomToothSprite;
    Sprite* m_pTopGumSprite;
    Sprite* m_pBottomGumSprite;
    
    Layer* m_pLayer;
};
#endif /* defined(__test__ToothManager__) */
