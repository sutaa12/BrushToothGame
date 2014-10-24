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
class Gum;

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
    
    static ToothManager* create(const Vec2& startLeftTopPos,Layer* layer);
    
    Sprite* getToothSprite(void){return m_pTooth;}
    Sprite* getTongerSprite(void){return m_pTonger;}
    
private:
    Vec2 m_startLeftTopPos;
    Layer* m_pLayer;
    
    Sprite* m_pTonger;
    Sprite* m_pTooth;
};
#endif /* defined(__test__ToothManager__) */
