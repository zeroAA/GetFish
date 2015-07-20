//
//  Set.cpp
//  GetFish
//
//  Created by zhusu on 15/5/6.
//
//

#include "Set.h"
#include "Common.h"
#include "MapScene.h"

Set::Set()
{
    
}

Set::~Set()
{
}

bool Set::init()
{
    if(CCLayer::init()) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/ui_set.plist");
        
        CCSprite* back = CCSprite::createWithSpriteFrameName("ui_tishi_back.png");
        
        addChild(back);
        
        CCSprite* shezi = CCSprite::createWithSpriteFrameName("ui_set_shezhi.png");
        shezi->setAnchorPoint(ccp(0, 1));
        shezi->setPosition(ccp(-back->boundingBox().size.width*0.5+20, back->boundingBox().size.height*0.5-10));
        addChild(shezi);
        
        CCSprite* yinxiao = CCSprite::createWithSpriteFrameName("ui_set_yinxiao.png");
        yinxiao->setAnchorPoint(ccp(0, 0.5));
        yinxiao->setPosition(ccp(-back->boundingBox().size.width*0.5+15, 40));
        addChild(yinxiao);
        
        CCSprite* yinyu = CCSprite::createWithSpriteFrameName("ui_set_yinyue.png");
        yinyu->setAnchorPoint(ccp(0, 0.5));
        yinyu->setPosition(ccp(-back->boundingBox().size.width*0.5+15, -50));
        addChild(yinyu);
        
        if (IS_ON_MUISC) {
            yinxiaoon = CCSprite::createWithSpriteFrameName("ui_set_on.png");
        }else{
            yinxiaoon = CCSprite::createWithSpriteFrameName("ui_set_off.png");
        }
        
        yinxiaoon->setAnchorPoint(ccp(0, 0.5));
        yinxiaoon->setPosition(ccp(-back->boundingBox().size.width*0.5+105, 40));
        addChild(yinxiaoon);
        
        if (IS_ON_SFX) {
            yinyuon = CCSprite::createWithSpriteFrameName("ui_set_on.png");
        }else{
            yinyuon = CCSprite::createWithSpriteFrameName("ui_set_off.png");
        }
        
        yinyuon->setAnchorPoint(ccp(0, 0.5));
        yinyuon->setPosition(ccp(-back->boundingBox().size.width*0.5+105, -50));
        addChild(yinyuon);
        
        CCSprite* xian = CCSprite::createWithSpriteFrameName("ui_set_xian.png");
        
        addChild(xian);
        
        if (IS_ON_BUTTON) {
            anniuon = CCSprite::createWithSpriteFrameName("ui_set_xianliang.png");
        }else{
            anniuon = CCSprite::createWithSpriteFrameName("ui_set_xianhui.png");
            
        }
        anniuon->setAnchorPoint(ccp(0, 1));
        anniuon->setPosition(ccp(back->boundingBox().size.width*0.09, 65));
        addChild(anniuon);
        
        if (IS_ON_BUTTON) {
            anniuoff = CCSprite::createWithSpriteFrameName("ui_set_yinhui.png");
        }else{
            anniuoff = CCSprite::createWithSpriteFrameName("ui_set_yinliang.png");
        }
        anniuoff->setAnchorPoint(ccp(0, 1));
        anniuoff->setPosition(ccp(back->boundingBox().size.width*0.09, -25));
        addChild(anniuoff);
        
        this->setTouchEnabled(true);
        
        return true;
    }
    
    return false;
}

void Set::onEnter()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, KEY_SET, true);
    
    CCLayer::onEnter();
}

void Set::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CCLayer::onExit();
}

bool Set::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint pos = pTouch->getLocation();
    
//    if (CCRectMake(_screenSize.width*0.1, _screenSize.height*0.2, _screenSize.width*0.8, _screenSize.height*0.6).containsPoint(pos)) {
//        
//        _nowSelect= 1000;
//        return true;
//    }
    
    if(CCRectMake(yinxiaoon->boundingBox().origin.x+this->getPositionX(), yinxiaoon->boundingBox().origin.y+this->getPositionY(), yinxiaoon->boundingBox().size.width, yinxiaoon->boundingBox().size.height).containsPoint(pos)){
        if (IS_ON_MUISC) {
            CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ui_set_off.png");
            
            yinxiaoon->setDisplayFrame(frame);
            IS_ON_MUISC = false;
        }else{
            CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ui_set_on.png");
            yinxiaoon->setDisplayFrame(frame);
            IS_ON_MUISC = true;
        }
       
        return true;
    }
    
    
    if(CCRectMake(yinyuon->boundingBox().origin.x+this->getPositionX(), yinyuon->boundingBox().origin.y+this->getPositionY(), yinyuon->boundingBox().size.width, yinyuon->boundingBox().size.height).containsPoint(pos)){
        if (IS_ON_SFX) {
            CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ui_set_off.png");
            
            yinyuon->setDisplayFrame(frame);
            IS_ON_SFX = false;
        }else{
            CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ui_set_on.png");
            yinyuon->setDisplayFrame(frame);
            IS_ON_SFX = true;
        }
       
        return true;
    }
    
    
    if(CCRectMake(anniuon->boundingBox().origin.x+this->getPositionX(), anniuon->boundingBox().origin.y+this->getPositionY(), anniuon->boundingBox().size.width, anniuon->boundingBox().size.height).containsPoint(pos)){
        if (!IS_ON_BUTTON) {
            
            CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ui_set_xianliang.png");
            
            anniuon->setDisplayFrame(frame);
           
            CCSpriteFrame* frame1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ui_set_yinhui.png");
            
            anniuoff->setDisplayFrame(frame1);
            
            IS_ON_BUTTON = true;
            
        }
        
        return true;
    }
    
    if(CCRectMake(anniuoff->boundingBox().origin.x+this->getPositionX(), anniuoff->boundingBox().origin.y+this->getPositionY(), anniuoff->boundingBox().size.width, anniuoff->boundingBox().size.height).containsPoint(pos)){
        
        if (IS_ON_BUTTON) {
            
            CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ui_set_xianhui.png");
            
            anniuon->setDisplayFrame(frame);
            
            CCSpriteFrame* frame1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ui_set_yinliang.png");
            
            anniuoff->setDisplayFrame(frame1);
            
            IS_ON_BUTTON = false;
            
        }
        return true;
    }
    
    
    return false;
}

void Set::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    
}

void Set::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
   
    
}