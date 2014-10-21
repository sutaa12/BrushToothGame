//
//  common.h
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/16.
//
//

#ifndef ToothBrushGame_common_h
#define ToothBrushGame_common_h

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

//シーンリスト
enum SCENE_LIST
{
    SCENE_NONE = 0,
    SCENE_TITLE,
    SCENE_GAME,
    SCENE_RESULT
};
#endif
