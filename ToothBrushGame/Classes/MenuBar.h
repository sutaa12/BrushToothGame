//
//  MenuBar.h
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/16.
//
//

#ifndef __ToothBrushGame__MenuBar__
#define __ToothBrushGame__MenuBar__

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
class MenuBar
{
public:
    MenuBar();
    ~MenuBar();

    bool init(void);
    void uninit(void);
    void update(void);

    static MenuBar* create(Layer* pPauseTagetLayer = nullptr,const Vec2& pos = Vec2(0.0f,0.0f));
    Sprite* getSprite(void){return m_pSpriteBase;}
    Menu* getMenu(void){return m_pMenu;}
    void setPausePermission(bool bFlg);

    void setPos(Vec2 pos){m_pos = pos;}
    void setPos(float x,float y){m_pos.x = x;m_pos.y = y;}
    void setPosX(float x){m_pos.x = x;}
    void setPosY(float y){m_pos.y = y;}
    void addPos(Vec2 pos){m_pos += pos;}
    void addPos(float x,float y){m_pos.x += x;m_pos.y += y;}
    void addPosX(float x){m_pos.x += x;}
    void addPosY(float y){m_pos.y += y;}
    Vec2 getPos(void){return m_pos;}

    void refreshSpritePos(void);

private:
    void menuCallback(void);

    Sprite* m_pSpriteBase;
    MenuItemSprite* m_pMenuItemSprite;
    Menu* m_pMenu;
    Layer* m_pPauseTagetLayer;

    Vec2 m_pos;
    Vec3 m_rot;
    bool m_bPausePermission;
};

#endif /* defined(__ToothBrushGame__MenuBar__) */
