//
//  UgaiEffect.h
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/29.
//
//

#ifndef __ToothBrushGame__UgaiEffect__
#define __ToothBrushGame__UgaiEffect__

#include "cocos2d.h"
using namespace cocos2d;

class UgaiEffect
{
public:
    
    UgaiEffect();   //コンストラクタ
    ~UgaiEffect();  //デストラクタ
    
    bool init();    //初期設定
    void uninit();  //
    void update();  //更新
    static UgaiEffect* create(Layer* pLayer,const Vec2& pos = Vec2(0.0f,0.0f));
    Sprite* getSprite(void){return m_pSprite;}
    
    //行動選択関数
    void choiceAction(void);
    
    //位置を画像に適用
    void refreshSpritePos(void){m_pSprite->setPosition(m_pos);}
    //出現
    void setSpawn();
    
private:
    static const int MAX_WATER = 10;
    Sprite* m_pSprite;
    Sprite* m_pWater[MAX_WATER];
    Vec2 m_pos;
    //時間
    int m_time;
    //行動状態
    int m_actionMode;
    
    Layer* m_pLayer;
    
    //定数
public:
};

#endif /* defined(__ToothBrushGame__UgaiEffect__) */
