//
//  AchievementList.cpp
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/23.
//
//

#include "AchievementList.h"
// on "init" you need to initialize your instance
bool AchievementList::init()
{
    m_window_size = Director::getInstance()->getVisibleSize() / 2 + SCREEN_CENTER;

    //画面サイズサイズを取得
    TableView* tableView = TableView::create(this, m_window_size);
    //展開方向
    tableView->setDirection(TableView::Direction::VERTICAL);
    //表示順序上からしたへ
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    
    //追加
    tableView->setDelegate(this);
    m_pLayer->addChild(tableView);
    tableView->reloadData();
    
    return true;
}
AchievementList* AchievementList::create(Layer* layer)
{
    AchievementList* achievelist = new AchievementList;
    achievelist->m_pLayer = layer;
    achievelist->init();
    return achievelist;
}

// セルの大きさを設定する
Size AchievementList::cellSizeForTable(TableView *table){
    return Size(m_window_size.width, 25);
}

// 1セルに表示させるValueをセット
TableViewCell* AchievementList::tableCellAtIndex(TableView *table, ssize_t idx)
{
    std::string id = StringUtils::format("%zd", idx);
    std::string text = StringUtils::format("Line %zd", idx);
    TableViewCell *cell = table->dequeueCell();
    
    cell = new TableViewCell();
    cell->autorelease();
    // セルの背景は交互に色を変更する
    auto background_color = Color3B(255,255,255);
    if (idx%2) {
        background_color = Color3B(200,200,200);
    }
    
    Sprite* bg = Sprite::create();
    bg->setAnchorPoint(Point(0, 0));
    bg->setTextureRect(Rect(0, 0, m_window_size.width, 24));
    bg->setColor(background_color);
    bg->setTag(100);
    cell->addChild(bg);
    
    // ボーダーライン
    Sprite* line = Sprite::create();
    line->setAnchorPoint(Point(0, 0));
    line->setTextureRect(Rect(0, 0, m_window_size.width, 1));
    line->setColor(Color3B(0,0,0));
    cell->addChild(line);
    
    // ID部分
    auto *label_1 = LabelTTF::create(id.c_str(), "Arial", 20);
    label_1->setAnchorPoint(Point(0, 0));
    label_1->setPosition(Point(50, 0));
    label_1->setColor(Color3B(0,0,0));
    cell->addChild(label_1);
    
    // テキスト部分
    auto *label_2 = LabelTTF::create(text.c_str(), "Arial", 20);
    label_2->setAnchorPoint(Point(0, 0));
    label_2->setPosition(Point(100, 0));
    label_2->setColor(Color3B(0,0,0));
    cell->addChild(label_2);
    
    return cell;
}

// セル数
ssize_t AchievementList::numberOfCellsInTableView(TableView *table){
    return 40;
}

// セルがタッチされた時のcallback
void AchievementList::tableCellTouched(TableView* table, TableViewCell* cell){
    CCLOG("%ziのセルがタッチされました", cell->getIdx());
}