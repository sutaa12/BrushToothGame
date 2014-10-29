//
//  common.h
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/16.
//
//

#ifndef ToothBrushGame_common_h
#define ToothBrushGame_common_h
#include <cocos2d.h>
USING_NS_CC;
#define DATA_PI (3.1415926535f)
#define MIKA_FONT ("mikachan")

//ベクトルの最大値チェック　超えていたら押し戻す
template <class T1,class T2>
inline void CHECK_MAX_POS(T1 &vec0,T2 &vecMin,T2 &vecMax)
{
    if(vec0 >= vecMax)
    {
        vec0 = vecMax;
    }else
        if(vec0 <= vecMin)
        {
            vec0 = vecMin;
        }
}
//セーフデリート
template<class T>
inline void SAFE_DELETE(T &p)
{
    if(p != nullptr)
    {
        delete p;
        p = nullptr;
    }
}
//セーフデリートアレイ
template<class T>
inline void SAFE_DELETE_ARRAY(T &p)
{
    if(p != nullptr)
    {
        delete[] p;
        p = nullptr;
    }
}
//角度チェック
template <class T>
inline void ROT_CHK(T &rot)
{
    if(rot > DATA_PI || rot < -DATA_PI)
    {
        if(rot > DATA_PI)
        {
            rot -= 2 * DATA_PI;
        }
        else
            if(rot < -DATA_PI)
            {
                rot += 2 * DATA_PI;
            }
    }
};
//シーンリスト
enum SCENE_LIST
{
    SCENE_NONE = 0,
    SCENE_TITLE,
    SCENE_GAME,
    SCENE_RESULT
};

//定数定義
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 960;

const int SCREN_WIDTH_CENTER = SCREEN_WIDTH / 2;
const int SCREN_HEIGHT_CENTER = SCREEN_HEIGHT / 2;

const Size SCREEN_SIZE = Size(SCREEN_WIDTH,SCREEN_HEIGHT);
const Size SCREEN_CENTER = Size(SCREN_WIDTH_CENTER,SCREN_HEIGHT_CENTER);

#endif
