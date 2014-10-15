//
//  ToothManager.h
//  cocosTest
//
//  Created by 鈴木 愛忠 on 2014/10/10.
//
//

#ifndef __cocosTest__ToothManager__
#define __cocosTest__ToothManager__

#include <cocos2d.h>
struct TOOTH_DATA
{
    cocos2d::Sprite* Tooth[2];
    cocos2d::Rect ToothData[2];
    cocos2d::Sprite* ToothMeat[2];
    cocos2d::Rect ToothDataMeat[2];
};
class ToothManager{
public:
    //歯を作成
    //コンストラクタ
    ToothManager(cocos2d::Vec2 &pos);
    TOOTH_DATA& getTooth(void){return m_toothData;}
    
    
private:
    TOOTH_DATA m_toothData;
};
#endif /* defined(__cocosTest__ToothManager__) */
