//
//  AchievementList.h
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/23.
//
//

#ifndef __ToothBrushGame__AchievementList__
#define __ToothBrushGame__AchievementList__
#include <cocos2d.h>
#include <extensions/cocos-ext.h>
#include "common.h"
USING_NS_CC;
using namespace cocos2d::extension;

class AchievementList :
public TableViewDataSource,
public TableViewDelegate
{
public:
    AchievementList(){}
    ~AchievementList(){}
    
    static AchievementList* create(Layer* layer);
    virtual bool init();
    
    //TableViewDataSourceの抽象メソッド
    virtual Size cellSizeForTable(TableView* table);
    virtual TableViewCell* tableCellAtIndex(TableView* table,ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    
    //TableViewDelegateの抽象メソッド
    virtual void tableCellTouched(TableView* table,TableViewCell* cell);
    
    //TableViewDelegateが継承しているScrollViewの抽象メソッド
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view){};
private:
    Size m_window_size;
    Layer* m_pLayer;
    
};
#endif /* defined(__ToothBrushGame__AchievementList__) */
