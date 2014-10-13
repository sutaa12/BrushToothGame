//********************************************************************************
//  HitCheck.cpp
//  test
//
//  Created by 丸山 潤 on 2014/10/08.
//
//********************************************************************************
//********************************************************************************
// インクルード
//********************************************************************************
#include "HitCheck.h"

//================================================================================
// 点と四角のあたり判定
//================================================================================
bool HitCheck::hitCheckPointAndBox(const Vec2& pointPos,const Vec2& boxPos,const Vec2& sizeHalf)
{
    if(pointPos.x >= boxPos.x - sizeHalf.x && pointPos.x <= boxPos.x + sizeHalf.x &&
       pointPos.y >= boxPos.y - sizeHalf.y && pointPos.y <= boxPos.y + sizeHalf.y)
    {
        return true;
    }
    return false;
}

//================================================================================
// 点と円のあたり判定
//================================================================================
bool HitCheck::hitCheckPointAndCircle(const Vec2& pointPos,const Vec2& circlePos,const float& radius)
{
    float workX = pointPos.x - circlePos.x;
    float workY = pointPos.y - circlePos.y;
    
    if(workX * workX + workY * workY <= radius * radius)
    {
        return true;
    }
    
    return false;
}

//================================================================================
// 円と円のあたり判定
//================================================================================
bool HitCheck::hitCheckCircleAndCircle(const Vec2& circlePos1,const float& radius1,const Vec2& circlePos2,const float& radius2)
{
    float workX = circlePos1.x - circlePos2.x;
    float workY = circlePos1.y - circlePos2.y;
    float workRad = radius1 + radius2;
    
    if(workX * workX + workY * workY <= workRad * workRad)
    {
        return true;
    }
    
    return false;
}
