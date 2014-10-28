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
    m_bGiddy = false;
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
    m_pSprite = Sprite::create(TEX_LITTLEGIRL_CRY);

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
// パターン変更チェック処理
//================================================================================
void CharacterStatus::checkChangePattern(int nEnemyAllNum, int nEnemyDownNum)
{
    int nChangeBorder = nEnemyAllNum / 4;

    if(nChangeBorder == 0)
    {
    	return;
    }

    int nPattern = nEnemyDownNum / nChangeBorder;
    if(nPattern == m_pattern)
    {
        return;
    }

    switch (nPattern)
    {
        case 0:
            setPattern(CHARACTERSTATUS_PATTERN_CRY);
            break;

        case 1:
            setPattern(CHARACTERSTATUS_PATTERN_NORMAL);
            break;

        case 2:
            setPattern(CHARACTERSTATUS_PATTERN_SMAILE);
            break;

        case 3:
            setPattern(CHARACTERSTATUS_PATTERN_GLAD);
            break;

        default:
            break;
    }
}

//================================================================================
// 幼女表情パターンセット処理
//================================================================================
void CharacterStatus::setPattern(CHARACTERSTATUS_PATTERN pattern)
{
    if (pattern >= CHARACTERSTATUS_PATTERN_MAX || pattern < 0)
    {
        return;
    }

    if(m_bGiddy == true)
    {
        return;
    }

    m_oldPattern = m_pattern;
    m_pattern = pattern;
    m_pSprite->setTexture(IMAGE_LIST[pattern]);

    // 目眩時
    if(m_pattern == CHARACTERSTATUS_PATTERN_GIDDY)
    {
        setGiddy();
    }
    else
    {
        setJump(1.0f,Vec2(0,0),60,2);
    }
}

//================================================================================
// ジャンプアクションセット処理
//================================================================================
void CharacterStatus::setJump(float fTime,Vec2 move,int nHigh,int nCount)
{
    auto action = JumpBy::create(fTime,move, nHigh, nCount);
    m_pSprite->runAction(action);
}

//================================================================================
// 目眩アクションセット処理
//================================================================================
void CharacterStatus::setGiddy(void)
{
    m_bGiddy = true;

    auto actionJump = JumpBy::create(0.5f,Vec2(0,0),30,1);
    auto actionDelay = DelayTime::create(0.5f);
    CallFunc *func = CallFunc::create(CC_CALLBACK_0(CharacterStatus::recoveryGiddy, this));
    m_pSprite->runAction(Sequence::create(actionJump,actionDelay,func, NULL));
}

//================================================================================
// 目眩アクション復帰処理
//================================================================================
void CharacterStatus::recoveryGiddy(void)
{
    m_pSprite->setTexture(IMAGE_LIST[m_oldPattern]);
    m_pattern = m_oldPattern;
    m_bGiddy = false;
}


