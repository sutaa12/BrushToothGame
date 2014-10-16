//********************************************************************************
//  PlaqueManager.cpp
//  ToothBrushGame
//
//  Created by 丸山 潤 on 2014/10/15.
//
//********************************************************************************
//********************************************************************************
// インクルード
//********************************************************************************
#include "PlaqueManager.h"
#include "Plaque.h"

//================================================================================
// コンストラクタ
//================================================================================
PlaqueManager::PlaqueManager(void)
{
    m_nPlaqueNum = 0;
    m_ppPlaque = nullptr;
}

//================================================================================
// デストラクタ
//================================================================================
PlaqueManager::~PlaqueManager()
{
    for(int nCnt = 0;nCnt < m_nPlaqueMaxNum;nCnt++)
    {
        delete m_ppPlaque[nCnt];
        m_ppPlaque[nCnt] = nullptr;
    }

    delete m_ppPlaque;
    m_ppPlaque = nullptr;
}

//================================================================================
// 初期化処理
//================================================================================
bool PlaqueManager::init(void)
{
    // クリエイトで持ってきた最大値分だけ動的確保
    m_ppPlaque = new Plaque*[m_nPlaqueMaxNum];

    for(int nCnt = 0;nCnt < m_nPlaqueMaxNum;nCnt++)
    {
        m_ppPlaque[nCnt] = nullptr;
    }

    createPlaque();

    return true;
}

//================================================================================
// 終了処理
//================================================================================
void PlaqueManager::uninit(void)
{

}

//================================================================================
// 更新処理
//================================================================================
void PlaqueManager::update(void)
{
    for(int nPlaqueNum = 0;nPlaqueNum < m_nPlaqueMaxNum;nPlaqueNum++)
    {
        m_ppPlaque[nPlaqueNum]->update();
    }
}

//================================================================================
// 生成処理
//================================================================================
PlaqueManager* PlaqueManager::create(int nPlaqueMaxNum,Layer* pLayer)
{
    PlaqueManager* pPlaqueManager = new PlaqueManager();

    pPlaqueManager->m_nPlaqueMaxNum = nPlaqueMaxNum;
    pPlaqueManager->m_pLayer = pLayer;

    pPlaqueManager->init();

    return pPlaqueManager;
}

//================================================================================
// 歯垢生成処理
//================================================================================
void PlaqueManager::createPlaque(void)
{
    Vec2 pos = Vec2(50,600);

    // 生成チェック
    for(int nCnt = 0;nCnt < m_nPlaqueMaxNum;nCnt++)
    {
        m_ppPlaque[nCnt] = Plaque::create(pos);

        m_pLayer->addChild(m_ppPlaque[nCnt]->getSprite());

        m_nPlaqueNum++;

        pos.x += 10;
    }
}





