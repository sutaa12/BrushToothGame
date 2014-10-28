//
//  VirusToothManager.cpp
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/28.
//
//

#include "VirusToothManager.h"

//********************************************************************************
// インクルード
//********************************************************************************
#include "common.h"
#include "VirusToothManager.h"
#include "VirusTooth.h"
#include "Random.h"
//================================================================================
// コンストラクタ
//================================================================================
VirusToothManager::VirusToothManager(int numVirusTooth)
{
    
    // メンバ変数の初期化
    if(numVirusTooth >= VIRUSTOOTH_MAX)
    {
        numVirusTooth = VIRUSTOOTH_MAX - 1;
    }
    m_numVirusTooth = numVirusTooth;
    m_pLayer = nullptr;
    for(int nloop = 0;nloop < VIRUSTOOTH_MAX;nloop++)
    {
        m_pVirusTooth[nloop] = nullptr;
    }
    m_nTime = 0;
}

//================================================================================
// デストラクタ
//================================================================================
VirusToothManager::~VirusToothManager()
{
    for(int nloop = 0;nloop < VIRUSTOOTH_MAX;nloop++)
    {
        SAFE_DELETE(m_pVirusTooth[nloop]);
    }
}

//================================================================================
// 初期化処理
//================================================================================
bool VirusToothManager::init(void)
{
    for(int nloop = 0;nloop < VIRUSTOOTH_MAX;nloop++)
    {
        m_pVirusTooth[nloop] = VirusTooth::create(Vec2(0,0));
        m_pLayer->addChild(m_pVirusTooth[nloop]->getSprite());
        
    }
    
    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void VirusToothManager::uninit(void)
{
    
}

//================================================================================
// 更新処理
//================================================================================
void VirusToothManager::update(void)
{
    m_nTime++;
    
}

//================================================================================
// 生成処理
//================================================================================
VirusToothManager* VirusToothManager::create(Layer* layer)
{
    // 歯マネージャーのインスタンス化
    VirusToothManager* pVirusToothManager = new VirusToothManager(0);
    
    // メンバー変数の代入
    pVirusToothManager->m_pLayer = layer;
    
    // 初期化
    pVirusToothManager->init();
    
    return pVirusToothManager;
}

//================================================================================
// 敵生成処理
//================================================================================
void VirusToothManager::spawn(Vec2 pos)
{
    Size visibleSize = Director::getInstance()->getVisibleSize() / 2 + SCREEN_CENTER;
    Vec2 origin = Director::getInstance()->getVisibleSize() / 2 - SCREEN_CENTER;
    Vec2 MaxPos = Vec2(visibleSize.width - origin.x,visibleSize.height - 128 - origin.y);
    Vec2 MinPos = Vec2(origin.x,MaxPos.y - 512 + origin.y);
    
    int nVirusToothNum = 0;
    
    for(int nloop = VIRUSTOOTH_MAX - 1 ;nloop >= 0 ;nloop--)
    {
        if(m_pVirusTooth[nloop]->getVirusToothDownFlag())
        {
            if(pos.x == -1 && pos.y == -1)
            {
                pos =Vec2(RandomMT::getRandom(MinPos.x, MaxPos.x),RandomMT::getRandom(MinPos.y,MaxPos.y));
            }
            m_pVirusTooth[nloop]->setSpawn(pos);
            nVirusToothNum++;
            return;
        }
    }
}
