//
//  Enemy.cpp
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/14.
//
//

#include "Enemy.h"
#include "Random.h"
//ベクトルの最大値チェック　超えていたら押し戻す
template <class T1,class T2>
inline void CHECK_MAX_POS(T1 &vec0,T2 &vecMin,T2 &vecMax)
{
    if(vec0 >= vecMax)
    {
        vec0 = vecMax;
    }else
        if(vec0 <= vecMin)
        {
            vec0 = vecMin;
        }
}

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
    m_pFunc[2] = &Enemy::attackAction;
    m_pFunc[3] = &Enemy::delayAction;
    m_actionMode = 0;
    m_time = 0;
    
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
    m_pSprite = Sprite::create("Enemy.png");

    // エラーチェック
    if(m_pSprite == nullptr)
    {
        // スプライト生成エラー
        return false;
    }

    // スプライトの座標設定
    m_pSprite->setPosition(m_pos);

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
// 更新処理
//================================================================================
void Enemy::update(void)
{
    //状態に応じた処理開始
    (this->*m_pFunc[m_actionMode])();
    //タイムが0なら強制的に行動させる
    if(m_time <= 0)
    {
        m_time = 0;
        m_actionMode = ACTION_NONE;
    }
}
//================================================================================
//行動選択関数
//================================================================================
void Enemy::choiceAction(void)
{
    m_actionMode = RandomMT::getRandom(0, ACTION_MAX - 1);
    m_time = RandomMT::getRandom(0, Enemy::MAX_TIME);
    m_move = Vec2(RandomMT::getRandom(0,Enemy::MAX_MOVE),RandomMT::getRandom(0,Enemy::MAX_MOVE));
}
//================================================================================
//移動
//================================================================================
void Enemy::moveAction(void)
{
    Vec2 minSize = Vec2(Enemy::MIN_X + m_pSprite->getContentSize().width / 2,Enemy::MIN_Y + m_pSprite->getContentSize().height / 2);
    Vec2 maxSize = Vec2(Enemy::MAX_X - m_pSprite->getContentSize().width / 2,Enemy::MAX_Y - m_pSprite->getContentSize().height / 2);

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
// 生成処理
//================================================================================
Enemy* Enemy::create(const Vec2& pos)
{
    // インスタンスの生成
    Enemy* pEnemy = new Enemy();

    // メンバ変数の代入
    pEnemy->m_pos = pos;

    // 初期化
    pEnemy->init();
    
    return pEnemy;
}
