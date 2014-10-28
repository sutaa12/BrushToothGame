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
    m_bPatternChangeEnd = false;
    m_pattern = m_oldPattern = CHARACTERSTATUS_PATTERN_CRY;
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
	// パターンを更新する必要がないならば処理をしない
	if(m_bPatternChangeEnd)
	{
		return;
	}
    int nChangeBorder = nEnemyAllNum / 4;

    // 0割対策
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
            m_pattern = CHARACTERSTATUS_PATTERN_CRY;
            break;

        case 1:
            m_pattern = CHARACTERSTATUS_PATTERN_NORMAL;
            break;

        case 2:
            m_pattern = CHARACTERSTATUS_PATTERN_SMAILE;
            break;

        case 3:
        	// クリア時に変更するためここで変更する必要なし。
            //m_pattern = CHARACTERSTATUS_PATTERN_GLAD;
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

    m_pSprite->setTexture(IMAGE_LIST[pattern]);

    // 目眩時
    if(pattern == CHARACTERSTATUS_PATTERN_GIDDY)
    {
        setGiddy();
        return;
    }

    bool bJump = false;

    // 目眩をする前の表情と違う場合
    if(m_oldPattern != m_pattern)
    {
        bJump = true;
    }

    m_oldPattern = m_pattern;
    m_pattern = pattern;

    if(bJump)
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

    auto actionDelay = DelayTime::create(1.0f);
    CallFunc *func = CallFunc::create(CC_CALLBACK_0(CharacterStatus::recoveryGiddy, this));
    m_pSprite->runAction(Sequence::create(actionDelay,func, NULL));
}

//================================================================================
// 目眩アクション復帰処理
//================================================================================
void CharacterStatus::recoveryGiddy(void)
{
    m_bGiddy = false;
    setPattern(m_pattern);
}

//================================================================================
// 現在パターン取得処理
//================================================================================
CharacterStatus::CHARACTERSTATUS_PATTERN CharacterStatus::getPattern(void)
{
    // 目眩時はメンバ変数に入っていないので直接値を返す
	if(m_bGiddy)
	{
		return CHARACTERSTATUS_PATTERN_GIDDY;
	}

	return m_pattern;
}

//================================================================================
// 無限ジャンプセット処理
//================================================================================
void CharacterStatus::setAnimJumpInfinity(float fTime,Vec2 move,int nHigh)
{
	m_pSprite->stopAllActions();

    auto action = JumpBy::create(fTime, move, nHigh, 1);

    m_pSprite->runAction(RepeatForever::create(action));

}
