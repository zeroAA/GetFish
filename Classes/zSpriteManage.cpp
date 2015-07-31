//
//  zSpriteManage.cpp
//  GetFish
//
//  Created by zhusu on 15/7/30.
//
//

#include "zSpriteManage.h"

//
//  zSpriteManage.cpp
//
//  Created by zs on 14-4-28.
//
//

#include "zSpriteManage.h"
#include "Actor.h"


zSpriteManage* zSpriteManage::create(const char *name)
{
    zSpriteManage* pRet = new zSpriteManage();
    
    if(pRet && pRet->init(name)) {
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
}

zSpriteManage::zSpriteManage():_isAutoDead(true)
{
    
}

zSpriteManage::~zSpriteManage()
{
    if (_spriteSet) {
        _spriteSet->release();
        _spriteSet=NULL;
    }
}

bool zSpriteManage::init(const char *name)
{
    if(CCNode::init()) {
        
        _spriteSet = CCArray::create();
        _spriteSet->retain();
        
        _spriteNode=CCSpriteBatchNode::create(name);
        addChild(_spriteNode);
        
        return true;
    }
    
    return false;
}

void zSpriteManage::setAutoDead(bool at){
    if (!at) {
        //        unschedule(schedule_selector(zSpriteManage::manageCycle));
    }
}

void zSpriteManage::addSprite(zSprite* sprite)
{
    
    addSprite(sprite,0);
    
}

void zSpriteManage::addSprite(zSprite *sprite, int z)
{
    _spriteSet->addObject(sprite);
    _spriteNode->addChild(sprite,z);
}

void zSpriteManage::addSpriteForChild(zSprite* sprite)
{
    addSpriteForChild(sprite, 0);
}

void zSpriteManage::addSpriteForChild(zSprite* sprite,int z)
{
    _spriteSet->addObject(sprite);
    this->addChild(sprite,z);
}

void zSpriteManage::cycle(float delta)
{
    
    for (int i =0; i<_spriteSet->count(); ++i) {
        
        zSprite* sprite =(zSprite*) (_spriteSet->objectAtIndex(i));
        
        sprite->cycle(delta);
        
        if (sprite->getState() == zSprite::STATE_DEAD) {
            removeSprite(sprite);
            i--;
            continue;
        }
        
        
    }
}

void zSpriteManage::removeSprite(zSprite *sprite)
{
    _spriteSet->removeObject(sprite);
    _spriteNode->removeChild(sprite, true);
    this->removeChild(sprite, true);
}

CCArray* zSpriteManage::getSprite() const
{
    return _spriteSet;
}

