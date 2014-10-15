//
//  TextureManager.cpp
//  cocosTest
//
//  Created by 鈴木 愛忠 on 2014/10/08.
//
//

#include "TextureManager.h"

std::string TextureManager::m_Texture[TEX_MAX] = {
    "tooth_01.png",
    "GameUITop.png",
    "GameUIBottom.png",
    "haguki.png",
    "HPBar.png",
    "bubble_01.png",
    "HelloWorld.png",
};

//HDかSDか決定して配列を変更する
void TextureManager::initTexture()
{
}