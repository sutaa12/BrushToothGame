//
//  VirusToothManager.cpp
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/28.
//
//

#include "VirusToothManager.h"

//********************************************************************************
// インクルード
//********************************************************************************
#include "common.h"
#include "VirusToothManager.h"
#include "VirusTooth.h"
#include "Random.h"
const Point SPAWN_POINTS[]=
{
    Point(100,600),Point(200,600),Point(300,600),Point(400,600),Point(500,600),
    Point(150,600),Point(250,600),Point(350,600),Point(450,600),Point(550,600),
    Point(100,90),Point(200,90),Point(300,90),Point(400,90),Point(500,90),
    Point(150,90),Point(250,90),Point(350,90),Point(450,90),Point(550,90),
    Point(50,275),Point(50,300),Point(600,230),Point(570,300),
    Point(50,430),Point(580,480),Point(580,430),Point(580,480),

};

//================================================================================
// コンストラクタ
//================================================================================
VirusToothManager::VirusToothManager(int numVirusTooth)
{
    
    // メンバ変数の初期化
    if(numVirusTooth >= VIRUSTOOTH_MAX)
    {
        numVirusTooth = VIRUSTOOTH_MAX - 1;
    }
    m_numVirusTooth = numVirusTooth;
    m_pLayer = nullptr;
    for(int nloop = 0;nloop < VIRUSTOOTH_MAX;nloop++)
    {
        m_pVirusTooth[nloop] = nullptr;
    }
    m_nTime = 0;
    m_nVirusPosMax = sizeof(SPAWN_POINTS) / sizeof(SPAWN_POINTS[0]);
}

//================================================================================
// デストラクタ
//================================================================================
VirusToothManager::~VirusToothManager()
{
    for(int nloop = 0;nloop < VIRUSTOOTH_MAX;nloop++)
    {
        SAFE_DELETE(m_pVirusTooth[nloop]);
    }
}

//================================================================================
// 初期化処理
//================================================================================
bool VirusToothManager::init(void)
{
    for(int nloop = 0;nloop < VIRUSTOOTH_MAX;nloop++)
    {
        m_pVirusTooth[nloop] = VirusTooth::create(Vec2(0,0));
        m_pLayer->addChild(m_pVirusTooth[nloop]->getSprite());
        
    }
    spawn(Vec2(-1,-1));
    
    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void VirusToothManager::uninit(void)
{
    
}

//================================================================================
// 更新処理
//================================================================================
void VirusToothManager::update(void)
{
    m_nTime++;
    
}

//================================================================================
// 生成処理
//================================================================================
VirusToothManager* VirusToothManager::create(Layer* layer,Sprite* pSprite)
{
    // 歯マネージャーのインスタンス化
    VirusToothManager* pVirusToothManager = new VirusToothManager(PHASE_MAX);
    pVirusToothManager->m_pos = Vec2(pSprite->getPosition().x + pSprite->getContentSize().width / 2,pSprite->getPosition().y + pSprite->getContentSize().height / 2);
    // メンバー変数の代入
    pVirusToothManager->m_pLayer = layer;
    
    // 初期化
    pVirusToothManager->init();
    
    return pVirusToothManager;
}

//================================================================================
// 敵生成処理
//================================================================================
void VirusToothManager::spawn(Vec2 pos)
{
    Size visibleSize = Director::getInstance()->getVisibleSize() / 2 + SCREEN_CENTER;
    Vec2 origin = Director::getInstance()->getVisibleSize() / 2 - SCREEN_CENTER;
    Vec2 MaxPos = Vec2(visibleSize.width - origin.x,visibleSize.height - 128 - origin.y);
    Vec2 MinPos = Vec2(origin.x,MaxPos.y - 512 + origin.y);
    Vec2 posPown;
    int nVirusToothNum = 0;
    
    for(int nloop = 0 ;nloop < VIRUSTOOTH_MAX ;nloop++)
    {
        if(m_pVirusTooth[nloop]->getVirusToothDownFlag())
        {
            if(pos.x == -1 && pos.y == -1)
            {
                int rand = RandomMT::getRaodom(0,m_nVirusPosMax);
                posPown = m_pos - SPAWN_POINTS[rand];
            }
            m_pVirusTooth[nloop]->setSpawn(posPown);
            nVirusToothNum++;
        }
    }
}

bool VirusToothManager::collideAtPoint(Sprite* pSprite, Point point)
{
    bool bCollision = false;
    
    int searchWidth = 1;
    int searchHeight = 1;
    
    unsigned int numPixels = searchWidth * searchHeight;
    
    Size size = Director::getInstance()->getWinSize();
    RenderTexture *rt =RenderTexture::create(size.width, size.height, kCCTexture2DPixelFormat_RGBA8888);
    rt->beginWithClear(0, 0, 0, 0);
    
    // Render both sprites: first one in RED and second one in GREEN
    glColorMask(1, 0, 0, 1);
    pSprite->visit();
    glColorMask(1, 1, 1, 1);
    
    // Get color values of intersection area
    Color4B *buffer = (Color4B *)malloc( sizeof(Color4B) * numPixels );
    glReadPixels(point.x, point.y, searchWidth, searchHeight, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    
    unsigned int step = 1;
    for(unsigned int i=0; i<numPixels; i+=step) {
        Color4B color = buffer[i];
        //CCLog("Pixel color: %d, %d, %d", color.r, color.g, color.b);
        if (color.r > 0) {
            bCollision = true;
            CCLOG("Colliding");
            break;
        }
    }
    rt->end();
    return bCollision;
}
