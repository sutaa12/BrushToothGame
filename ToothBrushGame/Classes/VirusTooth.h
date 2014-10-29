//
//  VirusTooth.h
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/28.
//
//

#ifndef __ToothBrushGame__VirusTooth__
#define __ToothBrushGame__VirusTooth__
#include "cocos2d.h"
#include "TextureFile.h"
#include "AchievementDataBase.h"
using namespace cocos2d;

class VirusTooth
{
public:
    
    VirusTooth();   //コンストラクタ
    ~VirusTooth();  //デストラクタ
    
    bool init();    //初期設定
    void uninit();  //
    void update();  //更新
    void disappear();   //消滅
    static VirusTooth* create(const Vec2& pos = Vec2(0.0f,0.0f));
    Sprite* getSprite(void){return m_pSprite;}
    
    bool getDisapper(void){return m_bDeath;}
    //行動選択関数
    void choiceAction(void);
    
    //位置を画像に適用
    void refreshSpritePos(void){m_pSprite->setPosition(m_pos);}
    //出現
    void setSpawn(Vec2 pos);
    //倒れたフラグを拾う
    bool getVirusToothDownFlag(void){return m_bDown;}
    
private:
    Sprite* m_pSprite;
    Vec2 m_pos;
    //時間
    int m_time;
    //行動状態
    int m_actionMode;
    //敵が倒れたフラグ
    bool m_bDown;
    //生きてるか死んでるかのフラグ
    bool m_bDeath;
    
    //定数
public:
};
#endif /* defined(__ToothBrushGame__VirusTooth__) */