//
//  ToothPowder.h
//  ToothBrushGame
//
//  Created by 鈴木愛忠 on 2014/10/22.
//
//

#ifndef __ToothBrushGame__ToothPowder__
#define __ToothBrushGame__ToothPowder__


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
class ToothPowder
{
public:
    ToothPowder();
    ~ToothPowder();
    
    bool init(void);
    void uninit(void);
    void update(void);
    void disappear(void);
    
    static ToothPowder* create(Layer* pLayer,const Vec2& pos = Vec2(0.0f,0.0f));
    Sprite* getSprite(void){return m_pSprite;}
    Sprite* getItemIconSprite(void){return m_pItemIcon;}
    
    void setPos(Vec2 pos);
    void setPos(float x,float y){m_pos.x = x;m_pos.y = y;}
    Vec2 getPos(void){return m_pos;}
    
    void refreshSpritePos(void){m_pSprite->setPosition(m_pos);}
    
    void chkPowderTouchFlag(Point pos);
    void setPowderTouchFlag(bool bFlag){m_bPowderTouchFlag = bFlag;}
    bool getPowderTouchFlag(void){return m_bPowderTouchFlag;}
    
private:
    Layer* m_pLayer;
    Sprite* m_pSprite;
    Sprite* m_pItemIcon;
    Vec2 m_pos;
    Vec3 m_rot;
    bool m_bPowderTouchFlag;
};

#endif /* defined(__ToothBrushGame__ToothPowder__) */
