//
//  Bubble.h
//  ToothBrushGame
//
//  Created by 鈴木愛忠 on 2014/10/17.
//
//

#ifndef __ToothBrushGame__Bubble__
#define __ToothBrushGame__Bubble__

#include "cocos2d.h"

using namespace cocos2d;


class Bubble
{
    
public:
    Bubble();   //コンストラクタ
    ~Bubble();  //デストラクタ
    
    bool init();    //初期設定
    void uninit();  //
    void update();  //更新
    void disappear();   //消滅
    
    static Bubble* create(const Vec2& pos = Vec2(0.0f,0.0f));
    Sprite* getSprite(void){return m_pSprite;}
    
    //セッター　ゲッター
    void setPos(Vec2 pos){m_pos = pos;}
    void setPos(float x,float y){m_pos.x = x;m_pos.y = y;}
    void setPosX(float x){m_pos.x = x;}
    void setPosY(float y){m_pos.y = y;}
    void addPos(Vec2 pos){m_pos += pos;}
    void addPos(float x,float y){m_pos.x += x;m_pos.y += y;}
    void addPosX(float x){m_pos.x += x;}
    void addPosY(float y){m_pos.y += y;}
    Vec2 getPos(void){return m_pos;}
    bool getDisapper(void){return m_bDeath;}
    //位置を画像に適用
    void refreshSpritePos(void){m_pSprite->setPosition(m_pos);}
    //出現
    void setSpawn(Vec2 pos,Color3B col = Color3B(255,255,255));
    
private:
    Sprite* m_pSprite;
    Vec2 m_pos;
    Vec2 m_move;
    Vec3 m_rot;
    //時間
    int m_time;
    //行動状態
    int m_actionMode;
    //生きてるか死んでるかのフラグ
    bool m_bDeath;
    //HP
    int m_nLife;
    //定数
public:
    //ライフの最大値
    static const int MAX_LIFE = 3;
    //時間の最大値
    static const int MAX_TIME = 25;
    //移動の最大値
    static const int MAX_MOVE = 10;
    static const int DAMEGE = 1;
    
};


#endif /* defined(__ToothBrushGame__Bubble__) */
