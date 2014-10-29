//
//  AchieveLayer.cpp
//  ToothBrushGame
//
//  Created by 鈴木愛忠 on 2014/10/27.
//
//

#include "AchieveLayer.h"
#include "common.h"
#include "TextureFile.h"
#include "AchievementList.h"
#include "TitleScene.h"
#include "GameMainScene.h"
#include "RankManager.h"
#include "Sound.h"
USING_NS_CC;
//================================================================================
// シーン生成
//================================================================================
Scene* AchieveLayer::createScene(void)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = AchieveLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

//================================================================================
// シーン初期化
//================================================================================
// on "init" you need to initialize your instance
bool AchieveLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize() / 2 + SCREEN_CENTER;
    Vec2 origin = Director::getInstance()->getVisibleSize() / 2 - SCREEN_CENTER;
    
    m_pAchieve = Sprite::create(TEX_ACHIEVE_WINDOW);
    m_pAchieve->setColor(Color3B::WHITE);
    m_pAchieve->setPosition(Vec2(origin.x -ACHIEVE_LAYER_POS_WIDTH / 2,origin.y + 850));
    
    // 文字列
    m_pTitle = LabelTTF::create("実績解除",MIKA_FONT, 24);
    //左上の位置に設定
    m_pTitle->setPosition(Vec2(-ACHIEVE_LAYER_POS_WIDTH / 2,origin.y + 880));

    // 文字列
    m_pMessage = LabelTTF::create("", MIKA_FONT, 24);
    //左上の位置に設定
    m_pMessage->setPosition(Vec2(-ACHIEVE_LAYER_POS_WIDTH / 2,origin.y + 840));
    
    this->addChild(m_pAchieve,9996);
    this->addChild(m_pMessage,9997);
    this->addChild(m_pTitle,9998);
        return true;
}

//================================================================================
// ゲーム更新
//================================================================================
void AchieveLayer::update(float fTime)
{
}

//================================================================================
// タップ開始判定
//================================================================================

bool AchieveLayer::onTouchBegin(Touch* pTouch,Event* pEvent)
{
    // タッチ座標の取得
    m_touchPos = pTouch->getLocation();
    return true;
}

//================================================================================
// スワイプ判定
//================================================================================

void AchieveLayer::onTouchMoved(Touch* pTouch,Event* pEvent)
{
    
    // タッチ座標の取得
    m_oldTouchPos = m_touchPos;
    m_touchPos = pTouch->getLocation();
}

//================================================================================
// タップ離した判定
//================================================================================

void AchieveLayer::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    
}

//================================================================================
// タッチ時に割り込み処理
//================================================================================
void AchieveLayer::onTouchCancelled(Touch* pTouch, Event* pEvent)
{
    
}

//================================================================================
// タイトルボタン処理
//================================================================================
void AchieveLayer::ButtonTitle(void)
{
    this->getEventDispatcher()->removeAllEventListeners();
    this->removeAllChildren();
    this->unscheduleUpdate();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f,TitleScene::createScene(),Color3B::WHITE));
}

//実績解除表示
void AchieveLayer::setDispAchieveLayer(int nAchieveNum)
{
    Vec2 origin = Director::getInstance()->getVisibleSize() / 2 - SCREEN_CENTER;

    m_pAchieve->stopAllActions();
    m_pMessage->stopAllActions();
    m_pTitle->stopAllActions();
    m_pAchieve->setPosition(Vec2(origin.x -ACHIEVE_LAYER_POS_WIDTH / 2,origin.y + 850));
    //左上の位置に設定
    m_pTitle->setPosition(Vec2(-ACHIEVE_LAYER_POS_WIDTH / 2,origin.y + 880));
    
    //左上の位置に設定
    m_pMessage->setPosition(Vec2(-ACHIEVE_LAYER_POS_WIDTH / 2,origin.y + 840));
    
    
    m_pMessage->setString(AchievementDataBaseList::getAchievement(nAchieveNum).title);
    m_pMessage->setColor(Color3B::BLACK);
    m_pTitle->setColor(Color3B::BLACK);

    m_pAchieve->runAction(Sequence::create(MoveBy::create(1.0f,Vec2(ACHIEVE_LAYER_POS_WIDTH,0)),MoveBy::create(2.0f,Vec2(0,0)),MoveBy::create(1.0f,Vec2(-ACHIEVE_LAYER_POS_WIDTH,0)), NULL));
    m_pMessage->runAction(Sequence::create(MoveBy::create(1.0f,Vec2(ACHIEVE_LAYER_POS_WIDTH,0)),MoveBy::create(2.0f,Vec2(0,0)),MoveBy::create(1.0f,Vec2(-ACHIEVE_LAYER_POS_WIDTH,0)), NULL));
    m_pTitle->runAction(Sequence::create(MoveBy::create(1.0f,Vec2(ACHIEVE_LAYER_POS_WIDTH,0)),MoveBy::create(2.0f,Vec2(0,0)),MoveBy::create(1.0f,Vec2(-ACHIEVE_LAYER_POS_WIDTH,0)), NULL));

    //SE
    SimpleAudioEngine::getInstance()->playEffect(SE_GET_ACHIEVEMENT_4);

}

