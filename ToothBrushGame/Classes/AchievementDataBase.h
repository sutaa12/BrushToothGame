//
//  AchievementDataBase.h
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/23.
//
//

#ifndef __ToothBrushGame__AchievementDataBase__
#define __ToothBrushGame__AchievementDataBase__

#define __ToothBrushGame__AchievementList__
#include <cocos2d.h>
#include "common.h"
USING_NS_CC;

class AchievementDataBaseList{
public:
    //実績解除種類
    enum ACHIEVEMENT_KIND
    {
        ACHIEVE_TYPE_NONE = 0,//実績タイプ
        ACHIEVE_TYPE_TURN_ON,//起動回数
        ACHIEVE_TYPE_GAME_PLAY,//プレイ回数
        /*
         ACHIEVE_TYPE_GAMEOVER,//ゲームオーバー回数
         ACHIEVEMENT_TYPE_ENEMY_DOWN,//倒した敵の総数
         ACHIEVEMENT_TYPE_ENEMY_NORMAL_ONE_DOWN,//普通の種類の敵の倒した数
         ACHIEVEMENT_TYPE_ENEMY_NORMAL_TWO_DOWN,
         ACHIEVEMENT_TYPE_ENEMY_LAIR_ONE_DOWN,//レア種類の敵を倒した数
         ACHIEVEMENT_TYPE_ENEMY_LAIR_TWO_DOWN,
         ACHIEVEMENT_TYPE_TAP_GIRL_TITLE,
         ACHIEVEMENT_TYPE_SWIPE_GIRL_TITLE,
         ACHIEVEMENT_TYPE_TAP_GIRL_GAMESTATUS,
         ACHIEVEMENT_TYPE_SWIPE_GIRL_GAMESTATUS,
         */
        ACHIEVEMENT_MAX
    };
    
    //実績解除条件のデータ構造隊
    struct ACHIEVE_STATUS
    {
        ACHIEVEMENT_KIND achieveFlagKind;
        int unlockNum;//解除に必要な数
        bool lock;//解除されたか
        int date;//解除日
        char* title;//実績名
        char* message;//実績内容
    };
    
public:
    AchievementDataBaseList(){}
    ~AchievementDataBaseList(){}
    static void init();
    static int getDataNumber();
    static int addDataNumber();
    static ACHIEVE_STATUS getAchievement();
    
private:
    static int m_nAchievementData[ACHIEVEMENT_MAX];//各リストのデータの大きさ
};





//実績解除条件

#endif /* defined(__ToothBrushGame__AchievementDataBase__) */
