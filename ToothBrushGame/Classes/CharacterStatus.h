//
//  CharacterStatus.h
//  ToothBrushGame
//
//  Created by 鈴木愛忠 on 2014/10/22.
//
//

#ifndef __ToothBrushGame__CharacterStatus__
#define __ToothBrushGame__CharacterStatus__

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
class CharacterStatus
{
public:

    typedef enum
    {
        CHARACTERSTATUS_PATTERN_CRY = 0,
        CHARACTERSTATUS_PATTERN_NORMAL,
        CHARACTERSTATUS_PATTERN_SMAILE,
        CHARACTERSTATUS_PATTERN_MAX,
    }CHARACTERSTATUS_PATTERN;

    CharacterStatus();
    ~CharacterStatus();

    bool init(void);
    void uninit(void);
    void update(void);

    static CharacterStatus* create(const Vec2& startRigthBottomPos = Vec2(0.0f,0.0f),
                                   CHARACTERSTATUS_PATTERN pattern = CHARACTERSTATUS_PATTERN_CRY);

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

    void setJump(float fTime = 0.5f,Vec2 move = Vec2(0,0),int nHigh = 60,int nCount = 1);
    void setPattern(CHARACTERSTATUS_PATTERN pattern);
    CHARACTERSTATUS_PATTERN getPattern(void){return m_pattern;}

private:
    const char* IMAGE_LIST[CHARACTERSTATUS_PATTERN_MAX] =
    {
        "StatusLittleGirl_00.png",
        "Enemy.png",
        "Boss.png"
    };

    Sprite* m_pSprite;
    Vec2 m_pos;
    Vec3 m_rot;
    CHARACTERSTATUS_PATTERN m_pattern;
};

#endif /* defined(__ToothBrushGame__CharacterStatus__) */
