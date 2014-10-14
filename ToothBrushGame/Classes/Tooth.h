//********************************************************************************
//  Tooth.h
//  test
//
//  Created by 丸山 潤 on 2014/10/08.
//
//********************************************************************************
//********************************************************************************
// インクルードガード
//********************************************************************************
#ifndef __test__Tooth__
#define __test__Tooth__

//********************************************************************************
// インクルード
//********************************************************************************
#include "cocos2d.h"

//********************************************************************************
// 名前空間の使用
//********************************************************************************
using namespace cocos2d;

//********************************************************************************
// クラス宣言
//********************************************************************************
class Tooth
{
public:
    Tooth();
    ~Tooth();
    
    bool init(void);
    void uninit(void);
    void update(void);
    
    static Tooth* Create(const Vec2& pos);
    Sprite* getSprite(void){return m_pToothSprite;}
    
    void setPos(Vec2 pos){m_pos = pos;}
    void setPos(float x,float y){m_pos.x = x;m_pos.y = y;}
    void addPos(Vec2 pos){m_pos += pos;}
    void addPos(float x,float y){m_pos.x += x;m_pos.y += y;}
    Vec2 getPos(void){return m_pos;}
    
    void RefreshToothSpritePos(void){m_pToothSprite->setPosition(m_pos);}
    
private:
    Sprite* m_pToothSprite;
    Vec2 m_pos;
    Vec3 m_rot;
};

#endif /* defined(__test__Tooth__) */
