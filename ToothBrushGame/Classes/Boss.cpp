//
//  Boss.cpp
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/14.
//
//

#include "Boss.h"
#include "Random.h"
#include "common.h"
#include "LifeBar.h"
#include "EnemyManager.h"
//================================================================================
// コンストラクタ
//================================================================================
Boss::Boss(void)
{
    // メンバ変数の初期化
    m_pSprite = nullptr;
    
    //関数ポインタセット
    m_pFunc[0] = &Boss::choiceAction;
    m_pFunc[1] = &Boss::moveAction;
    m_pFunc[2] = &Boss::attackAction;
    m_pFunc[3] = &Boss::delayAction;
    m_pFunc[4] = &Boss::spawnAction;

    m_actionMode = 0;
    m_time = 0;
    m_nLife = 0;
    m_bDeath = true;
}

//================================================================================
// デストラクタ
//================================================================================
Boss::~Boss()
{
    
}

//================================================================================
// 初期化処理
//================================================================================
bool Boss::init(void)
{
    // スプライトの作成
    m_pSprite = Sprite::create("Boss.png");
    
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
void Boss::uninit(void)
{
}

//================================================================================
//消滅処理
//================================================================================
void Boss::disappear(void)
{
    unsigned short uOpacity = m_pSprite->getOpacity();
    if(uOpacity >= 0)
    {
        uOpacity -= OPACITY_SPEED;
    }
    m_pSprite->setOpacity(uOpacity);
    if(uOpacity <= 0)
    {
        uOpacity = 0;
        m_bDeath = true;
    }
}
//================================================================================
// 更新処理
//================================================================================
void Boss::update(void)
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
            m_nLife = 0;
            disappear();
        }
    }
}
//================================================================================
//行動選択関数
//================================================================================
void Boss::choiceAction(void)
{
    m_actionMode = RandomMT::getRandom(0, Boss::ACTION_MAX);
    m_time = RandomMT::getRandom(0, Boss::MAX_TIME);
    m_move = Vec2(RandomMT::getRandom(-Boss::MAX_MOVE,Boss::MAX_MOVE),RandomMT::getRandom(-Boss::MAX_MOVE,Boss::MAX_MOVE));
}
//================================================================================
//移動
//================================================================================
void Boss::moveAction(void)
{
    Vec2 minSize = Vec2(Boss::MIN_X + m_pSprite->getContentSize().width / 2,Boss::MIN_Y + m_pSprite->getContentSize().height / 2);
    Vec2 maxSize = Vec2(Boss::MAX_X - m_pSprite->getContentSize().width / 2,Boss::MAX_Y - m_pSprite->getContentSize().height / 2);
    
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
void Boss::attackAction(void)
{
    //攻撃
    if(m_time % 20 == 0)
    {
        LifeBar::addLife(-1);
    }

    m_time--;
}
//================================================================================
//待機
//================================================================================
void Boss::delayAction(void)
{
    m_time--;
}
//================================================================================
//敵出現
//================================================================================
void Boss::spawnAction(void)
{
    //攻撃
    if(m_time % 50 == 0)
    {
        m_pEnemyManager->spawn(1);
    }
    m_time--;
}
//================================================================================
//ダメージ処理
//================================================================================
void Boss::addDamage(int nDamage)
{
    m_nLife -= nDamage;
}
//================================================================================
// 敵再配置処理
//================================================================================
void Boss::setSpawn(Vec2 pos)
{
    m_bDeath = false;
    m_pos = pos;
    m_pSprite->setPosition(pos);
    m_pSprite->setOpacity(255);
    m_nLife = MAX_LIFE;
    
}
//================================================================================
// 生成処理
//================================================================================
Boss* Boss::create(EnemyManager* pEnemyManager,const Vec2& pos)
{
    // インスタンスの生成
    Boss* pBoss = new Boss();
    
    // メンバ変数の代入
    pBoss->m_pos = pos;
    pBoss->m_pEnemyManager = pEnemyManager;
    // 初期化
    pBoss->init();
    
    return pBoss;
}