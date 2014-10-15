//********************************************************************************
//  ToothManager.cpp
//  test
//
//  Created by 丸山 潤 on 2014/10/08.
//
//********************************************************************************
//********************************************************************************
// インクルード
//********************************************************************************
#include "ToothManager.h"
#include "Tooth.h"
#include "Gum.h"

static const int TOOTHMANAGER_DISPLAY_CENTER_X = (320);

//================================================================================
// コンストラクタ
//================================================================================
ToothManager::ToothManager(void)
{
    // メンバ変数の初期化
    m_pTopTooth = nullptr;
    m_pBottomTooth = nullptr;
    m_pLayer = nullptr;
}

//================================================================================
// デストラクタ
//================================================================================
ToothManager::~ToothManager()
{

}

//================================================================================
// 初期化処理
//================================================================================
bool ToothManager::init(void)
{
    // 上歯茎生成
    m_pTopGum = Gum::create();
    
    // スプライトサイズ取得
    Rect gumSpriteRect = (m_pTopGum->getSprite()->getBoundingBox());
    
    // 座標変換(左上を持ってきているため、中心にそろえる処理)
    m_pTopGum->setPos(Vec2(TOOTHMANAGER_DISPLAY_CENTER_X,
                           m_startLeftTopPos.y - (gumSpriteRect.size.height / 2)));
    
    // スプライトの再配置
    m_pTopGum->refreshSpritePos();

    // スプライトの登録
    m_pLayer->addChild(m_pTopGum->getSprite());

    // 上歯生成処理
    m_pTopTooth = Tooth::create();
    
    // スプライトサイズ取得
    Rect toothSpriteRect = m_pTopTooth->getSprite()->getBoundingBox();
    
    // 座標変換
    m_pTopTooth->setPos(TOOTHMANAGER_DISPLAY_CENTER_X,
                        m_pTopGum->getPos().y - gumSpriteRect.size.height / 2 - (toothSpriteRect.size.height / 2));
    
    // スプライトの再配置
    m_pTopTooth->refreshSpritePos();
    
    // スプライトの登録
    m_pLayer->addChild(m_pTopTooth->getSprite());
    
    
    // 下歯生成処理
    m_pBottomTooth = Tooth::create(Vec2(TOOTHMANAGER_DISPLAY_CENTER_X,
                                        m_pTopTooth->getPos().y - toothSpriteRect.size.height));
    
    // スプライトの回転
    m_pBottomTooth->getSprite()->setRotation(180);
    
    // スプライトの登録
    m_pLayer->addChild(m_pBottomTooth->getSprite());
    
    // 下歯茎生成処理
    m_pBottomGum = Gum::create(Vec2(TOOTHMANAGER_DISPLAY_CENTER_X,
                                    m_pBottomTooth->getPos().y - toothSpriteRect.size.height / 2 - gumSpriteRect.size.height / 2));
    
    // スプライトの登録
    m_pLayer->addChild(m_pBottomGum->getSprite());
 
    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void ToothManager::uninit(void)
{

}

//================================================================================
// 更新処理
//================================================================================
void ToothManager::update(void)
{
}

//================================================================================
// 生成処理
//================================================================================
ToothManager* ToothManager::Create(const Vec2& startLeftTopPos,Layer* layer)
{
    // 歯マネージャーのインスタンス化
    ToothManager* pToothManager = new ToothManager();
    
    // メンバー変数の代入
    pToothManager->m_startLeftTopPos = startLeftTopPos;
    pToothManager->m_pLayer = layer;
    
    // 初期化
    pToothManager->init();
    
    return pToothManager;
}

//================================================================================
// 上歯茎と上歯の座標を足す
//================================================================================
void ToothManager::addTopGumPosAndTopToothPos(const Vec2& vec)
{
    m_pTopGum->addPos(vec);
    m_pTopGum->refreshSpritePos();
    
    m_pTopTooth->addPos(vec);
    m_pTopTooth->refreshSpritePos();
}

//================================================================================
// 下歯茎と下歯の座標を足す
//================================================================================
void ToothManager::addBottomGumPosAndBottomToothPos(const Vec2& vec)
{
    m_pBottomGum->addPos(vec);
    m_pBottomGum->refreshSpritePos();
    
    m_pBottomTooth->addPos(vec);
    m_pBottomTooth->refreshSpritePos();
}




