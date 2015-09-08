//
//  LeafManage.cpp
//  GetFish
//
//  Created by zhusu on 15/3/11.
//
//

#include "LeafManage.h"
LeafManage::LeafManage()
{
    
}

LeafManage::~LeafManage()
{
    
}

bool LeafManage::init()
{
    if(!ActorManage::init()) {
        return  false;
    }
    
    return true;
}

void LeafManage::addLeaf(const char *name, int dir , float speed,float y)
{
    Leaf* leaf = Leaf::create(name, 1000, dir, speed, 0);
    
    if (dir == Leaf::DIR_LEFT) {
        leaf->setPosition(ccp(0-leaf->getBodyRect().size.width*0.4, y));
    }else if (dir == Leaf::DIR_RIGHT){
        leaf->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width+leaf->getBodyRect().size.width*0.3, y));
    }
    
    
    
    addActor(leaf);
}


void LeafManage::addLeaf(const char *name, int dir , float speed,float x,float y)
{
    Leaf* leaf = Leaf::create(name, 1000, dir, speed, 0);
    
    
    leaf->setPosition(ccp(x, y));
    
    addActor(leaf);
}