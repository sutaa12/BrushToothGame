//
//  Score.cpp
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/15.
//
//

//********************************************************************************
// インクルード
#include "Score.h"
#include "Number.h"

static const int Score_DISPLAY_CENTER_X = (320);

//================================================================================
// コンストラクタ
//================================================================================
Score::Score(void)
{
    // メンバ変数の初期化
    m_ppNumbers = nullptr;
    m_pLayer = nullptr;
    m_nMaxNumber = 0;
}

//================================================================================
// デストラクタ
//================================================================================
Score::~Score()
{
    
}

//================================================================================
// 初期化処理
//================================================================================
bool Score::init(void)
{
    m_ppNumbers = new Number*[m_nMaxNumber];
    for(int nloop = 0;nloop < m_nMaxNumber;nloop++)
    {
        // 上歯茎生成
        m_ppNumbers[nloop] = Number::create();
        
        // スプライトサイズ取得
        Rect numgerRect = (m_ppNumbers[nloop]->getSprite()->getBoundingBox());
        
        // 座標変換(左上を持ってきているため、中心にそろえる処理)
        m_ppNumbers[nloop]->setPos(Vec2(Score_DISPLAY_CENTER_X,
                               m_startLeftTopPos.y - (numgerRect.size.height / 2)));
        
        // スプライトの再配置
        m_ppNumbers[nloop]->refreshSpritePos();
        
        // スプライトの登録
        m_pLayer->addChild(m_ppNumbers[nloop]->getSprite());
    }
    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void Score::uninit(void)
{
    
}

//================================================================================
// 更新処理
//================================================================================
void Score::update(void)
{
    
}

//================================================================================
// 生成処理
//================================================================================
Score* Score::create(const Vec2& startLeftTopPos,int nMaxNumber,Layer* layer)
{
    // 歯マネージャーのインスタンス化
    Score* pScore = new Score();
    
    // メンバー変数の代入
    pScore->m_startLeftTopPos = startLeftTopPos;
    pScore->m_pLayer = layer;
    pScore->m_nMaxNumber = nMaxNumber;
    // 初期化
    pScore->init();
    
    return pScore;
}
