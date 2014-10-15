//
//  Random.h
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/15.
//
//

#ifndef __ToothBrushGame__Random__
#define __ToothBrushGame__Random__

#include <random>
class RandomMT
{
public:
    RandomMT();
    ~RandomMT();
   static void initRand();
   static int getRaodom(int min, int max);
   static double getRandom(double min, double max);
private:
    static std::mt19937 m_mtRand;
};
#endif /* defined(__ToothBrushGame__Random__) */
