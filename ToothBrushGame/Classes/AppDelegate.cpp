#include "AppDelegate.h"
#include "GameMainScene.h"
#include "TitleScene.h"
#include "Random.h"
#include "Sound.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{

}

bool AppDelegate::applicationDidFinishLaunching() {
    //乱数初期化
    RandomMT::initRand();

    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("BrushToothGame");
        director->setOpenGLView(glview);
        
        //glview->setDesignResolutionSize(320, 480, ResolutionPolicy::SHOW_ALL);
        //director->setContentScaleFactor(1920 / 480);
    }
    
    std::vector< std::string > searchPath;    //リソースのパスを格納するvector
    //画像フォルダ指定
    searchPath.push_back("hd");
    
    //音楽フォルダ指定
    searchPath.push_back("se");
    searchPath.push_back("bgm");

    //サーチパスに設定
    FileUtils::getInstance()->setSearchPaths(searchPath);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

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
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

//SE、BGMをプリロードする
void SoundPreload() {

//BGM
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BGM_BOSS_SCENE_1);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BGM_BOSS_SCENE_2);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BGM_BOSS_SCENE_3);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BGM_BOSS_SCENE_4);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BGM_BOSS_SCENE_5);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BGM_BOSS_SCENE_6);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BGM_BOSS_SCENE_7);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BGM_BOSS_SCENE_8);

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BGM_ENEMY_SCENE_1);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BGM_ENEMY_SCENE_2);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BGM_ENEMY_SCENE_3);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BGM_ENEMY_SCENE_4);

        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BGM_GAME_CLEAR_1);

        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BGM_STAGE_SELECT_1);
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BGM_STAGE_SELECT_2);

            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BGM_RESULT_1);



//SE
    //ボタン
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SE_BUTTON_1);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SE_BUTTON_2);

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SE_START_BUTTON_1);

    //敵
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SE_ENEMY_DOWN_1);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SE_ENEMY_DOWN_2);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SE_ENEMY_DOWN_3);

    //ボス

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SE_BOSS_DOWN_1);

        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SE_BOSS_APPEAR_1);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SE_BOSS_GAME_OVER_1);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SE_BOSS_GAME_OVER_2);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SE_DAMAGE_1);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SE_SWIPE_1);
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SE_SWIPE_2);
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SE_SWIPE_3);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SE_FANFARE_1);
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SE_GAME_OVER_1);




}
//データ解放
void SoundUnload() {
    //ボタン
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(SE_BUTTON_1);
    //敵
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(SE_ENEMY_DOWN_1);
    //ボス
}