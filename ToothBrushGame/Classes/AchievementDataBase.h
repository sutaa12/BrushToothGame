//
//  AchievementDataBase.h
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/23.
//
//

#ifndef __ToothBrushGame__AchievementDataBase__
#define __ToothBrushGame__AchievementDataBase__

#include <stdio.h>

//実績解除種類
enum ACHIEVEMENT_FLAG
{
    ACHIEVE_TYPE_NONE = 0,//実績タイプ
    ACHIEVE_TYPE_TURN_ON,//起動回数
    ACHIEVE_TYPE_GAME_PLAY,//プレイ回数
    ACHIEVE_TYPE_GAMEOVER,//ゲームオーバー回数
    ACHIEVEMENT_TYPE_ENEMY_DOWN,//倒した敵の数
    ACHIEVEMENT_MAX
};

//実績解除条件のデータ構造隊
struct ACHIEVE_STATUS
{
    ACHIEVEMENT_FLAG achieveFlagMode;
    int unlockNum;//解除に必要な数
    bool lock;//解除されたか
    int date;//解除日
    char* title;//実績名
    char* message;//実績内容
};



//実績解除条件

#endif /* defined(__ToothBrushGame__AchievementDataBase__) */
