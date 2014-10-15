#include "HelloWorldScene.h"
#include "TextureManager.h"
#include "ToothManager.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. レイヤーの初期化ができなかったら終了
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //スケジュールの更新設定
    this->scheduleUpdate();

    //カウント初期化
    m_cont = 0;
    
    m_ImagePosition = Point(0,0);
    m_ImageMove = Point(0,0);
    
    //イベントリスナー作成
    auto listener = EventListenerTouchOneByOne::create();
    
    //イベントを飲み込むかどうか
    listener->setSwallowTouches(true);
    
    //タッチメソッド設定
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    
    //優先度100でディスパッチャーに登録
    this->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 100);
    
    /////////////////////////////
    //メニューボタンオブジェクトの作成
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // メニューのボタン生成
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //HelloWorld文字列表示
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // 位置設定
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    // add the label as a child to this layer
    this->addChild(label, 1);

    Vec2 ToothPos = Vec2(visibleSize.width/2 + origin.x, 0);
    m_Tooth = new ToothManager(ToothPos);
    this->addChild(m_Tooth->getTooth().Tooth[0]);
    this->addChild(m_Tooth->getTooth().Tooth[1]);
    this->addChild(m_Tooth->getTooth().ToothMeat[0]);
    this->addChild(m_Tooth->getTooth().ToothMeat[1]);
    
return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
//-------------------------
// タップ時
bool HelloWorld::onTouchBegan(Touch *touch, Event *event)
{
    Point location = touch->getLocation();
    CCLOG("x:%f, y:%f", location.x, location.y);
    m_ImageMove = location - m_ImagePosition;
    m_ImagePosition = location;
    return true;
}

//-------------------------
// パン・スワイプ時
void HelloWorld::onTouchMoved(Touch *touch, Event *event)
{
    Point location = touch->getLocation();
    m_ImageMove = location - m_ImagePosition;
    
    m_ImagePosition = location;
}
//-------------------------
// 更新処理
void HelloWorld::update(float delta) {
    m_cont++;
    CCLOG("test : %d", m_cont);
    
}
