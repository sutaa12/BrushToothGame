//
//  VirusToothManager.h
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/28.
//
//

#ifndef __ToothBrushGame__VirusToothManager__
#define __ToothBrushGame__VirusToothManager__
#include "cocos2d.h"
#include "TextureFile.h"
#include "AchievementDataBase.h"
#include "GameDifficult.h"
using namespace cocos2d;
class VirusTooth;
//********************************************************************************
// クラス宣言
//********************************************************************************
class VirusToothManager
{
public:
    //最初に出す敵の数
    VirusToothManager(int numVirusTooth);
    ~VirusToothManager();
    
    bool init(void);
    void uninit(void);
    void update(void);
    
    static VirusToothManager* create(Layer* layer);
    
    //敵の先頭取得
    VirusTooth* getVirusToothsTop(void){return m_pVirusTooth[0];}
    
    void spawn(Vec2 pos);
    
public:
    //敵の最大数
    static const int VIRUSTOOTH_MAX = PHASE_MAX;
private:
    
    //敵の配列
    VirusTooth* m_pVirusTooth[VIRUSTOOTH_MAX];
    
    Layer* m_pLayer;
    int m_numVirusTooth;
    
    int m_nTime;
    
    int m_nTimeSpan;
    
    int m_nSpriteMax;
    int m_nSpriteMin;
    
};

#endif /* defined(__ToothBrushGame__VirusToothManager__) */
