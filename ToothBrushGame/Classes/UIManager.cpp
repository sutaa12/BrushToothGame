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
#include "UIManager.h"
#include "Score.h"
#include "MenuBar.h"
#include "LifeBar.h"
#include "Item.h"

static const int TOOTHMANAGER_DISPLAY_CENTER_X = (320);

//================================================================================
// コンストラクタ
//================================================================================
UIManager::UIManager(void)
{
    // メンバ変数の初期化
    m_pScore = nullptr;
    m_pMenuBar = nullptr;
    m_pLifeBar = nullptr;
    m_pItem = nullptr;
    m_pLayer = nullptr;
}

//================================================================================
// デストラクタ
//================================================================================
UIManager::~UIManager()
{

}

//================================================================================
// 初期化処理
//================================================================================
bool UIManager::init(void)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /**
     *  UI Score Generation
     **/
    // スコア生成
    m_pScore = Score::create(Vec2(0, 0), 1, m_pLayer);

    /**
     *  UI Item Generation
     **/
    // UIアイテム生成処理
    m_pItem = Item::create();
    // スプライトサイズ取得
    Rect itemSpriteRect = m_pItem->getSprite()->getBoundingBox();
    //座標変換(左上を持ってきているため、中心にそろえる処理)
    m_pItem->setPos(Vec2(320, m_pItem->getSprite()->getContentSize().height / 2 + 1));
    // スプライトの再配置
    m_pItem->refreshSpritePos();
    // スプライトの登録
    m_pLayer->addChild(m_pItem->getSprite());

    /**
     *  UI Menubar Generation
     **/
    // UIアイテム生成処理
    m_pMenuBar = MenuBar::create();
    // スプライトサイズ取得
    Rect MenuBarSpriteRect = m_pMenuBar->getSprite()->getBoundingBox();
    //座標変換(左上を持ってきているため、中心にそろえる処理)
    m_pMenuBar->setPos(Vec2(320, visibleSize.height - 32));
    // スプライトの再配置
    m_pMenuBar->refreshSpritePos();
    // スプライトの登録
    m_pLayer->addChild(m_pMenuBar->getSprite());

    
    /**
     *  UI LifeBar Generation
     **/
    // ライフバー生成
    m_pLifeBar = LifeBar::create(m_pLayer,Vec2(320,240));

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
