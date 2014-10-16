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
    m_pItem->setPos(Vec2(TOOTHMANAGER_DISPLAY_CENTER_X,
                         0 + itemSpriteRect.size.height / 2 ));
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
    m_pMenuBar->setPos(Vec2(TOOTHMANAGER_DISPLAY_CENTER_X,
                         m_startLeftTopPos.y - (MenuBarSpriteRect.size.height / 2)));
    // スプライトの再配置
    m_pMenuBar->refreshSpritePos();
    // スプライトの登録
    m_pLayer->addChild(m_pMenuBar->getSprite());

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
}

//================================================================================
// 生成処理
//================================================================================
UIManager* UIManager::create(const Vec2& startLeftTopPos,Layer* layer)
{
    // 歯マネージャーのインスタンス化
    UIManager* pUIManager = new UIManager();

    // メンバー変数の代入
    pUIManager->m_startLeftTopPos = startLeftTopPos;
    pUIManager->m_pLayer = layer;

    // 初期化
    pUIManager->init();

    return pUIManager;
}
/*
//================================================================================
// 上歯茎と上歯の座標を足す
//================================================================================
void UIManager::addTopGumPosAndTopToothPos(const Vec2& vec)
{
    m_pTopGum->addPos(vec);
    m_pTopGum->refreshSpritePos();

    m_pTopTooth->addPos(vec);
    m_pTopTooth->refreshSpritePos();
}

//================================================================================
// 下歯茎と下歯の座標を足す
//================================================================================
void UIManager::addBottomGumPosAndBottomToothPos(const Vec2& vec)
{
    m_pBottomGum->addPos(vec);
    m_pBottomGum->refreshSpritePos();

    m_pBottomTooth->addPos(vec);
    m_pBottomTooth->refreshSpritePos();
}

//================================================================================
// 上下歯を動かす
//================================================================================
void UIManager::moveToothAndGum(float time, Vec2 pos)
{
    //仮の座標に画像のPosを加算する
    m_pTopTooth->addPos(pos);
    m_pBottomTooth->addPos(pos * -1);
    m_pTopGum->addPos(pos);
    m_pBottomGum->addPos(pos * -1);
    //m_pTopTooth->RefreshSpritePos();

    Vec2 TopToothPos = m_pTopTooth->getPos();
    Vec2 BottomToothPos = m_pBottomTooth->getPos();

    Vec2 TopGumPos = m_pTopGum->getPos();
    Vec2 BottomGumPos = m_pBottomGum->getPos();

    //歯
    m_pTopTooth->getSprite()->runAction(MoveTo::create(1.0f, TopToothPos));
    m_pBottomTooth->getSprite()->runAction(MoveTo::create(1.0f, BottomToothPos));
    //歯茎
    m_pTopGum->getSprite()->runAction(MoveTo::create(1.0f, TopGumPos));
    m_pBottomGum->getSprite()->runAction(MoveTo::create(1.0f, BottomGumPos));
    
}
*/
