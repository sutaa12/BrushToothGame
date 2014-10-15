//
//  LayerManager.h
//  cocosTest
//
//  Created by 鈴木 愛忠 on 2014/10/08.
//
//

#ifndef __cocosTest__LayerManager__
#define __cocosTest__LayerManager__

#include <cocos2d.h>

enum LAYER_MODE
{
    LAYER_0 = 0,
    LAYER_1,
    LAYER_2,
    LAYER_MAX
};
class LayerManager : public cocos2d::Layer
{
public:
    virtual bool init();
    static bool initLayer(void);
    // implement the "static create()" method manually
    CREATE_FUNC(LayerManager);
    static cocos2d::Layer* getLayer(int layerMode){return m_Layer[layerMode];}
private:
    static LayerManager* m_Layer[LAYER_MAX];
};


#endif /* defined(__cocosTest__LayerManager__) */
