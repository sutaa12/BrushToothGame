//
//  ToothPowder.cpp
//  ToothBrushGame
//
//  Created by 鈴木愛忠 on 2014/10/22.
//
//

//********************************************************************************
// インクルード
//********************************************************************************
#include "TextureFile.h"
#include "Sound.h"
#include "ToothPowder.h"

//================================================================================
// コンストラクタ
//================================================================================
ToothPowder::ToothPowder(void)
{
    // メンバ変数の初期化
    m_pSprite = nullptr;
}

//================================================================================
// デストラクタ
//================================================================================
ToothPowder::~ToothPowder()
{
    
}
//================================================================================
// 終了処理
//================================================================================
void ToothPowder::disappear(void)
{
    m_pItemIcon->setPosition(m_pos);
    m_pItemIcon->setOpacity(0);
    m_bPowderTouchFlag = false;
}


//================================================================================
// 初期化処理
//================================================================================
bool ToothPowder::init(void)
{
    m_bPowderTouchFlag = false;

    // スプライトの作成
    m_pSprite = Sprite::create(TEX_BUTTON_ITEM_TOOTHPOWDER);
    m_pItemIcon = Sprite::create(TEX_ITEM_TOOTHPOWDER);
    // エラーチェック
    if(m_pSprite == nullptr)
    {
        // スプライト生成エラー
        return false;
    }
    
    // スプライトの座標設定
    m_pSprite->setPosition(m_pos);
    m_pSprite->setScale(2.0f,1.5f);

    m_pItemIcon->setPosition(m_pos);
    m_pItemIcon->setOpacity(0);
    
    m_pLayer->addChild(m_pSprite);
    m_pLayer->addChild(m_pItemIcon);
    
    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void ToothPowder::uninit(void)
{
    
}

//================================================================================
// 更新処理
//================================================================================
void ToothPowder::update(void)
{
    //m_pToothSprite->setPosition(m_pos);
    
    
}

//================================================================================
// 生成処理
//================================================================================
ToothPowder* ToothPowder::create(Layer* pLayer,const Vec2& pos)
{
    // インスタンスの生成
    ToothPowder* pToothPowder = new ToothPowder();
    
    // メンバ変数の代入
    pToothPowder->m_pos = pos;
    pToothPowder->m_pLayer = pLayer;
    // 初期化
    pToothPowder->init();
    
    return pToothPowder;
}
//================================================================================
// アイコン移動
//================================================================================
void ToothPowder::setPos(Vec2 pos)
{
    m_pItemIcon->setOpacity(90);
    m_pItemIcon->setPosition(pos);
}
//================================================================================
// 判定チェック
//================================================================================
void ToothPowder::chkPowderTouchFlag(Point pos)
{
    Rect rectPowder = Rect(m_pSprite->getBoundingBox());
    if(rectPowder.containsPoint(pos))
    {
        m_bPowderTouchFlag = true;
    }
    
}