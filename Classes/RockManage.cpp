//
//  RockManage.cpp
//  GetFish
//
//  Created by zhusu on 15/3/11.
//
//

#include "RockManage.h"

RockManage::RockManage()
{
    
}

RockManage::~RockManage()
{
    
}

bool RockManage::init()
{
    if(!ActorManage::init()) {
        return  false;
    }
    
    return true;
}

void RockManage::addRock(const char *name, int hp , CCPoint pos)
{
    Rock* rock = Rock::create(name, hp);
    
    rock->setPosition(pos);
    
    addActor(rock);
}
