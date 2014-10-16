//
//  Plaque.h
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/14.
//
//

#ifndef __ToothBrushGame__Plaque__
#define __ToothBrushGame__Plaque__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class Plaque
{

public:
    Plaque();   //コンストラクタ
    ~Plaque();  //デストラクタ

    bool init();    //初期設定
    void uninit();  //
    void update();  //更新
    void disappear();   //消滅

    static Plaque* create(const Vec2& pos = Vec2(0.0f,0.0f));
    Sprite* getSprite(void){return m_pSprite;}

    void setPos(Vec2 pos){m_pos = pos;}
    void setPos(float x,float y){m_pos.x = x;m_pos.y = y;}
    void setPosX(float x){m_pos.x = x;}
    void setPosY(float y){m_pos.y = y;}
    void addPos(Vec2 pos){m_pos += pos;}
    void addPos(float x,float y){m_pos.x += x;m_pos.y += y;}
    void addPosX(float x){m_pos.x += x;}
    void addPosY(float y){m_pos.y += y;}
    Vec2 getPos(void){return m_pos;}

    void refreshSpritePos(void){m_pSprite->setPosition(m_pos);}

    bool getDisappear(void){return m_bDisappear;}
    void setDisappear(bool bFlg){m_bDisappear = bFlg;}

    // ダメージ処理(内部:ダメージタイマーがダメージ許可時間を上回っていたらダメージを与える)
    void addDamage(int nDamage = 1);

private:
    Sprite* m_pSprite;
    Vec2 m_pos;
    Vec3 m_rot;

    bool m_bDisappear;
    int m_nLife;
    int m_nDamageTimer;

public:
    static const unsigned short OPACITY_SPEED = 255;
    static const unsigned int DAMAGE_PERMISSION_TIME = 30;
};


#endif /* defined(__ToothBrushGame__Plaque__) */
