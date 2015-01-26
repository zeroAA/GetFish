//
//  FishManage.cpp
//  GetFish
//
//  Created by zhusu on 14/12/14.
//
//

#include "FishManage.h"
#include "Fish.h"

FishManage::FishManage()
{
    
}

FishManage::~FishManage()
{
    
}

bool FishManage::init()
{
    if(ActorManage::init()) {
        _screenSize = CCDirector::sharedDirector()->getWinSize();
        
        return true;
    }
    
    return false;
}


void FishManage::addFish(int type, float speed , int dir,const char* name)
{
    
    
    Fish* fish = Fish::create(type,speed , dir,name);

//    addActorForChild(fish);
    
    addActor(fish);
    
}