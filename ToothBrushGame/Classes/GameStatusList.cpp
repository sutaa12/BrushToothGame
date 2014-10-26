//
//  GameStatusList.cpp
//  ToothBrushGame
//
//  Created by 鈴木愛忠 on 2014/10/27.
//
//

#include "GameStatusList.h"
#include "AchievementDataBase.h"
// on "init" you need to initialize your instance
bool GameStatusList::init()
{
    m_window_size = Director::getInstance()->getVisibleSize() / 2 + SCREEN_CENTER;
    m_window_size.height -= 128;
    
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
    tableView->setPosition(Vec2(0,128));
    
    
    return true;
}
GameStatusList* GameStatusList::create(Layer* layer)
{
    GameStatusList* achievelist = new GameStatusList;
    achievelist->m_pLayer = layer;
    achievelist->init();
    return achievelist;
}

// セルの大きさを設定する
Size GameStatusList::cellSizeForTable(TableView *table){
    return Size(m_window_size.width, CELL_SIZE);
}

// 1セルに表示させるValueをセット
TableViewCell* GameStatusList::tableCellAtIndex(TableView *table, ssize_t idx)
{
    AchievementDataBaseList::getAchieveInfo((int)idx);
    std::string id = StringUtils::format("%zd", idx);
    std::string title = AchievementDataBaseList::getAchievementName((int)idx);

    std::string message = StringUtils::format("%d",AchievementDataBaseList::getAchieveInfo((int)idx));

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
    bg->setTextureRect(Rect(0, 0, m_window_size.width, CELL_SIZE));
    bg->setColor(background_color);
    bg->setTag(100);
    cell->addChild(bg);
    
    
    // ID部分
    auto *label_1 = LabelTTF::create(id.c_str(), "Arial", ACHIEVE_TITLE_SIZE);
    label_1->setAnchorPoint(Point(0, 0));
    label_1->setPosition(Point(20,label_1->getContentSize().height / 2));
    label_1->setColor(Color3B(0,0,0));
    cell->addChild(label_1);
    
    // タイトル部分
    auto *label_2 = LabelTTF::create(title.c_str(), "Arial", ACHIEVE_TITLE_SIZE);
    label_2->setAnchorPoint(Point(0, 0));
    label_2->setPosition(Point(50 + label_1->getContentSize().width, label_2->getContentSize().height / 2));
    label_2->setColor(Color3B(0,0,0));
    cell->addChild(label_2);
    
    // メッセージ部分
    auto *label_3 = LabelTTF::create(message.c_str(), "Arial", ACHIEVE_MESSAGE_SIZE);
    label_3->setAnchorPoint(Point(0, 0));
    label_3->setPosition(Point(80 + label_1->getContentSize().width + label_2->getContentSize().width,label_2->getContentSize().height / 2));
    label_3->setColor(Color3B(0,0,0));
    cell->addChild(label_3);
    return cell;
}

// セル数
ssize_t GameStatusList::numberOfCellsInTableView(TableView *table){
    return ACHIEVEMENT_MAX;
}

// セルがタッチされた時のcallback
void GameStatusList::tableCellTouched(TableView* table, TableViewCell* cell){
    CCLOG("%ziのセルがタッチされました", cell->getIdx());
}