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
#include "common.h"
#include "ToothManager.h"
#include "Tooth.h"
#include "Gum.h"
#include "TextureFile.h"

//================================================================================
// コンストラクタ
//================================================================================
ToothManager::ToothManager(void)
{
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
    m_pTonger = nullptr;
    m_pTooth = nullptr;
    //舌ベロ生成
    m_pTonger = Sprite::create(TEX_TONGER_BACK);
    m_startLeftTopPos.y -= m_pTonger->getContentSize().height / 2;

    m_pTonger->setPosition(m_startLeftTopPos);
    m_pLayer->addChild(m_pTonger);
    
    //歯生成
    m_pTooth = Sprite::create(TEX_TOOTH_FRONT);
    m_pTooth->setPosition(m_startLeftTopPos);
    
    m_pLayer->addChild(m_pTooth);
    
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
ToothManager* ToothManager::create(const Vec2& startLeftTopPos,Layer* layer)
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


