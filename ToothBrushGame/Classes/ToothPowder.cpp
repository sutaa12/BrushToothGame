//
//  ToothPowder.cpp
//  ToothBrushGame
//
//  Created by 鈴木愛忠 on 2014/10/22.
//
//

//********************************************************************************
// インクルード
//********************************************************************************
#include "TextureFile.h"
#include "Sound.h"
#include "ToothPowder.h"
#include "SoundManager.h"
#include "AchievementDataBase.h"

//================================================================================
// コンストラクタ
//================================================================================
ToothPowder::ToothPowder(void)
{
    // メンバ変数の初期化
    m_pSprite = nullptr;
}

//================================================================================
// デストラクタ
//================================================================================
ToothPowder::~ToothPowder()
{
    
}
//================================================================================
// 終了処理
//================================================================================
void ToothPowder::disappear(void)
{
    if(m_bPowderTouchFlag)
    {
        m_nCount = 1;
        AchievementDataBaseList::addAchievement(ACHIEVEMENT_TYPE_USE_TOOTHPOWDER);
    }
    m_pItemIcon->setPosition(m_pos);
    m_pItemIcon->setOpacity(0);
    m_bPowderTouchFlag = false;
    
}


//================================================================================
// 初期化処理
//================================================================================
bool ToothPowder::init(void)
{
    m_nCount = 0;
    m_bPowderTouchFlag = false;
    
    Sprite* pSprite = Sprite::create(TEX_BUTTON_ITEM_TOOTHPOWDER);

    //タイマー作成
    m_pProgressTimer = ProgressTimer::create(pSprite);
    
    //最初は0パーセント
    m_pProgressTimer->setPercentage(0);
    
    //タイマーの形（棒状に設定）
    m_pProgressTimer->setType(ProgressTimer::Type::BAR);
    
    //バーの伸びる方向（x方向に設定）
    m_pProgressTimer->setBarChangeRate(Point(0, 1));

    m_pProgressTimer->setScale(0.9f,0.85f);
    
    //タイマーの基準点（左側に設定）
    m_pProgressTimer->setMidpoint(Point(0, 0));
    
    //タイマーを配置
    m_pProgressTimer->setPosition(m_pos);
    m_pProgressTimer->setTag(100);

    // スプライトの作成
    m_pSprite = Sprite::create(TEX_BUTTON_ITEM_TOOTHPOWDER);
    m_pItemIcon = Sprite::create(TEX_ITEM_TOOTHPOWDER);
    // エラーチェック
    if(m_pSprite == nullptr)
    {
        // スプライト生成エラー
        return false;
    }
    m_pSprite->setColor(Color3B::GRAY);
    // スプライトの座標設定
    m_pSprite->setPosition(m_pos);
    m_pSprite->setScale(0.9f,0.85f);

    m_pItemIcon->setPosition(m_pos);
    m_pItemIcon->setOpacity(0);
    
    m_pLayer->addChild(m_pSprite);
    m_pLayer->addChild(m_pItemIcon);
    m_pLayer->addChild(m_pProgressTimer);
    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void ToothPowder::uninit(void)
{
    
}

//================================================================================
// 更新処理
//================================================================================
void ToothPowder::update(void)
{
    if(m_nCount != 0)
    {
        m_nCount++;
        float fPer = m_nCount / (60 * TOOTH_RESPONS_SEC) * 100;
        m_pProgressTimer->setPercentage(fPer);

        if(m_nCount > 60 * TOOTH_RESPONS_SEC)
        {
            m_nCount = 0;
        }
    }else{
        m_pProgressTimer->setPercentage(100);
    }
    //m_pToothSprite->setPosition(m_pos);
  /*
    if (m_bPowderTouchFlag == false){
        //効果音を止める
        SimpleAudioEngine::getInstance()->stopEffect(true);
    }*/
}

//================================================================================
// 生成処理
//================================================================================
ToothPowder* ToothPowder::create(Layer* pLayer,const Vec2& pos)
{
    // インスタンスの生成
    ToothPowder* pToothPowder = new ToothPowder();
    
    // メンバ変数の代入
    pToothPowder->m_pos = pos;
    pToothPowder->m_pLayer = pLayer;
    // 初期化
    pToothPowder->init();
    
    return pToothPowder;
}
//================================================================================
// アイコン移動
//================================================================================
void ToothPowder::setPos(Vec2 pos)
{
    m_pItemIcon->setOpacity(90);
    m_pItemIcon->setPosition(pos);
    
}
//================================================================================
// 判定チェック
//================================================================================
void ToothPowder::chkPowderTouchFlag(Point pos)
{
    if(m_nCount == 0)
    {
        Rect rectPowder = Rect(m_pSprite->getBoundingBox());
        if(rectPowder.containsPoint(pos))
        {
            m_bPowderTouchFlag = true;
            SoundManager::playSoundID(ID_SE_POWDER_2);

        }
    }
    
}