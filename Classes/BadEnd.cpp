//
//  BadEnd.cpp
//  GetFish
//
//  Created by zhusu on 15/7/22.
//
//

#include "BadEnd.h"
#include "Common.h"
#include "Tools.h"

BadEnd::BadEnd():_dead(-1)
{
    
}

BadEnd::~BadEnd()
{
}

bool BadEnd::init()
{
    if(CCLayer::init()) {
        
        CCLayerColor* layerColor = CCLayerColor::create();
        layerColor->setColor(ccc3(0, 0, 0));
        layerColor->setOpacity(200);
        
        addChild(layerColor);
        
        CCSize _screenSize = CCDirector::sharedDirector()->getWinSize();
        
        CCSprite* di = CCSprite::create("ui/badend.png");
        di->setPosition(ccp(_screenSize.width*0.5, _screenSize.height*0.65));
        addChild(di);
        
        
        _numLabel = CCLabelAtlas::create("10", "ui/shuzi4.png", 21, 28, 43);
        _numLabel->setAnchorPoint(ccp(0.5, 0.5));
        _numLabel->setScale(1.5);
        _numLabel->setPosition(ccp(di->boundingBox().size.width*0.5+10, 52));
        di->addChild(_numLabel);
        
        CCSprite* zi = CCSprite::create("ui/badendzi.png");
        zi->setPosition(ccp(_screenSize.width*0.5, _screenSize.height*0.2));
        addChild(zi);
        this->setTouchEnabled(true);
        
        _buttons = ButtonWithSpriteManage::create("ui/button.png");
        
        addChild(_buttons);
        
        ButtonWithSprite* button_reset = ButtonWithSprite::create(BUTTON_END_RESET, "button_chongzhi.png");
        
        button_reset->setPosition(ccp(_screenSize.width*0.5, _screenSize.height*0.32));
        
        _buttons->addButton(button_reset);
        
        ButtonWithSprite* button_play = ButtonWithSprite::create(BUTTON_END_PLAY, "buttion_chongwan.png");
        
        button_play->setPosition(ccp(_screenSize.width*0.7, _screenSize.height*0.32));
        
        _buttons->addButton(button_play);
        
        ButtonWithSprite* button_back = ButtonWithSprite::create(BUTTON_END_BACK, "buttion_fanhuiguanka.png");
        
        button_back->setPosition(ccp(_screenSize.width*0.3, _screenSize.height*0.32));
        
        _buttons->addButton(button_back);
        
        _time = 10*FPS+2;
        
        return true;
    }
    
    return false;
}

void BadEnd::touchesBegan(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesBegan(touchs, event);
}


void BadEnd::touchesMoved(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesMoved(touchs, event);
}

void BadEnd::touchesEnded(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesEnded(touchs, event);
   
    if(_buttons->getNowID() == BUTTON_END_RESET){
        setDead(DEAD_TYPE_REST);
    
    }else if(_buttons->getNowID() == BUTTON_END_PLAY){
        setDead(DEAD_TYPE_PLAY);
    }else if(_buttons->getNowID() == BUTTON_END_BACK){
        setDead(DEAD_TYPE_BACK);
    }
}

void BadEnd::cycle(float dt)
{
    _time--;
    _numLabel->setString(Tools::intToString((int)(_time/FPS)).c_str());
    
    if (_time<=0) {
        setDead(DEAD_TYPE_BACK);
    }
}