//
//  TextureManager.h
//  cocosTest
//
//  Created by 鈴木 愛忠 on 2014/10/08.
//
//

#ifndef __cocosTest__TextureManager__
#define __cocosTest__TextureManager__
#include<cocos2d.h>
enum TEXTURE_NAME
{
    TEX_TOOTH = 0,
    TEX_TOPUI,
    TEX_BOTTOMUI,
    TEX_TOOTHMEAT,
    TEX_HPBAR,
    TEX_BUBBLE,
    TEX_HELLO,
    TEX_MAX
};
class TextureManager
{
public:
    static void initTexture();
    static std::string getTexure(TEXTURE_NAME tex){return m_Texture[tex];}
private:
    static TEXTURE_NAME m_texName;
    static cocos2d::SpriteBatchNode* m_sprtTex[TEX_MAX];
    static std::string m_Texture[TEX_MAX];
};

#endif /* defined(__cocosTest__TextureManager__) */
