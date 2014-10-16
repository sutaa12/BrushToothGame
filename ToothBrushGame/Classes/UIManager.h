//
//  UIManager.h
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/16.
//
//

#ifndef __ToothBrushGame__UIManager__
#define __ToothBrushGame__UIManager__

//********************************************************************************
// インクルード
//********************************************************************************
#include "cocos2d.h"

//********************************************************************************
// 名前空間の使用
//********************************************************************************
using namespace cocos2d;

//********************************************************************************
// 前方クラス宣言
//********************************************************************************
class Score;
class MenuBar;
class LifeBar;
class Item;

//********************************************************************************
// クラス宣言
//********************************************************************************
class UIManager
{
public:
    UIManager();
    ~UIManager();

    bool init(void);
    void uninit(void);
    void update(void);

    static UIManager* create(const Vec2& startLeftTopPos,Layer* layer);

    Score* getScore(void){return m_pScore;}
    MenuBar* getMenuBar(void){return m_pMenuBar;}
    LifeBar* getLifeBar(void){return m_pLifeBar;}
    Item* getItem(void){return m_pItem;}

    //void addTopGumPosAndTopToothPos(const Vec2& vec);
    //void addBottomGumPosAndBottomToothPos(const Vec2& vec);
    //void moveToothAndGum(float time, Vec2 pos);

private:
    Vec2 m_startLeftTopPos;

    Score* m_pScore;
    MenuBar* m_pMenuBar;

    LifeBar* m_pLifeBar;
    Item* m_pItem;

    Layer* m_pLayer;
};


#endif /* defined(__ToothBrushGame__UIManager__) */
