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

    static UIManager* create(Layer* layer);

    Score* getScore(void){return m_pScore;}
    MenuBar* getMenuBar(void){return m_pMenuBar;}
    LifeBar* getLifeBar(void){return m_pLifeBar;}

private:
    Sprite* m_pGameTopBack;
    Sprite* m_pGameBottomBack;
    
    Score* m_pScore;
    MenuBar* m_pMenuBar;
    LifeBar* m_pLifeBar;
    Layer* m_pLayer;
    static const int GAME_MENU_BOTTOM_Y = 192 / 2;
};


#endif /* defined(__ToothBrushGame__UIManager__) */
