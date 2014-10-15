#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
class ToothManager;
class HelloWorld : public cocos2d::Layer
{
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    // タッチ判定処理
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    // パン・スワイプ時
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    //-------------------------
    // 更新処理
    void update(float delta);
    //メンバ変数
    //カウンター
    int m_cont;
    //座標
    cocos2d::Point m_ImagePosition;
    //移動速度
    cocos2d::Point m_ImageMove;
    
    cocos2d::Sprite* sprite;
    
    ToothManager* m_Tooth;
};

#endif // __HELLOWORLD_SCENE_H__
