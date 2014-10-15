//********************************************************************************
//  Tooth.cpp
//  test
//
//  Created by 丸山 潤 on 2014/10/08.
//
//********************************************************************************
//********************************************************************************
// インクルード
//********************************************************************************
#include "Tooth.h"

//================================================================================
// コンストラクタ
//================================================================================
Tooth::Tooth(void)
{
    // メンバ変数の初期化
    m_pSprite = nullptr;
}

//================================================================================
// デストラクタ
//================================================================================
Tooth::~Tooth()
{
    
}

//================================================================================
// 初期化処理
//================================================================================
bool Tooth::init(void)
{
    // スプライトの作成
    m_pSprite = Sprite::create("tooth_01.png");
    
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
void Tooth::uninit(void)
{
    
}

//================================================================================
// 更新処理
//================================================================================
void Tooth::update(void)
{
    //m_pToothSprite->setPosition(m_pos);
    
    
}

//================================================================================
// 生成処理
//================================================================================
Tooth* Tooth::create(const Vec2& pos)
{
    // インスタンスの生成
    Tooth* pTooth = new Tooth();
    
    // メンバ変数の代入
    pTooth->m_pos = pos;
    
    // 初期化
    pTooth->init();
    
    return pTooth;
}