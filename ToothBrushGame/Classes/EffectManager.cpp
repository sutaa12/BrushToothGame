//
//  EffectManager.cpp
//  ToothBrushGame
//
//  Created by 鈴木愛忠 on 2014/10/17.
//
//
#include "common.h"
#include "EffectManager.h"
#include "Bubble.h"
#include "Random.h"
//================================================================================
// コンストラクタ
//================================================================================
EffectManager::EffectManager(int numEffect)
{
    // メンバ変数の初期化
    if(numEffect >= Effect_MAX)
    {
        numEffect = Effect_MAX - 1;
    }
    m_pLayer = nullptr;
    for(int nloop = 0;nloop < Effect_MAX;nloop++)
    {
        m_pEffect[nloop] = nullptr;
    }
    m_nTime = 0;
    m_nTimeSpan = TIME_SPAN;
}

//================================================================================
// デストラクタ
//================================================================================
EffectManager::~EffectManager()
{
    for(int nloop = 0;nloop < Effect_MAX;nloop++)
    {
        SAFE_DELETE(m_pEffect[nloop]);
    }
}

//================================================================================
// 初期化処理
//================================================================================
bool EffectManager::init(void)
{
    for(int nloop = 0;nloop < Effect_MAX;nloop++)
    {
        m_pEffect[nloop] = Bubble::create(Vec2(0,0));
        m_pLayer->addChild(m_pEffect[nloop]->getSprite());
        
    }
    
    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void EffectManager::uninit(void)
{
    
}

//================================================================================
// 更新処理
//================================================================================
void EffectManager::update(void)
{
    m_nTime++;
    
    for(int nloop = 0;nloop < EffectManager::Effect_MAX;nloop++)
    {
        m_pEffect[nloop]->update();
    }
    
}

//================================================================================
// 生成処理
//================================================================================
EffectManager* EffectManager::create(Layer* layer,int numEffect)
{
    // 歯マネージャーのインスタンス化
    EffectManager* pEffectManager = new EffectManager(numEffect);
    
    // メンバー変数の代入
    pEffectManager->m_pLayer = layer;
    
    // 初期化
    pEffectManager->init();
    return pEffectManager;
}

//================================================================================
// エフェクト生成処理
//================================================================================
void EffectManager::spawn(int nSpawnNum,Vec2 pos,Color3B col)
{
    clampf(nSpawnNum, 0, Effect_MAX);
    int nEffectNum = 0;
    for(int nloop = 0;nloop < Effect_MAX;nloop++)
    {
        if(m_pEffect[nloop]->getDisapper())
        {
            m_pEffect[nloop]->setSpawn(pos,col);
            nEffectNum++;
        }
        if(nEffectNum >= nSpawnNum)
        {
            return;
        }
    }
}
//================================================================================
// 敵の数取得
//================================================================================
int EffectManager::getEffectNum(void)
{
    int numEffect = 0;
    for(int nloop = 0;nloop < Effect_MAX;nloop++)
    {
        if(!m_pEffect[nloop]->getDisapper())
        {
            numEffect++;
        }
    }
    return numEffect;
}
//================================================================================
// 敵をすべて消滅
//================================================================================
void EffectManager::setEffectClear(void)
{
    for(int nloop = 0;nloop < Effect_MAX;nloop++)
    {
        if(!m_pEffect[nloop]->getDisapper())
        {
            m_pEffect[nloop]->disappear();
        }
    }
}


