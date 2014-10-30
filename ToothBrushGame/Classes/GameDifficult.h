//
//  GameDifficult.h
//  ToothBrushGame
//
//  Created by 鈴木愛忠 on 2014/10/24.
//
//

#ifndef ToothBrushGame_GameDifficult_h
#define ToothBrushGame_GameDifficult_h
#include <cocos2d.h>
#include "Enemy.h"
using namespace cocos2d;

//ゲームのウェーブ調整
enum GAME_PHASE{
    PHASE_ONE = 0,
    PHASE_TWO,
    PHASE_TREE,
    PHASE_FOR,
    PHASE_FIVE,
    PHASE_SIX,
    PHASE_SEVEN,
    PHASE_EIGHT,
    PHASE_NINE,
    PHASE_TEN,
    PHASE_ELEVEN,
    PHASE_TWELVE,
    PHASE_THRTY,
    PHASE_FORTY,
    PHASE_FIFTY,
    PHASE_SIXTY,
    PHASE_SEVEMTY,
    PHASE_EIGHTY,
    PHASE_NINETY,
    PHASE_TWENTY,
    PHASE_TWENTYONE,
    PHASE_TWENTYTWO,
    PHASE_TWENTYTREE,
    PHASE_TWENTYFOR,
    PHASE_TWENTYFIVE,
    PHASE_TWENTYSIX,
    PHASE_TWENTYELEVEN,
    PHASE_TWENTYEIGHT,
    PHASE_TWENTYNINE,
    PHASE_THIRTY,
    PHASE_THIRTYONE,
    PHASE_THIRTYTWO,
    PHASE_THIRTYTHREE,
    PHASE_THIRTYFOR,
    PHASE_THIRTYFIVE,
    PHASE_THIRTYSIX,
    PHASE_MAX
};

struct GAME_PASE_DATA{
    Enemy::ENEMY_KIND enemykind;//どの種類の敵か
    int spawn;//軟体出てくるか
    int spawnTime;//何秒後に出てくるか
    Point pos;//どこに出てくるか

};

#endif
