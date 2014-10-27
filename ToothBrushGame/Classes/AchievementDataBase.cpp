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
    "ACHIEVEMENT_TYPE_ENEMY_LAIR_ONE_DOWN",//レア種類の敵を倒した数
    "ACHIEVEMENT_TYPE_ENEMY_LAIR_TWO_DOWN",
    "ACHIEVEMENT_TYPE_TAP_GIRL_TITLE",//タイトルの女の子のタップ回数
    "ACHIEVEMENT_TYPE_SWIPE_GIRL_TITLE",//タイトルの女の子のスワイプ回数
    "ACHIEVEMENT_TYPE_TAP_GIRL_GAMESTATUS",//ステータスの女の子のタップ回数
    "ACHIEVEMENT_TYPE_SWIPE_GIRL_GAMESTATUS",//ステータスの女の子スワイプ回数
};

const std::string ACHIEVEMENT_STATUSNAME[ACHIEVEMENT_MAX]
{
    "ACHIEVE_TYPE_NONE",//実績タイプ
    "きどうしたかいすう",//起動回数
    "みがいたかいすう",//プレイ回数
    "ばいばいしたばいきんさん",//倒した敵の総数
    "ばいばいしたよわいばいきんさん",//普通の種類の敵の倒した数
    "ばいばいしたふつうのばいきんさん",
    "ばいばいしたれあなばいきんさん",//レア種類の敵を倒した数
    "ばいばいしたれあなつよいばいきんさん",
    "歯磨き以外でお前に触られた数",//タイトルの女の子のタップ回数
    "歯磨き以外でお前になでられた数",//タイトルの女の子のスワイプ回数
    "歯磨き中にお前に触られた数",//ステータスの女の子のタップ回数
    "歯磨き中でお前になでられた数",//ステータスの女の子スワイプ回数
};

int AchievementDataBaseList::m_nAchievementCont[ACHIEVEMENT_MAX];
int AchievementDataBaseList::m_nAchivementSize;
bool* AchievementDataBaseList::m_pAchievemntFlag;
std::string* AchievementDataBaseList::m_pAchievemntDate;
AchievementDataBaseList::ACHIEVE_STATUS AchievementData[]=
{
    {"実績1","実績フラグ1",ACHIEVE_TYPE_TURN_ON,1,"","はじめてのはみがき","ゲームを始めて起動する"},
    {"実績2","実績フラグ2",ACHIEVE_TYPE_GAME_PLAY,1,"","たのしいはみがき","ゲームを始めて開始する"},
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

void AchievementDataBaseList::addAchievement(ACHIEVEMENT_KIND achievement)
{
    m_nAchievementCont[achievement]++;
    chkAchievement(achievement);
    saveAchievement();
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
            if(!m_pAchievemntFlag[achieve])
            {
                if(m_nAchievementCont[achieve] >= AchievementData[nloop].unlockNum)
                {
                    m_pAchievemntFlag[achieve] = true;
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
