#include "AppDelegate.h"
#include "GameMainScene.h"
#include "TitleScene.h"
#include "Random.h"
#include "Sound.h"
#include "common.h"
#include "AchievementDataBase.h"
#include "SoundManager.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
    AppDelegate::SoundUnload();
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("BrushToothGame");
    }

    director->setOpenGLView(glview);
    glview->setDesignResolutionSize(SCREEN_WIDTH, SCREEN_HEIGHT, ResolutionPolicy::SHOW_ALL);
    //乱数初期化
    RandomMT::initRand();
    //リソースのパスを格納するvector
    std::vector< std::string > searchPath;
    searchPath.push_back("bgm");
    searchPath.push_back("fonts");
    searchPath.push_back("se");
    searchPath.push_back("hd");
    //サーチパスに設定
    FileUtils::sharedFileUtils()->setSearchPaths(searchPath);

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    SoundPreload();

    AchievementDataBaseList::init();
    //実績スコアリセット
    //AchievementDataBaseList::resetAchievement();
    
    AchievementDataBaseList::addAchievement(ACHIEVE_TYPE_TURN_ON);
    
    // create a scene. it's an autorelease object
    //auto scene = GameMainScene::createScene();
    auto scene = TitleScene::createScene();
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // BGM・SE一時停止
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // BGM・SE再開
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
}

//SE、BGMをプリロードする
void AppDelegate::SoundPreload() {

    SoundManager::init();

}
//データ解放
void AppDelegate::SoundUnload() {

    SoundManager::uninit();

}
