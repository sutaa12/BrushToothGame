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
//#include "LifeBar.h"
#include "Clock.h"
#include "Item.h"
#include "ToothPowder.h"
#include "CharacterStatus.h"

//================================================================================
// コンストラクタ
//================================================================================
UIManager::UIManager(void)
{
    // メンバ変数の初期化
    m_pScore = nullptr;
    m_pMenuBar = nullptr;
   // m_pLifeBar = nullptr;
    m_pClock = nullptr;
    m_pLayer = nullptr;
    m_pGameBottomBack = nullptr;
    m_pGameTopBack = nullptr;
    m_pCharacterStatus = nullptr;
}

//================================================================================
// デストラクタ
//================================================================================
UIManager::~UIManager()
{
    SAFE_DELETE(m_pScore);
    SAFE_DELETE(m_pMenuBar);
    //SAFE_DELETE(m_pLifeBar);
    SAFE_DELETE(m_pToothPowder);
    SAFE_DELETE(m_pCharacterStatus);

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
    
    m_pGameBottomBack->setPosition(Vec2(visibleSize.width / 2,origin.y + 160 - m_pGameTopBack->getContentSize().height / 2));
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
    m_pClock = Clock::create(m_pLayer,Vec2(visibleSize.width / 2 + 32, visibleSize.height - 32));

    //歯磨き粉アイテム生成処理
    m_pToothPowder = ToothPowder::create(m_pLayer,Vec2(visibleSize.width / 3,origin.y + 128));

    // キャラクター生成。下部UIの右下から計算
    Rect bottomUIRect = m_pGameBottomBack->getBoundingBox();
    Vec2 characterDispPos = Vec2(origin.x + bottomUIRect.size.width,origin.y);
    m_pCharacterStatus = CharacterStatus::create(characterDispPos,CharacterStatus::CHARACTERSTATUS_PATTERN_CRY);
    m_pLayer->addChild(m_pCharacterStatus->getSprite());

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
    m_pClock->update();
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
