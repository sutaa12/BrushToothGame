//
//  SoundManager.h
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/27.
//
//

#ifndef __ToothBrushGame__SoundManager__
#define __ToothBrushGame__SoundManager__
#include "Sound.h"

enum SOUND_LABEL
{
    ID_SE_POWDER_2 = 0,
    SE_TOUP,
    SOUND_MAX
};

class SoundManager
{
public:
    SoundManager(){}
    ~SoundManager(){}

    static void init();
    static void uninit();
    static void playSoundID(SOUND_LABEL soundlabel);
    static void stopSoundID(SOUND_LABEL soundlabel);

private:
    static int m_nSoundId[SOUND_MAX];


};

#endif /* defined(__ToothBrushGame__SoundManager__) */

