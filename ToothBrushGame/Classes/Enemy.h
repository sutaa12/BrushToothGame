//
//  Enemy.h
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/14.
//
//

#ifndef __ToothBrushGame__Enemy__
#define __ToothBrushGame__Enemy__

#include "cocos2d.h"
#include "TextureFile.h"
#include "AchievementDataBase.h"
using namespace cocos2d;


class Enemy
{
private:
    //敵の行動状態
    enum ACTION_MODE
    {
        ACTION_NONE = 0,
        ACTION_MOVE,
        ACTION_DELAY,
        ACTION_MAX
    };
public:
    //敵の種類
    enum ENEMY_KIND
    {
        ENEMY_KIND_NORMAL_ONE,
        ENEMY_KIND_NORMAL_TWO,
        ENEMY_KIND_NORMAL_TREE,
        ENEMY_KIND_LAIR_ONE,
        ENEMY_KIND_LAIR_TWO,
        ENEMY_KIND_LAIR_TREE,
        ENEMY_KIND_MAX
    };
    //敵の画像リスト
    const char* ENEMY_IMAGE_LIST[ENEMY_KIND_MAX][2] =
    {
        {
            TEX_ENEMY_NORMAL_WAIT_00,
            TEX_ENEMY_NORMAL_DIE_01
        },
        {
            TEX_ENEMY_BLUE_WAIT_01,
            TEX_ENEMY_BLUE_DIE_01
        },
        {
            TEX_ENEMY_TOUGH_WAIT_01,
            TEX_ENEMY_TOUGH_DIE_01
        },

        {
            TEX_ENEMY_LAIR_WAIT_00,
            TEX_ENEMY_LAIR_DIE_01
        },
        {
            TEX_ENEMY_LAIR_LITTLE_WAIT_01,
            TEX_ENEMY_LAIR_LITTLE_DIE_01
        },
        {
            TEX_ENEMY_LITTLE_WAIT_01,
            TEX_ENEMY_LITTLE_DIE_01
        },
    };
public:
    
    //敵の個別情報
    struct ENEMY_STATUS
    {
        int move;
        int EnemyLife;
        ACHIEVEMENT_KIND achievement;
    };
    
    Enemy();   //コンストラクタ
    ~Enemy();  //デストラクタ

    bool init();    //初期設定
    void uninit();  //
    void update();  //更新
    void disappear();   //消滅
    static Enemy* create(const Vec2& pos = Vec2(0.0f,0.0f),ENEMY_KIND nKindEnemy = ENEMY_KIND_NORMAL_ONE);
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
    //行動選択関数
    void choiceAction(void);
    
    //移動
    void moveAction(void);
    //攻撃
    void attackAction(void);
    //待機
    void delayAction(void);
    //倒された
    void setEnemyDown();

    //位置を画像に適用
    void refreshSpritePos(void){m_pSprite->setPosition(m_pos);}
    //出現
    void setSpawn(ENEMY_KIND nEnemyKind,Vec2 pos);
    //ダメージ処理
    void addDamage(int nDamage = 1);
    //倒れたフラグを拾う
    bool getEnemyDownFlag(void){return m_bDown;}
    
    void setFollowPowder(bool bFollow){m_bFollowPowder = bFollow;}
    bool getFollowPowder(void){return m_bFollowPowder;}
    
    //敵の数取得
    static int getEnemyKindDownNum(int nEnemyKind){return m_nEnemyDown[nEnemyKind];}
    static int getEnemyAllDownNum(void){int nEnemyAllNum = 0;for(int nloop = 0; nloop < Enemy::ENEMY_KIND_MAX;nloop++){nEnemyAllNum += m_nEnemyDown[nloop];}return nEnemyAllNum;};
    //敵の数取得
    static int getEnemyKindDisappearNum(int nEnemyKind){return m_nEnemyDisappear[nEnemyKind];}
    static int getEnemyAllDisappearNum(void){int nEnemyAllNum = 0;for(int nloop = 0; nloop < Enemy::ENEMY_KIND_MAX;nloop++){nEnemyAllNum += m_nEnemyDisappear[nloop];}return nEnemyAllNum;};
    //倒した敵の数を種類分
    static int m_nEnemyDown[Enemy::ENEMY_KIND_MAX];
    static int m_nEnemyDisappear[Enemy::ENEMY_KIND_MAX];

    static void initEnemyDownNum(void){for(int nloop = 0; nloop < ENEMY_KIND_MAX;nloop++){m_nEnemyDown[nloop] = 0;m_nEnemyDisappear[nloop] = 0;}}

private:
    void (Enemy::*m_pFunc[ACTION_MAX])();	// 関数ポインタ
    Sprite* m_pSprite;
    Vec2 m_pos;
    int m_move;
    Vec3 m_rot;
    bool m_bFollowPowder;    
    //時間
    int m_time;
    //行動状態
    int m_actionMode;
    //敵が倒れたフラグ
    bool m_bDown;
    //生きてるか死んでるかのフラグ
    bool m_bDeath;
    //HP
    int m_nLife;
    
    //敵の種類
    ENEMY_KIND m_nEnemyKind;
    
    float m_fRot;//角度
    
//定数
public:
    //ライフの最大値
    static const int MAX_LIFE = 3;
    //時間の最大値
    static const int MAX_TIME = 100;
    //移動の最大値
    static const int MIN_X = 0;
    static const int MAX_X = 640;
    static const int MIN_Y = 0;
    static const int MAX_Y = 512;
    static const int MAX_MOVE = 20;
    static const int DAMEGE = 1;
    static const unsigned short OPACITY_SPEED = 255;
};



#endif /* defined(__ToothBrushGame__Enemy__) */
