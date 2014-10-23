//
//  AchievementDataBase.cpp
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/23.
//
//

#include "AchievementDataBase.h"
#include "sqlite3.h"
/*
sqlite3* db = NULL;
std::string path = CCFileUtils::sharedFileUtils()->getWritablePath()+SQLITE; std::string data; int id = 1;
if ( sqlite3_open( path.c_str() ,&db) == SQLITE_OK )
{
    sqlite3_stmt* stmt = NULL;
    if (sqlite3_prepare_v2(db, "SELECT hoge FROM test WHERE id=?", -1, &stmt, NULL) == SQLITE_OK)
    {
        sqlite3_bind_int(stmt, 1, id );
        int ret = sqlite3_step(stmt); if ( ret ==SQLITE_DONE || ret == SQLITE_ROW )
        {
            data = (const char *) sqlite3_column_text(stmt, 0);
        }
        sqlite3_reset(stmt);
    }
    sqlite3_finalize(stmt);
}
sqlite3_close(db);
*/
void AchievementDataBaseList::init(void)
{
    // SQLITE3
    sqlite3 *pDB = NULL;
    char* errMsg = NULL;
    std::string sqlstr;
    int result;
    
    std::string dbPath = FileUtils::sharedFileUtils()->getWritablePath();
    dbPath.append("Test.db");
    result = sqlite3_open(dbPath.c_str(),&pDB);
    if (result != SQLITE_OK){
        CCLOG("OPENING WRONG, %d, MSG:%s",result,errMsg);
    }else{
        CCLOG("OK! %d, %s",result,errMsg);
    }
    
    // 読み書きファイルパスの表示
    CCLog("%s",dbPath.c_str());
    
    result=sqlite3_exec( pDB, "create table MyTable_1( ID integer primary key autoincrement, name nvarchar(32) ) " , NULL, NULL, &errMsg );
    if( result != SQLITE_OK )
        CCLOG( "失敗　:%d ，原因:%s\n" , result, errMsg );
    
    //insert
    sqlstr=" insert into MyTable_1( name ) values ( 'いちご' ) ";
    result = sqlite3_exec( pDB, sqlstr.c_str() , NULL, NULL, &errMsg );
    if(result != SQLITE_OK )
        CCLOG( "失敗　:%d ，原因:%s\n" , result, errMsg );
    
    //insert
    sqlstr=" insert into MyTable_1( name ) values ( 'ぶどう' ) ";
    result = sqlite3_exec( pDB, sqlstr.c_str() , NULL, NULL, &errMsg );
    if(result != SQLITE_OK )
        CCLOG( "失敗　:%d ，原因:%s\n" , result, errMsg );
    
    //insert
    sqlstr=" insert into MyTable_1( name ) values ( 'ばなな' ) ";
    result = sqlite3_exec( pDB, sqlstr.c_str() , NULL, NULL, &errMsg );
    if(result != SQLITE_OK )
        CCLOG( "失敗　:%d ，原因:%s\n" , result, errMsg );
    
    sqlite3_close(pDB);
}