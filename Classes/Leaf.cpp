//
//  Leaf.cpp
//  GetFish
//
//  Created by zhusu on 15/3/11.
//
//

#include "Leaf.h"


Leaf* Leaf::create(const char* name,int hp,int dir,float speedx,float speedy)
{
    Leaf* leaf = new Leaf();
    
    if(leaf && leaf->init(name,hp, dir, speedx, speedy)) {
        leaf->autorelease();
        return leaf;
    }
    
    CC_SAFE_DELETE(leaf);
    return NULL;
}



Leaf::Leaf():_hp(100),_maxHp(_hp),_dir(DIR_LEFT),_speedx(3),_speedy(0)
{
    
}

Leaf::~Leaf()
{
    
}



bool Leaf::init(const char* name,int hp,int dir,float speedx,float speedy)
{
    
    if(!Actor::init(name)) {
        
        return false;
    }
    
    _hp = _maxHp = hp;
    _dir = dir;
    _speedx = speedx;
    _speedy = speedy;
    
    return true;
    
}



void Leaf::subHp()
{
    if (_hp>0) {
        _hp--;
        if (_hp<=0) {
            setState(STATE_DEAD);
        }else{
            CCMoveBy* mb = CCMoveBy::create(0.3, ccp(0, -10));
            CCMoveBy* mb2 = CCMoveBy::create(0.2, ccp(0, 10));
            
            CCSequence* seq = CCSequence::create(mb,mb2,NULL);
            
            this->runAction(seq);
        }
       
    }
    
}

int Leaf::getHp() const
{
    return _hp;
}

void Leaf::cycle(float delta)
{
    if (DIR_LEFT == _dir) {
        setPosition(ccp(this->getPositionX()+_speedx, this->getPositionY()));
    }else if(_dir == DIR_RIGHT){
        setPosition(ccp(this->getPositionX()-_speedx, this->getPositionY()));
    }
    
    if (getRotationX()<-getBodyRect().size.width*0.5||getRotationX()>CCDirector::sharedDirector()->getWinSize().width+getBodyRect().size.width*0.5) {
        setState(STATE_DEAD);
    }
}
