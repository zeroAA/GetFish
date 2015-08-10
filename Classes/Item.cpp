//
//  Item.cpp
//  GetFish
//
//  Created by zhusu on 15/7/28.
//
//

#include "Item.h"
#include "Tools.h"
#include "GameScene.h"
#include "FlyNum.h"

Item* Item::create(const char* name,int type)
{
    Item* ref = new Item();
    
    if(ref && ref->init(name,type)) {
        ref->autorelease();
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return NULL;
}



Item::Item():_time(0)
{
    
}

Item::~Item()
{
    
}

bool Item::init(const char* name,int type)
{
    
    if(!Actor::init(name)) {
        return false;
    }

    _type = type;
    
    return true;
    
}

void Item::cycle(float delta)
{
    if (_state==STATE_FALL) {
        this->setPositionY(getPositionY()-10);
        if (getPositionY()<0) {
            setState(STATE_DEAD);
        }
    }else{
    _time--;
    if (_time<=0) {
        setState(STATE_DEAD);
    }
    }
}

void Item::setDead()
{
    setState(STATE_DEAD);
    
    if (_type == TYPE_ZHENZHU) {
        GameScene::instance()->setZhenZhu();
    }else if (_type == TYPE_JIFEN){
        
        if (GameScene::instance()->getShip()->getActor()->count()>1) {
            GameScene::instance()->addFlyNum(FlyNum::TYPE_NORMAL, getScore(), 0, getPosition(), ccp(CCDirector::sharedDirector()->getWinSize().width*0.75,CCDirector::sharedDirector()->getWinSize().height*0.95));
        }else{
            GameScene::instance()->addFlyNum(FlyNum::TYPE_NORMAL, getScore(), 0, getPosition(), ccp(CCDirector::sharedDirector()->getWinSize().width*0.75,CCDirector::sharedDirector()->getWinSize().height*0.9));
        }
        
    }else if(_type == TYPE_CITIE){
        GameScene::instance()->allFishToDead(0);
    }
}

void Item::setFall()
{
    setState(STATE_FALL);
}