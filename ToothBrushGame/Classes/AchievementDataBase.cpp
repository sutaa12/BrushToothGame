//
//  AchievementDataBase.cpp
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/23.
//
//

#include <time.h>
#include "AchievementDataBase.h"
#include "AchieveLayer.h"
AchieveLayer* AchievementDataBaseList::m_pAchieveLayer;
const char* ACHIEVEMENT_NAME[ACHIEVEMENT_MAX]
{
    "ACHIEVE_TYPE_NONE",//実績タイプ
    "ACHIEVE_TYPE_TURN_ON",//起動回数
    "ACHIEVE_TYPE_GAME_PLAY",//プレイ回数
    "ACHIEVEMENT_TYPE_ENEMY_DOWN",//倒した敵の総数
    "ACHIEVEMENT_TYPE_ENEMY_NORMAL_ONE_DOWN",//普通の種類の敵の倒した数
    "ACHIEVEMENT_TYPE_ENEMY_NORMAL_TWO_DOWN",
    "ACHIEVEMENT_TYPE_ENEMY_NORMAL_TREE_DOWN",
    "ACHIEVEMENT_TYPE_ENEMY_LAIR_ONE_DOWN",//レア種類の敵を倒した数
    "ACHIEVEMENT_TYPE_ENEMY_LAIR_TWO_DOWN",
    "ACHIEVEMENT_TYPE_ENEMY_LAIR_TREE_DOWN",
    "ACHIEVEMENT_TYPE_USE_UGAI",//うがいを使用した回数
    "ACHIEVEMENT_TYPE_USE_TOOTHPOWDER",//歯磨きボムを使用した回数
    "ACHIEVEMENT_TYPE_USE_TOUP",//タップした回数
    "ACHIEVEMENT_TYPE_GAME_TOP_SCORE",//１ゲームのトップスコア
    "ACHIEVEMENT_TYPE_GAME_TOP_ENEMY_DOWN",//１ゲームの敵の最高で倒した数
    "ACHIEVEMENT_TYPE_GAME_TOP_ENEMY_DOWN_BOM",//１ゲームでボムで倒した敵の数
    "ACHIEVEMENT_TYPE_GAME_MIN_USE_BOM",//１ゲームでボムを使用した最も少ない回数
    "ACHIEVEMENT_TYPE_GAME_MAX_USE_BOM",//１ゲームでボムを使用した最も多い回数
    "ACHIEVEMENT_TYPE_GAME_USE_UGAI",//うがいを使用した回数
    "ACHIEVEMENT_TYPE_GAME_MAX_USE_ENEMY_DOWN_BOM",//１ゲームでボム使用で倒した敵で最も多い回数
    "ACHIEVEMENT_TYPE_GAME_TIME",//ゲームにかかった最短タイム
};

const std::string ACHIEVEMENT_STATUSNAME[ACHIEVEMENT_MAX]
{
    "ACHIEVE_TYPE_NONE",//実績タイプ
    "きどうしたかいすぅ　　　　　　　　　　　　　　　　　　",//起動回数
    "はみがきしたかいすぅ　　　　　　　　　　　　　　　　　",//プレイ回数
    "ばいばいしたばいきんさん　　　　　　　　　　　　　　　",//倒した敵の総数
    "ばいばいしたよわいばいきんさん　　　　　　　　　　　　",//普通の種類の敵の倒した数
    "ばいばいしたふつうのばいきんさん　　　　　　　　　　　",
    "ばいばいしたつよいのばいきんさん　　　　　　　　　　　",
    "ばいばいしたれあなよわいばいきんさん　　　　　　　　　",//レア種類の敵を倒した数
    "ばいばいしたれあなばいきんさん　　　　　　　　　　　　",//レア種類の敵を倒した数
    "ばいばいしたれあなつよいばいきんさん　　　　　　　　　",
    "がらがらっぺしたかいすぅ　　　　　　　　　　　　　　　",
    "おくちのなかすぅすぅしたかいすぅ　　　　　　　　　　　",
    "おくちにさわられたかいすぅ　　　　　　　　　　　　　　",
    "とっぷすこぁ　　　　　　　　　　　　　　　　　　　　　",//１ゲームのトップスコア
    "いっかいでいっぱいばいばいしたかずぅ　　　　　　　　　",//１ゲームの敵の最高で倒した数
    "いっかいのはみがきこぉでたぉしたかずぅ　　　　　　　　",//１ゲームでボムで倒した敵の数
    "はみがきではみがきこをつかわなかったかずぅ　",//１ゲームでボムを使用した最も少ない回数
    "みがきでいっぱいはみがきこをつかったかずぅ　　",//１ゲームでボムを使用した最も多い回数
    "いっかいのはみがきでいっぱいうがいしたかずぅ　　　　　",//うがいを使用した回数
    "はみがきこでばいばいしたばいきんさんがいちばんのかずぅ",//１ゲームでボム使用で倒した敵で最も多い回数
    "はみがきがいちばんみじかかったかずぅ　　　　　　　　　",//ゲームにかかった最短タイム
};

