//
//  Rock.cpp
//  GetRock
//
//  Created by zhusu on 15/3/11.
//
//

#include "Rock.h"

Rock* Rock::create(const char* name,int hp)
{
    Rock* rock = new Rock();
    
    if(rock && rock->init(name,hp)) {
        rock->autorelease();
        return rock;
    }
    
    CC_SAFE_DELETE(rock);
    return NULL;
}



Rock::Rock():_hp(5),_maxHp(_hp)
{
    
}

Rock::~Rock()
{
    
}



bool Rock::init(const char* name,int hp)
{
    
    if(!Actor::init(name)) {
        
        return false;
    }
    
    _hp = _maxHp = hp;
    
    this->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Rock::movementCallback));
    
    return true;

}

void Rock::setNowAnim()
{
    int indext = (_maxHp-_hp)*5/_maxHp;
    
    playWithIndex(indext);
}

void Rock::movementCallback(CCArmature * armature, MovementEventType type, const char * name)
{
    if (type == COMPLETE)
    {
        if (strcmp(name,"Animation5") == 0)
        {
            
            setState(STATE_DEAD);
        }
    }
}

void Rock::subHp()
{
    if (_hp>0) {
        _hp--;
        if (_hp<0) {
            _hp = 0;
        }
        setNowAnim();
    }
    
}

int Rock::getHp() const
{
    return _hp;
}

