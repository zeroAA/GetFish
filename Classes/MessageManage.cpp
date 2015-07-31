//
//  MessageManage.cpp
//  GetFish
//
//  Created by zhusu on 15/7/30.
//
//

#include "MessageManage.h"
#include "Message.h"

MessageManage* MessageManage::create(const char *name)
{
    MessageManage* pRet = new MessageManage();
    
    if(pRet && pRet->init(name)) {
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
}


MessageManage::MessageManage()
{
    
}

MessageManage::~MessageManage()
{
    
}

bool MessageManage::init(const char *name)
{
    if(zSpriteManage::init(name)) {
        
        return true;
    }
    
    return false;
}



void MessageManage::addMessage(int type, const char *name)
{
    Message* mg = Message::create(type, name);
    
    CCDelayTime* dt = CCDelayTime::create(0.5);
    
    CCMoveBy* mb = CCMoveBy::create(0.5, ccp(0, 100));
    
    CCFadeOut* out = CCFadeOut::create(0.5);
    
    CCSpawn* sp = CCSpawn::create(mb,out,NULL);
    
    mg->runAction(CCSequence::create(dt,sp,NULL));
    
    mg->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, CCDirector::sharedDirector()->getWinSize().height*0.5));
    
    addSprite(mg);
}