int AchievementDataBaseList::m_nAchievementCont[ACHIEVEMENT_MAX];
int AchievementDataBaseList::m_nAchivementSize;
bool* AchievementDataBaseList::m_pAchievemntFlag;
std::string* AchievementDataBaseList::m_pAchievemntDate;
AchievementDataBaseList::ACHIEVE_STATUS AchievementData[]=
{
    {"実績1","実績フラグ1",ACHIEVE_TYPE_TURN_ON,1,"はじめてのはみがき","ゲームを初めて起動する"},
    {"実績2","実績フラグ2",ACHIEVE_TYPE_GAME_PLAY,1,"たのしいはみがき","初めてゲームを始める"},
    {"実績3","実績フラグ3",ACHIEVEMENT_TYPE_ENEMY_DOWN,100,"ごじゅぅたぉしたぁ！","敵を５０体倒した！"},
    {"実績4","実績フラグ4",ACHIEVEMENT_TYPE_ENEMY_DOWN,100,"ひゃぁくたぉしたぁ！","敵を１００体倒した！"},
    {"実績5","実績フラグ5",ACHIEVEMENT_TYPE_ENEMY_DOWN,500,"ごひゃぁくたぉしたぁ！","敵を５００体倒した！"},
    {"実績6","実績フラグ6",ACHIEVEMENT_TYPE_ENEMY_DOWN,1000,"さうざんとぉすとらぁいく","敵を１０００体倒した！"},
    {"実績7","実績フラグ7",ACHIEVEMENT_TYPE_ENEMY_DOWN,5000,"ふぇぇいっぱいだよぉ","敵を５０００体倒した！"},
    {"実績8","実績フラグ8",ACHIEVEMENT_TYPE_ENEMY_DOWN,10000,"汚れ過ぎ","敵を１００００体倒した！"},
    {"実績9","実績フラグ9",ACHIEVEMENT_TYPE_GAME_TOP_SCORE,600,"もっとみがいてよぉ","スコア600pt達成した！",},
    {"実績10","実績フラグ10",ACHIEVEMENT_TYPE_GAME_TOP_SCORE,1000,"おくちきれいきれい","スコア1000pt達成した！"},
    {"実績11","実績フラグ11",ACHIEVEMENT_TYPE_GAME_TOP_SCORE,1500,"いっぱいみがいたね！","スコア1500達成した！"},
    {"実績12","実績フラグ12",ACHIEVEMENT_TYPE_ENEMY_DOWN,1800,"やばい。","スコア1800pt達成した！"},
    {"実績13","実績フラグ13",ACHIEVEMENT_TYPE_GAME_MIN_USE_BOM,0,"たっぷますたぁ。","タップのみでクリアした！"}
};

std::string strsprintf(const char* format,...){
    va_list ap;
    va_start(ap, format);
    char* alloc;
    if(vasprintf(&alloc,format,ap) == -1) {
        return std::string("");
    }
    va_end(ap);
    std::string retStr = std::string(alloc);
    free(alloc);
    return retStr;
}
AchievementDataBaseList::~AchievementDataBaseList()
{
    SAFE_DELETE_ARRAY(m_pAchievemntDate);SAFE_DELETE_ARRAY(m_pAchievemntFlag);SAFE_DELETE(m_pAchieveLayer);
}

//初期化
void AchievementDataBaseList::init()
{
    //実績情報の配列数数える
    m_nAchivementSize = sizeof(AchievementData) / sizeof(AchievementData[0]);
    m_pAchievemntDate = new std::string[m_nAchivementSize];
    m_pAchievemntFlag = new bool[m_nAchivementSize];
    loadAchievement();
    // 共有レイヤー追加
    Director::getInstance()->setNotificationNode(Node::create());
    // 共有レイヤー内にデバッグ用レイヤー追加
    m_pAchieveLayer = AchieveLayer::create();
    m_pAchieveLayer->setTag(999);
    DisplayLinkDirector::getInstance()->getNotificationNode()->addChild((Node*)m_pAchieveLayer,9999);
    m_pAchieveLayer->onEnter();
}
//実績リスト入手
AchievementDataBaseList::ACHIEVE_STATUS AchievementDataBaseList::getAchievement(int achieveInfo){
    return AchievementData[achieveInfo];
}

//実績リスト入手
std::string AchievementDataBaseList::getAchievementName(int achieveInfo){
    return ACHIEVEMENT_STATUSNAME[achieveInfo];
}

void AchievementDataBaseList::addAchievement(ACHIEVEMENT_KIND achievement,bool bSave)
{
    m_nAchievementCont[achievement]++;
    chkAchievement(achievement);
    if(bSave)
    {
        saveAchievement();
    }
}

void AchievementDataBaseList::dispAchievement(int nUnlcok)
{
    m_pAchieveLayer->setDispAchieveLayer(nUnlcok);
}

