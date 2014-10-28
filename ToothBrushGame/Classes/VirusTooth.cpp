//
//  VirusTooth.cpp
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/28.
//
//

#include "VirusTooth.h"
#include "TextureFile.h"
#include "Sound.h"
#include "VirusTooth.h"
#include "Random.h"
#include "common.h"
#include "LifeBar.h"
#include "Score.h"
#include "AchievementDataBase.h"
//================================================================================
// コンストラクタ
//================================================================================
VirusTooth::VirusTooth(void)
{
    
    // メンバ変数の初期化
    m_pSprite = nullptr;
    
    //関数ポインタセット
    m_actionMode = 0;
    m_time = 0;
    m_bDeath = true;
    m_bDown = true;
}

//================================================================================
// デストラクタ
//================================================================================
VirusTooth::~VirusTooth()
{
    
}
//================================================================================
// 初期化処理
//================================================================================
bool VirusTooth::init(void)
{
    
    // スプライトの作成
    m_pSprite = Sprite::create(TEX_PLAQUE_WAIT_01);
    
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
void VirusTooth::uninit(void)
{
}

//================================================================================
//倒される処理
//================================================================================
void VirusTooth::disappear(void)
{
    
    //死亡フラグセット
    m_bDeath = true;
    m_bDown = true;
    
    //画像をきり替え
    m_pSprite->setColor(Color3B::GRAY);
    
    m_pSprite->runAction(Spawn::create(FadeOut::create(0.8),Sequence::create(ScaleTo::create(0.01f,0.01),ScaleTo::create(0.5f,1.0), NULL) ,NULL));

}
//================================================================================
// 更新処理
//================================================================================
void VirusTooth::update(void)
{
}
//================================================================================
//行動選択関数
//================================================================================
void VirusTooth::choiceAction(void)
{
    
}
//================================================================================//================================================================================
// 敵再配置処理
//================================================================================
void VirusTooth::setSpawn(Vec2 pos)
{
    m_pSprite->stopAllActions();
    m_bDeath = false;
    m_pos = pos;
    m_pSprite->setPosition(pos);
    m_pSprite->setOpacity(255);

    m_bDown = false;
    m_pSprite->setColor(Color3B::GRAY);
    m_pSprite->setScale(1.0f);
    
    Sequence* pSequence = Sequence::create(ScaleTo::create(2.0f,1.0f,1.5f),ScaleTo::create(2.0f,1.0f,1.0f), NULL);
    m_pSprite->runAction(RepeatForever::create(pSequence));

    
}
//================================================================================
// 生成処理
//================================================================================
VirusTooth* VirusTooth::create(const Vec2& pos)
{
    // インスタンスの生成
    VirusTooth* pVirusTooth = new VirusTooth();
    
    // メンバ変数の代入
    pVirusTooth->m_pos = pos;
    
    
    // 初期化
    pVirusTooth->init();
    
    return pVirusTooth;
}
