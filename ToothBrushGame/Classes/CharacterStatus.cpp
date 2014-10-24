//
//  CharacterStatus.cpp
//  ToothBrushGame
//
//  Created by 鈴木愛忠 on 2014/10/22.
//
//
//********************************************************************************
// インクルード
//********************************************************************************
#include "TextureFile.h"
#include "CharacterStatus.h"
//================================================================================
// コンストラクタ
//================================================================================
CharacterStatus::CharacterStatus(void)
{
    // メンバ変数の初期化
    m_pSprite = nullptr;
}

//================================================================================
// デストラクタ
//================================================================================
CharacterStatus::~CharacterStatus()
{

}

//================================================================================
// 初期化処理
//================================================================================
bool CharacterStatus::init(void)
{
    // スプライトの作成
    m_pSprite = Sprite::create("StatusLittleGirl_00.png");

    // エラーチェック
    if(m_pSprite == nullptr)
    {
        // スプライト生成エラー
        return false;
    }

    // スプライトの座標設定
    m_pos.x -= (m_pSprite->getBoundingBox()).size.width / 2;
    m_pos.x -= 16;
    m_pos.y += (m_pSprite->getBoundingBox()).size.height / 2;
    m_pSprite->setPosition(m_pos);

    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void CharacterStatus::uninit(void)
{

}

//================================================================================
// 更新処理
//================================================================================
void CharacterStatus::update(void)
{
    //m_pToothSprite->setPosition(m_pos);


}

//================================================================================
// 生成処理
//================================================================================
CharacterStatus* CharacterStatus::create(const Vec2& startRigthBottomPos,CharacterStatus::CHARACTERSTATUS_PATTERN pattern)
{
    // インスタンスの生成
    CharacterStatus* pCharacterStatus = new CharacterStatus();

    // メンバ変数の代入
    pCharacterStatus->m_pos = startRigthBottomPos;
    pCharacterStatus->m_pattern = pattern;

    // 初期化
    pCharacterStatus->init();

    return pCharacterStatus;
}

//================================================================================
// 幼女表情パターンセット処理
//================================================================================
void CharacterStatus::setPattern(CHARACTERSTATUS_PATTERN pattern)
{
    if (pattern >= CHARACTERSTATUS_PATTERN_MAX)
    {
        return;
    }

    m_pattern = pattern;
    m_pSprite->setTexture(IMAGE_LIST[pattern]);
    setJump(1.0f,Vec2(0,0),60,2);
}

//================================================================================
// ジャンプアクションセット処理
//================================================================================
void CharacterStatus::setJump(float fTime,Vec2 move,int nHigh,int nCount)
{
    auto action = JumpBy::create(fTime,move, nHigh, nCount);
    m_pSprite->runAction(action);
}