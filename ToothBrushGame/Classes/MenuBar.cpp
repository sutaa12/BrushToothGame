//
//  MenuBar.cpp
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/16.
//
//


//********************************************************************************
// インクルード
//********************************************************************************
#include "TextureFile.h"
#include "Sound.h"
#include "MenuBar.h"
#include "PauseScene.h"

//================================================================================
// コンストラクタ
//================================================================================
MenuBar::MenuBar(void)
{
    // メンバ変数の初期化
    m_pSpriteBase = nullptr;
    m_pMenuItemSprite = nullptr;
    m_pPauseTagetLayer = nullptr;
    m_bPausePermission = true;
}

//================================================================================
// デストラクタ
//================================================================================
MenuBar::~MenuBar()
{

}

//================================================================================
// 初期化処理
//================================================================================
bool MenuBar::init(void)
{
    // スプライトの作成
    m_pSpriteBase = Sprite::create(TEX_MENU_BUTTON);
    Sprite* pSpriteSelected = Sprite::create(TEX_MENU_BUTTON);

    // エラーチェック
    if(m_pSpriteBase == nullptr || pSpriteSelected == nullptr)
    {
        // スプライト生成エラー
        return false;
    }

    pSpriteSelected->setColor(Color3B(200,200,200));

    m_pMenuItemSprite = MenuItemSprite::create(m_pSpriteBase, pSpriteSelected, CC_CALLBACK_0(MenuBar::menuCallback, this));
    m_pMenuItemSprite->setPosition(m_pos);
    m_pMenu = Menu::create(m_pMenuItemSprite, NULL);
    m_pMenu->setPosition(Vec2::ZERO);

    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void MenuBar::uninit(void)
{

}

//================================================================================
// 更新処理
//================================================================================
void MenuBar::update(void)
{
    //m_pToothSprite->setPosition(m_pos);

}

//================================================================================
// 生成処理
//================================================================================
MenuBar* MenuBar::create(Layer* pPauseTagetLayer,const Vec2& pos)
{
    // インスタンスの生成
    MenuBar* pMenuBar = new MenuBar();

    // メンバ変数の代入
    pMenuBar->m_pos = pos;
    pMenuBar->m_pPauseTagetLayer = pPauseTagetLayer;

    // 初期化
    pMenuBar->init();
    
    return pMenuBar;
}

//================================================================================
// メニューアイテムスプライト位置リフレッシュ処理
//================================================================================
void MenuBar::refreshSpritePos(void)
{
    m_pMenuItemSprite->setPosition(m_pos);
}

//================================================================================
// コールバック
//================================================================================
void MenuBar::menuCallback(void)
{
    // ポーズ対象がいなかったらコールバックを抜ける
    if(m_pPauseTagetLayer == nullptr)
    {
        return;
    }

    // ポーズが許可されていないならコールバックを抜ける
    if(m_bPausePermission == false)
    {
        return;
    }

    SimpleAudioEngine::getInstance()->setEffectsVolume(SE_VOLUME_HALF);
    SimpleAudioEngine::getInstance()->playEffect(SE_BUTTON_1);

    Layer* pPauseLayer = PauseScene::createLayer();
    m_pPauseTagetLayer->addChild(pPauseLayer);
    m_pPauseTagetLayer->pause();
}

void MenuBar::setPausePermission(bool bFlg)
{
    m_bPausePermission = bFlg;

    if(m_bPausePermission == false)
    {
        m_pMenuItemSprite->setEnabled(false);
    }
    else
    {
        m_pMenuItemSprite->setEnabled(true);
    }
}



