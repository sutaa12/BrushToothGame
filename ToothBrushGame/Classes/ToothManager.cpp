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
    m_pTopToothSprite = nullptr;
    m_pBottomToothSprite = nullptr;
    m_pLayer = nullptr;
}

//================================================================================
// デストラクタ
//================================================================================
ToothManager::~ToothManager()
{
//    delete[] m_pBottomTooth;
//    delete[] m_pTopTooth;
}

//================================================================================
// 初期化処理
//================================================================================
bool ToothManager::init(void)
{
    // 歯の数分動的確保
    m_pBottomTooth = new Tooth[m_nBottomToothNum];
    m_pTopTooth = new Tooth[m_nTopToothNum];
    
    // 上歯茎生成
    /*m_pTopGumSprite = Sprite::create("haguki.png");                                                             // スプライト生成
    Rect gumSpriteRect = (m_pTopGumSprite->getBoundingBox());                                                   // スプライトサイズ取得
    m_topGumPos = Vec2(TOOTHMANAGER_DISPLAY_CENTER_X,m_startLeftTopPos.y - (gumSpriteRect.size.height / 2));    // スプライト座標算出
    m_pTopGumSprite->setPosition(m_topGumPos);                                                     // スプライト座標設定
   */
    // 上歯茎生成
    m_pTopGum = Gum::Create();
    
    // スプライトサイズ取得
    Rect gumSpriteRect = (m_pTopGum->getSprite()->getBoundingBox());
    
    // 座標変換(左上を持ってきているため、中心にそろえる処理)
    m_pTopGum->setPos(Vec2(TOOTHMANAGER_DISPLAY_CENTER_X,m_startLeftTopPos.y - (gumSpriteRect.size.height / 2)));
    m_pTopGum->RefreshSpritePos();

    // スプライト登録
    m_pLayer->addChild(m_pTopGum->getSprite());


    // 上歯生成処理
    m_pTopToothSprite = Sprite::create("tooth_01.png");
    Rect toothSpriteRect = (m_pTopToothSprite->getBoundingBox());
    m_topToothPos = Vec2(TOOTHMANAGER_DISPLAY_CENTER_X, m_topGumPos.y - gumSpriteRect.size.height / 2 - (toothSpriteRect.size.height / 2));
    m_pTopToothSprite->setPosition(m_topToothPos.x,m_topToothPos.y);
    m_pLayer->addChild(m_pTopToothSprite);
    
    // 下歯生成処理
    m_pBottomToothSprite = Sprite::create("tooth_01.png");
    m_bottomToothPos = Vec2(TOOTHMANAGER_DISPLAY_CENTER_X,
                       m_topToothPos.y - (toothSpriteRect.size.height));
    m_pBottomToothSprite->setPosition(m_bottomToothPos.x,m_bottomToothPos.y);
    m_pBottomToothSprite->setRotation(180);
    m_pLayer->addChild(m_pBottomToothSprite);
   
    // 下歯茎生成
    m_pBottomGumSprite = Sprite::create("haguki.png");
    m_bottomGumPos = Vec2(TOOTHMANAGER_DISPLAY_CENTER_X,m_bottomToothPos.y - toothSpriteRect.size.height / 2 - gumSpriteRect.size.height / 2);
    m_pBottomGumSprite->setPosition(m_bottomGumPos);
    m_pLayer->addChild(m_pBottomGumSprite);
    
    
    
    
    

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
//    // 歯の更新
//    for(int nCnt = 0;nCnt < m_nBottomToothNum;nCnt++)
//    {
//        m_pBottomTooth[nCnt].update();
//    }
//    
//    // 歯の更新
//    for(int nCnt = 0;nCnt < m_nTopToothNum;nCnt++)
//    {
//        m_pTopTooth[nCnt].update();
//    }
}

//================================================================================
// 生成処理
//================================================================================
ToothManager* ToothManager::Create(const Vec2& startLeftTopPos,const int& nTopToothNum,
                                   const int& nBottomToothNum,const float& fDistance,Layer* layer)
{
    // 歯マネージャーのインスタンス化
    ToothManager* pToothManager = new ToothManager();
    
    // メンバー変数の代入
    pToothManager->m_startLeftTopPos = startLeftTopPos;
    pToothManager->m_nTopToothNum = nTopToothNum;
    pToothManager->m_nBottomToothNum = nBottomToothNum;
    pToothManager->m_fDistance = fDistance;
    pToothManager->m_pLayer = layer;
    
    // 初期化
    pToothManager->init();
    
    return pToothManager;
}

void ToothManager::AddTopGumPosAndTopToothPos(const Vec2& vec)
{
    m_topGumPos += vec;
    m_pTopGumSprite->setPosition(m_topGumPos);
    m_topToothPos += vec;
    m_pTopToothSprite->setPosition(m_topToothPos);
}

void ToothManager::AddBottomGumPosAndBottomToothPos(const Vec2& vec)
{
    m_bottomGumPos += vec;
    m_pBottomGumSprite->setPosition(m_bottomGumPos);
    m_bottomToothPos += vec;
    m_pBottomToothSprite->setPosition(m_bottomToothPos);
}




