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
    
    addFish(type,speed,dir,name,Fish::EXIT_DEAD_NORMAL,CCPointMake(-1000, 0));
   
    
}

void FishManage::addFish(int type,float speed ,int dir, const char* name,int exitType,CCPoint pos)
{
    Fish* fish = Fish::create(type,speed , dir,name);
    fish->setExitDeadType(exitType);
    //    addActorForChild(fish);
    
    if (pos.x !=-1000) {
        
        fish->setXY(pos.x, pos.y);
    }
    
    addActor(fish);
}