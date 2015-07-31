//
//  ItemManage.cpp
//  GetFish
//
//  Created by zhusu on 15/7/28.
//
//

#include "ItemManage.h"

ItemManage::ItemManage()
{
    
}

ItemManage::~ItemManage()
{
    
}

bool ItemManage::init()
{
    if(!ActorManage::init()) {
        return  false;
    }
    
    return true;
}

void ItemManage::addItem(const char* name,CCPoint pos,int type,int v,int time)
{
    Item* item = Item::create(name, type);
    item->setPosition(pos);
    item->setScore(v);
    item->setTime(time);
    item->playWithIndex(0);
    addActor(item);
}