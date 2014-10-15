//
//  EnemyManager.cpp
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/15.
//
//


//********************************************************************************
// インクルード
//********************************************************************************
#include "EnemyManager.h"
#include "Enemy.h"

static const int TOOTHMANAGER_DISPLAY_CENTER_X = (320);

//================================================================================
// コンストラクタ
//================================================================================
EnemyManager::EnemyManager(void)
{
    // メンバ変数の初期化
    m_pTopTooth = nullptr;
    m_pBottomTooth = nullptr;
    m_pLayer = nullptr;
}

//================================================================================
// デストラクタ
//================================================================================
EnemyManager::~EnemyManager()
{

}

//================================================================================
// 初期化処理
//================================================================================
bool EnemyManager::init(void)
{
    /*
    // 上歯茎生成
    m_pTopGum = Gum::Create();

    // スプライトサイズ取得
    Rect gumSpriteRect = (m_pTopGum->getSprite()->getBoundingBox());

    // 座標変換(左上を持ってきているため、中心にそろえる処理)
    m_pTopGum->setPos(Vec2(TOOTHMANAGER_DISPLAY_CENTER_X,
                           m_startLeftTopPos.y - (gumSpriteRect.size.height / 2)));

    // スプライトの再配置
    m_pTopGum->RefreshSpritePos();

    // スプライトの登録
    m_pLayer->addChild(m_pTopGum->getSprite());

    // 上歯生成処理
    m_pTopTooth = Tooth::Create();

    // スプライトサイズ取得
    Rect toothSpriteRect = m_pTopTooth->getSprite()->getBoundingBox();

    // 座標変換
    m_pTopTooth->setPos(TOOTHMANAGER_DISPLAY_CENTER_X,
                        m_pTopGum->getPos().y - gumSpriteRect.size.height / 2 - (toothSpriteRect.size.height / 2));

    // スプライトの再配置
    m_pTopTooth->RefreshSpritePos();

    // スプライトの登録
    m_pLayer->addChild(m_pTopTooth->getSprite());


    // 下歯生成処理
    m_pBottomTooth = Tooth::Create(Vec2(TOOTHMANAGER_DISPLAY_CENTER_X,
                                        m_pTopTooth->getPos().y - toothSpriteRect.size.height));

    // スプライトの回転
    m_pBottomTooth->getSprite()->setRotation(180);

    // スプライトの登録
    m_pLayer->addChild(m_pBottomTooth->getSprite());

    // 下歯茎生成処理
    m_pBottomGum = Gum::Create(Vec2(TOOTHMANAGER_DISPLAY_CENTER_X,
                                    m_pBottomTooth->getPos().y - toothSpriteRect.size.height / 2 - gumSpriteRect.size.height / 2));

    // スプライトの登録
    m_pLayer->addChild(m_pBottomGum->getSprite());
     
    */
    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void EnemyManager::uninit(void)
{

}

//================================================================================
// 更新処理
//================================================================================
void EnemyManager::update(void)
{
}

//================================================================================
// 生成処理
//================================================================================
EnemyManager* EnemyManager::create(const Vec2& startLeftTopPos,Layer* layer)
{
    // 歯マネージャーのインスタンス化
    EnemyManager* pEnemyManager = new EnemyManager();

    // メンバー変数の代入
    pEnemyManager->m_startLeftTopPos = startLeftTopPos;
    pEnemyManager->m_pLayer = layer;

    // 初期化
    pEnemyManager->init();

    return pEnemyManager;
}


//================================================================================
// 消滅処理
//================================================================================
void EnemyManager::disappear(const Vec2& vec)
{
    /*
    m_pTopGum->addPos(vec);
    m_pTopGum->RefreshSpritePos();

    m_pTopTooth->addPos(vec);
    m_pTopTooth->RefreshSpritePos();
     */
}

//================================================================================
// 行動処理
//================================================================================
void EnemyManager::action(const Vec2& vec)
{
    /*
     m_pTopGum->addPos(vec);
     m_pTopGum->RefreshSpritePos();

     m_pTopTooth->addPos(vec);
     m_pTopTooth->RefreshSpritePos();
     */
}
//================================================================================
// 攻撃処理
//================================================================================
void EnemyManager::attack(const Vec2& vec)
{
    /*
     m_pTopGum->addPos(vec);
     m_pTopGum->RefreshSpritePos();

     m_pTopTooth->addPos(vec);
     m_pTopTooth->RefreshSpritePos();
     */
}

//================================================================================
// 移動処理
//================================================================================
void EnemyManager::move(const Vec2& vec)
{
    /*
     m_pTopGum->addPos(vec);
     m_pTopGum->RefreshSpritePos();

     m_pTopTooth->addPos(vec);
     m_pTopTooth->RefreshSpritePos();
     */
}

//================================================================================
// 敵生成処理
//================================================================================
void EnemyManager::spawn(const Vec2& vec)
{
    /*
     m_pTopGum->addPos(vec);
     m_pTopGum->RefreshSpritePos();

     m_pTopTooth->addPos(vec);
     m_pTopTooth->RefreshSpritePos();
     */
}

//================================================================================
// ダメージ判定処理
//================================================================================
void EnemyManager::checkDamage(const Vec2& vec)
{
    /*
     m_pTopGum->addPos(vec);
     m_pTopGum->RefreshSpritePos();

     m_pTopTooth->addPos(vec);
     m_pTopTooth->RefreshSpritePos();
     */
}

