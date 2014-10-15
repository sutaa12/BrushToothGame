//
//  Random.cpp
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/15.
//
//

#include "Random.h"
#include <random>
std::mt19937 RandomMT::m_mtRand;

void RandomMT::initRand(){
    std::random_device rndDev;
    m_mtRand = std::mt19937(rndDev());
}

int RandomMT::getRaodom(int min, int max){
    std::uniform_int_distribution<int> dist(min, max);
    return dist(m_mtRand);
}

double RandomMT::getRandom(double min, double max){
    std::uniform_real_distribution<double> dist(min, max);
    return dist(m_mtRand);
}