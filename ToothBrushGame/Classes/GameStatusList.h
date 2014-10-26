//
//  GameStatusList.h
//  ToothBrushGame
//
//  Created by 鈴木愛忠 on 2014/10/27.
//
//

#ifndef __ToothBrushGame__GameStatusList__
#define __ToothBrushGame__GameStatusList__

#include <cocos2d.h>
#include <extensions/cocos-ext.h>
#include "common.h"
USING_NS_CC;
using namespace cocos2d::extension;

class GameStatusList :
public TableViewDataSource,
public TableViewDelegate
{
public:
    GameStatusList(){}
    ~GameStatusList(){}
    
    static GameStatusList* create(Layer* layer);
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
    static const int CELL_SIZE = 50;
    static const int ACHIEVE_TITLE_SIZE = CELL_SIZE / 3;
    static const int ACHIEVE_MESSAGE_SIZE = CELL_SIZE / 3;
    
};

#endif /* defined(__ToothBrushGame__GameStatusList__) */
