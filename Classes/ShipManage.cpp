//
//  ShipManage.cpp
//  GetFish
//
//  Created by zhusu on 14/12/19.
//
//

#include "ShipManage.h"

#include "Ship.h"

ShipManage::ShipManage()
{
    
}

ShipManage::~ShipManage()
{
    
}

bool ShipManage::init()
{
    if(ActorManage::init()) {
        _screenSize = CCDirector::sharedDirector()->getWinSize();
        
        return true;
    }
    
    return false;
}


void ShipManage::addShip(int type, const char *name,int ID,int sex,int moveCD)
{
    
    
    Ship* ship = Ship::create(type,name);
    ship->playWithIndex(0);
    ship->setSex(sex);
    ship->setMoveCD(moveCD);
    ship->setID(ID);
    addActorForChild(ship);
    
}