void AchievementDataBaseList::saveAchievement()
{
    //保存先の生成
    UserDefault *userDef = UserDefault::getInstance();
    for(int nloop = 0;nloop < ACHIEVEMENT_MAX;nloop++)
    {
        userDef->setIntegerForKey(ACHIEVEMENT_NAME[nloop], m_nAchievementCont[nloop]);
    }
    for(int nloop = 0;nloop<m_nAchivementSize;nloop++)
    {
        userDef->setBoolForKey(AchievementData[nloop].boolname,m_pAchievemntFlag[nloop]);
        userDef->setStringForKey(AchievementData[nloop].name,m_pAchievemntDate[nloop]);
    }
    //書き込み
    userDef->flush();
}

void AchievementDataBaseList::loadAchievement()
{
    //ロードの生成
    UserDefault *userDef = UserDefault::getInstance();
    for(int nloop = 0;nloop < ACHIEVEMENT_MAX;nloop++)
    {
        m_nAchievementCont[nloop] = userDef->getIntegerForKey(ACHIEVEMENT_NAME[nloop], 0);
    }
    for(int nloop = 0;nloop < m_nAchivementSize;nloop++)
    {
        m_pAchievemntFlag[nloop] = userDef->getBoolForKey(AchievementData[nloop].boolname,false);
        m_pAchievemntDate[nloop] = userDef->getStringForKey(AchievementData[nloop].name,"");
    }
}
void AchievementDataBaseList::resetAchievement()
{
    //保存先の生成
    UserDefault *userDef = UserDefault::getInstance();
    for(int nloop = 0;nloop < ACHIEVEMENT_MAX;nloop++)
    {
        m_nAchievementCont[nloop] = 0;

        userDef->setIntegerForKey(ACHIEVEMENT_NAME[nloop],0);
    }
    for(int nloop = 0;nloop<m_nAchivementSize;nloop++)
    {
        m_pAchievemntFlag[nloop] = false;
        m_pAchievemntDate[nloop] = "";

        userDef->setBoolForKey(AchievementData[nloop].boolname,false);
        userDef->setStringForKey(AchievementData[nloop].name,"");
    }
    //書き込み
    userDef->flush();
}
void AchievementDataBaseList::chkAchievement(ACHIEVEMENT_KIND achieve)
{
    for(int nloop = 0;nloop<m_nAchivementSize;nloop++)
    {
        if(AchievementData[nloop].achieveFlagKind == achieve)
        {
            if(!m_pAchievemntFlag[nloop])
            {
                if(m_nAchievementCont[achieve] >= AchievementData[nloop].unlockNum)
                {
                    m_pAchievemntFlag[nloop] = true;
                    time_t curTime;
                    tm *timeObject;
                    time(&curTime);
                    timeObject = localtime(&curTime);
                    std::string time = strsprintf("%d年 %d月 %d日 %d : %d : %d" ,
                                           timeObject->tm_year + 1900 , timeObject->tm_mon + 1 ,
                                           timeObject->tm_mday , timeObject->tm_hour ,
                                           timeObject->tm_min , timeObject->tm_sec);
                    m_pAchievemntDate[nloop].swap(time);
                    dispAchievement(nloop);
                }
            }
            
        }
    }
}
void AchievementDataBaseList::chkAchievementMin(ACHIEVEMENT_KIND achieve)
{
    for(int nloop = 0;nloop<m_nAchivementSize;nloop++)
    {
        if(AchievementData[nloop].achieveFlagKind == achieve)
        {
            if(!m_pAchievemntFlag[nloop])
            {
                if(m_nAchievementCont[achieve] <= AchievementData[nloop].unlockNum)
                {
                    m_pAchievemntFlag[nloop] = true;
                    time_t curTime;
                    tm *timeObject;
                    time(&curTime);
                    timeObject = localtime(&curTime);
                    std::string time = strsprintf("%d年 %d月 %d日 %d : %d : %d" ,
                                                  timeObject->tm_year + 1900 , timeObject->tm_mon + 1 ,
                                                  timeObject->tm_mday , timeObject->tm_hour ,
                                                  timeObject->tm_min , timeObject->tm_sec);
                    m_pAchievemntDate[nloop].swap(time);
                    dispAchievement(nloop);
                }
            }
            
        }
    }
}

void AchievementDataBaseList::setAchievementMin(ACHIEVEMENT_KIND achievement,int nNum,bool bSave)
{
    if(nNum < m_nAchievementCont[achievement])
    {
        m_nAchievementCont[achievement] = nNum;
        chkAchievementMin(achievement);
        
        if(bSave)
        {
            saveAchievement();
        }
    }
}
void AchievementDataBaseList::setAchievementMax(ACHIEVEMENT_KIND achievement,int nNum,bool bSave)
{
    if(nNum > m_nAchievementCont[achievement])
    {
    m_nAchievementCont[achievement] = nNum;
    chkAchievement(achievement);
        if(bSave)
        {
            saveAchievement();
        }
    }
}
