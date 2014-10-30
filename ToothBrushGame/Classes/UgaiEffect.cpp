//
//  UgaiEffect.cpp
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/29.
//
//
#include "UgaiEffect.h"
#include "TextureFile.h"
#include "Sound.h"
#include "common.h"
#include "AchievementDataBase.h"
#include "CharacterStatus.h"
//================================================================================
// コンストラクタ
//================================================================================
UgaiEffect::UgaiEffect(void)
{
    
    // メンバ変数の初期化
    m_pSprite = nullptr;
    
    //関数ポインタセット
    m_actionMode = 0;
    m_time = 0;
}

//================================================================================
// デストラクタ
//================================================================================
UgaiEffect::~UgaiEffect()
{
    
}
//================================================================================
// 初期化処理
//================================================================================
bool UgaiEffect::init(void)
{
    
    // スプライトの作成
    m_pSprite = Sprite::create(TEX_UGAI_WATER);
    
    // スプライトの座標設定
    m_pSprite->setPosition(m_pos);
    
    m_pSprite->setOpacity(0);
    
    m_pLayer->addChild(m_pSprite);
    for(int nloop = 0;nloop < MAX_WATER;nloop++)
    {
        // スプライトの作成
        m_pWater[nloop] = Sprite::create(TEX_UGAI_WATER);
        
        // スプライトの座標設定
        m_pWater[nloop]->setPosition(m_pos);
        m_pWater[nloop]->setOpacity(0);
        m_pLayer->addChild(m_pWater[nloop]);
    }
    
    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void UgaiEffect::uninit(void)
{
}

//================================================================================
// 更新処理
//================================================================================
void UgaiEffect::update(void)
{
}
//================================================================================
//行動選択関数
//================================================================================
void UgaiEffect::choiceAction(void)
{
    
}
//================================================================================//
// 敵再配置処理
//================================================================================
void UgaiEffect::setSpawn()
{
    AchievementDataBaseList::addAchievement(ACHIEVEMENT_TYPE_USE_UGAI);
    m_pSprite->stopAllActions();
    m_pSprite->setPosition(m_pos);
    m_pSprite->setOpacity(75);

    Sequence* pSequence = Sequence::create(MoveTo::create(UGAI_DELAY,Vec2(m_pos.x,m_pos.y - m_pSprite->getContentSize().height)), NULL);
    m_pSprite->runAction(pSequence);
}
//================================================================================
// 生成処理
//================================================================================
UgaiEffect* UgaiEffect::create(Layer* pLayer,const Vec2& pos)
{
    // インスタンスの生成
    UgaiEffect* pUgaiEffect = new UgaiEffect();

    // メンバ変数の代入
    pUgaiEffect->m_pos = pos;
    
    pUgaiEffect->m_pLayer = pLayer;
    
    // 初期化
    pUgaiEffect->init();
    
    return pUgaiEffect;
}
