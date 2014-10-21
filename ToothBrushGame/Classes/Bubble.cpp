//
//  Bubble.cpp
//  ToothBrushGame
//
//  Created by 鈴木愛忠 on 2014/10/17.
//
//
#include "TextureFile.h"
#include "Bubble.h"
#include "Random.h"
#include "common.h"
#include "LifeBar.h"
//================================================================================
// コンストラクタ
//================================================================================
Bubble::Bubble(void)
{
    // メンバ変数の初期化
    m_pSprite = nullptr;
    
    //関数ポインタセット
    m_actionMode = 0;
    m_time = 0;
    m_nLife = 0;
}

//================================================================================
// デストラクタ
//================================================================================
Bubble::~Bubble()
{
    
}

//================================================================================
// 初期化処理
//================================================================================
bool Bubble::init(void)
{
    // スプライトの作成
    m_pSprite = Sprite::create(TEX_BUBBLE_01);
    
    // エラーチェック
    if(m_pSprite == nullptr)
    {
        // スプライト生成エラー
        return false;
    }
    
    m_bDeath = true;
    // スプライトの座標設定
    m_pSprite->setPosition(m_pos);
    
    m_pSprite->setOpacity(0);
    
    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void Bubble::uninit(void)
{
}

//================================================================================
//消滅処理
//================================================================================
void Bubble::disappear(void)
{
    m_pos += m_move;
    getSprite()->setPosition(m_pos);

    m_nLife = 0;
    short uOpacity = m_pSprite->getOpacity();
    if(uOpacity > 0)
    {
        uOpacity -= m_time;
    }
    if(uOpacity <= 0)
    {
        m_bDeath = true;
        uOpacity = 0;
        m_time = 0;
    }

    m_pSprite->setOpacity(uOpacity);
}
//================================================================================
// 更新処理
//================================================================================
void Bubble::update(void)
{
    if(!m_bDeath)
    {
        disappear();
    }
}
//================================================================================
// 敵再配置処理
//================================================================================
void Bubble::setSpawn(Vec2 pos,Color3B col)
{
    m_bDeath = false;
    m_pos = pos;
    m_pSprite->setPosition(pos);
    m_pSprite->setOpacity(255);
    m_time = RandomMT::getRandom(30, MAX_TIME);
    m_nLife = RandomMT::getRaodom(1, MAX_LIFE);
    m_move = Vec2(RandomMT::getRandom(-Bubble::MAX_MOVE,Bubble::MAX_MOVE),RandomMT::getRandom(1,Bubble::MAX_MOVE));
    m_pSprite->setColor(col);
    float fSize = RandomMT::getRandom(0.25,0.03);
    m_pSprite->setScale(fSize, fSize);
}
//================================================================================
// 生成処理
//================================================================================
Bubble* Bubble::create(const Vec2& pos)
{
    // インスタンスの生成
    Bubble* pBubble = new Bubble();
    
    // メンバ変数の代入
    pBubble->m_pos = pos;
    
    // 初期化
    pBubble->init();
    
    return pBubble;
}