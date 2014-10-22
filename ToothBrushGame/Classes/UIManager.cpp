//
//  UIManager.cpp
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/16.
//
//

//********************************************************************************
// インクルード
//********************************************************************************
#include "TextureFile.h"
#include "common.h"
#include "UIManager.h"
#include "Score.h"
#include "MenuBar.h"
#include "LifeBar.h"
#include "Item.h"

//================================================================================
// コンストラクタ
//================================================================================
UIManager::UIManager(void)
{
    // メンバ変数の初期化
    m_pScore = nullptr;
    m_pMenuBar = nullptr;
    m_pLifeBar = nullptr;
    m_pLayer = nullptr;
    m_pGameBottomBack = nullptr;
    m_pGameTopBack = nullptr;
}

//================================================================================
// デストラクタ
//================================================================================
UIManager::~UIManager()
{
    SAFE_DELETE(m_pScore);
    SAFE_DELETE(m_pMenuBar);
    SAFE_DELETE(m_pLifeBar);
}

//================================================================================
// 初期化処理
//================================================================================
bool UIManager::init(void)
{
    Size visibleSize = Director::getInstance()->getVisibleSize() / 2 + SCREEN_CENTER;
    Vec2 origin = Director::getInstance()->getVisibleSize() / 2 - SCREEN_CENTER;

    /**
     *  UI Score Generation
     **/
    
    m_pGameBottomBack = Sprite::create(TEX_GAME_BOTTOM_BACK);

    m_pGameTopBack = Sprite::create(TEX_GAME_TOP_BACK);
    
    m_pGameBottomBack->setPosition(Vec2(visibleSize.width / 2,origin.y + GAME_MENU_BOTTOM_Y - m_pGameTopBack->getContentSize().height / 2));
    m_pLayer->addChild(m_pGameBottomBack);
    
    m_pGameTopBack->setPosition(Vec2(visibleSize.width / 2,visibleSize.height - m_pGameTopBack->getContentSize().height / 2));
    m_pLayer->addChild(m_pGameTopBack);
    
    // スコア生成
    m_pScore = Score::create(Vec2(100, visibleSize.height - 32), 1, m_pLayer);

    /**
     *  UI Menubar Generation
     **/
    // UIアイテム生成処理
    m_pMenuBar = MenuBar::create();
    // スプライトサイズ取得
    Rect MenuBarSpriteRect = m_pMenuBar->getSprite()->getBoundingBox();
    //座標変換(左上を持ってきているため、中心にそろえる処理)
    m_pMenuBar->setPos(Vec2(565, visibleSize.height - 32));
    // スプライトの再配置
    m_pMenuBar->refreshSpritePos();
    // スプライトの登録
    m_pLayer->addChild(m_pMenuBar->getSprite());
    
    /**
     *  UI LifeBar Generation
     **/
    // ライフバー生成  画面左上から計算し直打ち
    m_pLifeBar = LifeBar::create(m_pLayer,Vec2(320, visibleSize.height - 704 - 16));

    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void UIManager::uninit(void)
{

}

//================================================================================
// 更新処理
//================================================================================
void UIManager::update(void)
{
    m_pLifeBar->update();
    m_pScore->update();
}

//================================================================================
// 生成処理
//================================================================================
UIManager* UIManager::create(Layer* layer)
{
    // 歯マネージャーのインスタンス化
    UIManager* pUIManager = new UIManager();

    // メンバー変数の代入
    pUIManager->m_pLayer = layer;

    // 初期化
    pUIManager->init();

    return pUIManager;
}
