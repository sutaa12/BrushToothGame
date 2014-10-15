//
//  ToothManager.cpp
//  cocosTest
//
//  Created by 鈴木 愛忠 on 2014/10/10.
//
//

#include "TextureManager.h"
#include "ToothManager.h"

ToothManager::ToothManager(cocos2d::Vec2 &pos)
{

    
    for(int loop = 0; loop < 2 ;loop++)
    {
        
        m_toothData.ToothMeat[loop] = cocos2d::Sprite::create(TextureManager::getTexure(TEX_TOOTHMEAT));
        m_toothData.Tooth[loop] = cocos2d::Sprite::create(TextureManager::getTexure(TEX_TOOTH));

    }
    cocos2d::Vec2 tooth0 = pos;
    cocos2d::Vec2 tooth1 = pos;
    cocos2d::Vec2 tMeat0 = pos;
    cocos2d::Vec2 tMeat1 = pos;
    tooth0.y += m_toothData.ToothMeat[0]->getContentSize().height;
    tooth1.y += m_toothData.ToothMeat[0]->getContentSize().height + m_toothData.Tooth[0]->getContentSize().height;
    tMeat1.y += m_toothData.ToothMeat[0]->getContentSize().height;

        //歯茎の設定
        m_toothData.ToothMeat[0]->setPosition(tMeat0);
        m_toothData.ToothMeat[1]->setPosition(tMeat1);
        
        m_toothData.ToothDataMeat[0].origin = pos - m_toothData.Tooth[0]->getContentSize() / 2;
        m_toothData.ToothDataMeat[0].size = m_toothData.ToothMeat[0]->getContentSize();


        m_toothData.Tooth[0]->setPosition(tooth0);
        m_toothData.Tooth[1]->setPosition(tooth1);
        
        m_toothData.ToothData[0].origin = pos - m_toothData.Tooth[0]->getContentSize() / 2;
        m_toothData.ToothData[0].size = m_toothData.Tooth[0]->getContentSize();

    m_toothData.Tooth[1]->setRotation(180);
    m_toothData.ToothMeat[1]->setRotation(180);

}