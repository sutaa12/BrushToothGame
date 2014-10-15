//
//  LayerManager.cpp
//  cocosTest
//
//  Created by 鈴木 愛忠 on 2014/10/08.
//
//

#include "LayerManager.h"
LayerManager* LayerManager::m_Layer[LAYER_MAX];
bool LayerManager::initLayer(void)
{
    for (int loop = 0; loop < LAYER_MAX; loop++) {
        m_Layer[loop] = LayerManager::create();
        if ( !m_Layer[loop]->init())
        {
            return false;
        }
    }
    return true;
}