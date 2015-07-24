//
//  Pause.cpp
//  GetFish
//
//  Created by zhusu on 15/7/20.
//
//

#include "Pause.h"
#include "Common.h"

Pause::Pause():_dead(DEAD_TYPE_NODEAD)
{
    
}

Pause::~Pause()
{
}

bool Pause::init()
{
    if(CCLayer::init()) {
        
        CCSprite* back = CCSprite::createWithSpriteFrameName("ui_tishi_back.png");
        
        addChild(back);
        
        CCSprite* ming = CCSprite::createWithSpriteFrameName("ui_c_zanting.png");
        ming->setAnchorPoint(ccp(0, 1));
        ming->setPosition(ccp(-back->boundingBox().size.width*0.5+15, back->boundingBox().size.height*0.5-10));
        addChild(ming);
        
        _buttons = ButtonWithSpriteManage::create("ui/button.png");
        
        addChild(_buttons);
        
        
        ButtonWithSprite* _back = ButtonWithSprite::create(BUTTON_PAUSE_BACK, "button_fanhui2.png");
        _back->setPosition(ccp(-back->boundingBox().size.width*0.3, -120));
        
        _buttons->addButton(_back);
        
        
        ButtonWithSprite* _toGame = ButtonWithSprite::create(BUTTON_PAUSE_TOGAME, "button_jixu.png");
        _toGame->setPosition(ccp(back->boundingBox().size.width*0.3, -120));
        
        _buttons->addButton(_toGame);
        
        return true;
    }
    
    return false;
}


void Pause::touchesBegan(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesBegan(touchs, event);
}

void Pause::touchesCancelled(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesCancelled(touchs, event);
}

void Pause::touchesMoved(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesMoved(touchs, event);
}

void Pause::touchesEnded(CCSet * touchs,CCEvent * event)
{
    
    _buttons->touchesEnded(touchs, event);
    
    if (_buttons->getNowID() == BUTTON_PAUSE_BACK) {
        CCDirector::sharedDirector()->resume();
        setDead(DEAD_TYPE_BACK);
    }else if (_buttons->getNowID() == BUTTON_PAUSE_TOGAME) {
        CCDirector::sharedDirector()->resume();
        setDead(DEAD_TYPE_TOGAME);
    }
    
}