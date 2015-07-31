//
//  BackGround.cpp
//  GetFish
//
//  Created by zhusu on 14/12/17.
//
//

#include "BackGround.h"
#include "Tools.h"

BackGround* BackGround::create(int type)
{
    BackGround* ref = new BackGround();
    
    if(ref && ref->init(type)) {
        ref->autorelease();
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return NULL;
}

BackGround::BackGround()
{
    
}

BackGround::~BackGround()
{

}

bool BackGround::init(int type)
{
    if(CCNode::init()) {
        
        _screenSize = CCDirector::sharedDirector()->getWinSize();
        
        _bg = CCSprite::create(("bg/bg_"+Tools::intToString(type)+".png").c_str());
    
        
        _bg->setAnchorPoint(ccp(0.5f, 0.5f));
        
        _bg->setPosition(ccp(_screenSize.width*0.5f, _screenSize.height*0.5f));
        
        addChild(_bg,-10);
        
        return  true;
    }
    
    return false;
}