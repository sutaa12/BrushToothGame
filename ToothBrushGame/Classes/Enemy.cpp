//
//  Enemy.cpp
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/14.
//
//
#include "TextureFile.h"
#include "Sound.h"
#include "Enemy.h"
#include "Random.h"
#include "common.h"
#include "LifeBar.h"
#include "Score.h"
int Enemy::m_nEnemyDown[Enemy::ENEMY_KIND_MAX];
const Enemy::ENEMY_STATUS ENEMY_STATUS_LIST[Enemy::ENEMY_KIND_MAX] =
{
    {Vec2(2,2),1},
    {Vec2(2,2),1},
};
//================================================================================
// コンストラクタ
//================================================================================
Enemy::Enemy(void)
{
    
    // メンバ変数の初期化
    m_pSprite = nullptr;
    
    //関数ポインタセット
    m_pFunc[0] = &Enemy::choiceAction;
    m_pFunc[1] = &Enemy::moveAction;
    m_pFunc[2] = &Enemy::delayAction;
    m_actionMode = 0;
    m_time = 0;
    m_nLife = 0;
    m_bDeath = true;
    m_bDown = true;
    m_bFollowPowder = false;
}

//================================================================================
// デストラクタ
//================================================================================
Enemy::~Enemy()
{
    
}
//================================================================================
// 初期化処理
//================================================================================
bool Enemy::init(void)
{
    // スプライトの作成
    m_pSprite = Sprite::create(TEX_ENEMY_WAIT_01);

    // エラーチェック
    if(m_pSprite == nullptr)
    {
        // スプライト生成エラー
        return false;
    }
    
    m_bDeath = true;
    // スプライトの座標設定
    m_pSprite->setPosition(m_pos);
    
    m_pSprite->setOpacity(255);

    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void Enemy::uninit(void)
{
}

//================================================================================
//倒される処理
//================================================================================
void Enemy::disappear(void)
{
    
    //死亡フラグセット
    m_bDeath = true;
    //画像をきり替え
}
//================================================================================
// 更新処理
//================================================================================
void Enemy::update(void)
{
    if(!m_bDeath)
    {
        //状態に応じた処理開始
        (this->*m_pFunc[m_actionMode])();
        //タイムが0なら強制的に行動させる
        if(m_time <= 0)
        {
            m_time = 0;
            m_actionMode = ACTION_NONE;
        }
        //HPが０なら消滅
        if(m_nLife <= 0)
        {
            //敵に攻撃したときのSE
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SE_ENEMY_DOWN_1);

            m_nLife = 0;
            disappear();
        }
    }
}
//================================================================================
//行動選択関数
//================================================================================
void Enemy::choiceAction(void)
{
    m_actionMode = RandomMT::getRandom(0, ACTION_MAX - 1);
    m_time = RandomMT::getRandom(0, Enemy::MAX_TIME);
}
//================================================================================
//移動
//================================================================================
void Enemy::moveAction(void)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = m_pSprite->getContentSize() / 2;
    Vec2 MaxPos = Vec2(visibleSize.width - origin.x,visibleSize.height - 128 - origin.y);
    Vec2 MinPos = Vec2(origin.x,MaxPos.y - 512 + origin.y);

    Vec2 minSize = Vec2(MinPos.x,MinPos.y);
    Vec2 maxSize = Vec2(MaxPos.x,MaxPos.y);

    m_pos += m_move;
    if(m_pos.x >= maxSize.x || m_pos.x <= minSize.x)
    {
        m_move.x *= -1;
    }
    else
    if(m_pos.y >= maxSize.y || m_pos.y <= minSize.y)
    {
        m_move.y *= -1;
    }

    CHECK_MAX_POS(m_pos.x,minSize.x,maxSize.x);
    CHECK_MAX_POS(m_pos.y,minSize.y,maxSize.y);
    getSprite()->setPosition(m_pos);
    m_time--;
}
//================================================================================
//攻撃
//================================================================================
void Enemy::attackAction(void)
{
    //攻撃
    if(m_time % 50 == 0)
    {
        LifeBar::addLife(-1);
    }
    m_time--;
}
//================================================================================
//待機
//================================================================================
void Enemy::delayAction(void)
{
    m_time--;
    
}
//================================================================================
//ダメージ処理
//================================================================================
void Enemy::addDamage(int nDamage)
{
    m_nLife -= nDamage;
}
//================================================================================
// 敵再配置処理
//================================================================================
void Enemy::setSpawn(ENEMY_KIND nEnemyKind,Vec2 pos)
{
    m_nEnemyKind = nEnemyKind;
    m_bDeath = false;
    m_pos = pos;
    m_pSprite->setPosition(pos);
    m_pSprite->setOpacity(255);
    m_nLife = RandomMT::getRaodom(1, MAX_LIFE);
    m_move = ENEMY_STATUS_LIST[m_nEnemyKind].EnemySpeed;
    m_bDown = false;
    m_pSprite->setTexture(ENEMY_IMAGE_LIST[nEnemyKind][0]);
}
//================================================================================
// 生成処理
//================================================================================
Enemy* Enemy::create(const Vec2& pos,ENEMY_KIND nKindEnemy)
{
    // インスタンスの生成
    Enemy* pEnemy = new Enemy();

    // メンバ変数の代入
    pEnemy->m_pos = pos;
    pEnemy->m_nEnemyKind = nKindEnemy;

    // 初期化
    pEnemy->init();
    
    return pEnemy;
}
//================================================================================
//敵が消える処理
//================================================================================
void Enemy::setEnemyDown(void)
{
    Score::addScore(10);
    m_nLife = 0;
    m_bDeath = true;
    m_bDown = true;
    unsigned short uOpacity = m_pSprite->getOpacity();
    if(uOpacity >= 0)
    {
        uOpacity = 0;
    }
    m_pSprite->setOpacity(uOpacity);
    m_nEnemyDown[m_nEnemyKind]++;
    
}

