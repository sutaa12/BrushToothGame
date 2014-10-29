//
//  Clock.h
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/28.
//
//

#ifndef __ToothBrushGame__Clock__
#define __ToothBrushGame__Clock__

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
class Clock
{
public:
    Clock();
    ~Clock();

    bool init(void);
    void uninit(void);
    void update(void);

    static Clock* create(Layer* layer,const Vec2& pos = Vec2(0.0f,0.0f));
    Sprite* getSprite(void){return m_pBackLifeBar;}

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
    
    int getColockNow(void){return m_nCurrentTime;}
    
    void stopTime(void){m_bStop = true;}
    
private:
    Vec2 m_startLeftTopPos;
    Sprite* m_pSprite;
    Sprite* m_pBackLifeBar;
    ProgressTimer* m_pProgressTimer;
    Vec2 m_pos;
    Vec3 m_rot;
    static float m_nTime;
    Layer* m_pLayer;
    int m_nMaxLife;
    int m_nStartTimer;
    int m_nCurrentTime;
    int m_nTimer;
    LabelTTF* m_pPercentTxt;
    bool m_bSudden;
    
    bool m_bStop;

};


#endif /* defined(__ToothBrushGame__Clock__) */
