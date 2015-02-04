//
//  BackGround.cpp
//  GetFish
//
//  Created by zhusu on 14/12/17.
//
//

#include "BackGround.h"

BackGround::BackGround()
{
    
}

BackGround::~BackGround()
{

}

bool BackGround::init()
{
    if(CCNode::init()) {
        
        _screenSize = CCDirector::sharedDirector()->getWinSize();
        
        _bg = CCSprite::create("bg/bg_3.png");
    
        
        _bg->setAnchorPoint(ccp(0.5f, 0.5f));
        
        _bg->setPosition(ccp(_screenSize.width*0.5f, _screenSize.height*0.5f));
        
        addChild(_bg,-10);
        
        return  true;
    }
    
    return false;
}