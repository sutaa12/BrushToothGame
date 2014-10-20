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
#include "common.h"
#include "PlaqueManager.h"
#include "Plaque.h"
#include "Random.h"
#include "ToothManager.h"
#include "Gum.h"
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
        SAFE_DELETE(m_ppPlaque[nCnt]);
    }
    SAFE_DELETE(m_ppPlaque);
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

    std::set<int> randNum;

    // グリッド数は(640/16)*(512/16)=40*32 =1280だが、端に行くのを防止するために一列ずつ減らして39*31=1209
    getRandGlidNum(randNum, 0, 1209, m_nPlaqueMaxNum);
    std::set<int>::iterator it = randNum.begin();

    // 下歯茎の左上座標をスタート地点にする
    Vec2 startVec = Vec2(0,320);

    // 生成チェック
    for(int nCnt = 0;nCnt < m_nPlaqueMaxNum;nCnt++)
    {
        int nWork = (*it);
        int nWorkX = nWork / 31;
        int nWorkY = nWork - nWorkX * 31;
        Vec2 workVec  = startVec;
        workVec.x += nWorkX * 16 + 16;
        workVec.y += nWorkY * 16 + 16;

        m_ppPlaque[nCnt] = Plaque::create(workVec);

        m_pLayer->addChild(m_ppPlaque[nCnt]->getSprite());

        m_nPlaqueNum++;

        it++;
    }
}

//================================================================================
// 歯垢生成グリッド生成処理
//================================================================================
void PlaqueManager::getRandGlidNum(std::set<int>& result,int nMin,int nMax,int nNum)
{
    int randNum;

    for(int nCnt = 0;nCnt < nNum;nCnt++)
    {
        do{
            randNum = RandomMT::getRaodom(nMin, nMax);
        }while (result.find(randNum) != result.end());

        result.insert(randNum);
    }
}





