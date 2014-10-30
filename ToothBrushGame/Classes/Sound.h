//
//  Sound.h
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/20.
//
//

#ifndef ToothBrushGame_Sound_h
#define ToothBrushGame_Sound_h


#include "SimpleAudioEngine.h"

//CocosDenshion::を書くのが面倒な人用
using namespace CocosDenshion;


//********************************************************************************
// VOLUME
//********************************************************************************

//タイトル画面音量
#define BGM_TITLE_VOLUME (0.3f)

//リザルト画面音量
#define BGM_RESULT_VOLUME (0.7f)

//ゲームシーン音量
#define BGM_GAMESCENE_VOLUME_3 (0.3f)

#define BGM_VOLUME_MIN (0.1f)
#define BGM_VOLUME_HALF (0.5f)
#define BGM_VOLUME_MAX (1.0f)

#define SE_VOLUME_2 (0.2f)
#define SE_VOLUME_3 (0.3f)
#define SE_VOLUME_HALF (0.5f)
#define SE_VOLUME_MAX (1.0f)

//敵昇天音量
#define SE_ENEMY_DOWN_VOLUME_3 (0.3f)
#define SE_ENEMY_DOWN_VOLUME_5 (0.5f)


//********************************************************************************
// BGM
//********************************************************************************


#define BGM_TITLE_1 ("bgm_title_1.mp3")
#define BGM_TITLE_2 ("bgm_title_2.mp3")

#define BGM_ENEMY_SCENE_1 ("bgm_enemy_scene_1.mp3")
#define BGM_ENEMY_SCENE_2 ("bgm_enemy_scene_2.mp3")
#define BGM_ENEMY_SCENE_3 ("bgm_enemy_scene_3.mp3")
#define BGM_ENEMY_SCENE_4 ("bgm_enemy_scene_4.mp3")
#define BGM_ENEMY_SCENE_5 ("bgm_enemy_scene_5.mp3")

#define BGM_GAME_CLEAR_1 ("bgm_game_clear_1.mp3")

#define BGM_STAGE_SELECT_1 ("bgm_stageselect_1.mp3")
#define BGM_STAGE_SELECT_2 ("bgm_stageselect_2.mp3")

#define BGM_RESULT_1 ("bgm_result_1.mp3")


//********************************************************************************
// SE
//********************************************************************************

//ボタン
#define SE_BUTTON_1 ("se_button_1.mp3")
#define SE_START_BUTTON_1 ("se_game_start_1.mp3")

//実績解除音
#define SE_GET_ACHIEVEMENT_3 ("get_achievement_3.mp3")
#define SE_GET_ACHIEVEMENT_4 ("get_achievement_4.mp3")

//敵
#define SE_ENEMY_DOWN_1 ("hit_1.wav")
#define SE_ENEMY_DOWN_2 ("se_enemy_down_3.mp3")
#define SE_ENEMY_DOWN_3 ("se_enemy_down.wav")

//敵くっつくの音
#define SE_SWIPE_1 ("se_swipe_1.mp3")
//#define SE_SWIPE_2 ("se_swipe_2.wav")

//うがい時　音
#define SE_SHAKE_1 ("se_shake_1.mp3")
#define SE_SHAKE_2 ("se_shake_2.mp3")

//歯磨き粉ボム　使用中
//#define SE_POWDER_1 ("se_powder_1.mp3")
#define SE_POWDER_2 ("se_powder_2.mp3")

//チャージ完了
#define SE_POWDER_FULL_1 ("se_powder_full_1.mp3")
#define SE_POWDER_FULL_2 ("se_powder_full_2.mp3")

//爆発
#define SE_POWDER_EXPLOSION_1 ("se_powder_explosion_1.mp3")
#define SE_POWDER_EXPLOSION_2 ("se_powder_explosion_2.mp3")

//残り１０秒！音
#define SE_TIME_REMAIND_1 ("se_time_remaind_1.mp3")
#define SE_TIME_REMAIND_2 ("se_time_remaind_2.mp3")
#define SE_FANFARE_1 ("se_fanfare_1.mp3")

//ゲームクリア　キラキラ音
#define SE_SHINE_1 ("se_shine_1.mp3")
#define SE_SHINE_5 ("se_shine_5.mp3")

//ゲームオーバー
#define SE_GAME_OVER_1 ("se_game_over_1.mp3")
#define SE_GAME_OVER_2 ("se_game_over_2.mp3")


#endif
