//
//  zSprite.cpp
//  GetFish
//
//  Created by zhusu on 15/7/30.
//
//

#include "zSprite.h"
#include "Common.h"
#include "GameScene.h"
#include "Tools.h"


zSprite* zSprite::createWithSpriteFrameName(const char *name)
{
    zSprite* pRet = new zSprite();
    
    if(pRet && pRet->init(name)) {
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
}

zSprite::zSprite():_state(STATE_NORMAL),_isAutoDead(true)
{
    
}

zSprite::~zSprite()
{
}
bool zSprite::init(const char *name)
{
    if(CCSprite::initWithSpriteFrameName(name)) {
        return true;
    }
    
    return false;
}

void zSprite::setState(int state)
{
    _state = state;
}

int zSprite::getState() const
{
    return _state;
}

void zSprite::cycle(float delta)
{

}

CCRect zSprite::getBodyRect()
{
    return this->boundingBox();
}

void zSprite::setAutoDead(bool isDead)
{
    _isAutoDead = isDead;
}