//
//  ButtonManage.cpp
//  Zengine
//
//  Created by zs on 14-6-16.
//
//

#include "ButtonManage.h"

#include "GameScene.h"


ButtonManage::ButtonManage():_nowIndext(-1)
{
    
}

ButtonManage::~ButtonManage()
{
    
}

bool ButtonManage::init()
{
    if(ActorManage::init()) {
        
        
        
        return true;
    }
    
    return false;
}


void ButtonManage::addButton(int id ,const char *name, cocos2d::CCLabelBMFont *font,float fontScale, cocos2d::CCPoint pos)
{
    Button* button = Button::createWithFont(id, name,font,fontScale);
    
//    Button* button = Button::create(id, name);
    
    button->setPosition(pos);
    
    addButton(button);
}


void ButtonManage::addButton(int id ,const char *name, cocos2d::CCPoint pos)
{
    Button* button = Button::create(id, name);
    
    button->setPosition(pos);
    
    addButton(button);
}



void ButtonManage::addButton(Button *button)
{
    ActorManage::addActorForChild(button);
}

bool ButtonManage::touchesBegan(CCSet * touchs,CCEvent * event)
{
    
    CCArray* buttonSet = getActor();
    
    for (int i = 0; i<buttonSet->count(); ++i) {
        Button* button = (Button*) buttonSet->objectAtIndex(i);
        if(button->touchesBegan(touchs, event)){
            _nowIndext = i;
            return true;
        }
    }
    _nowIndext = -1;
    return false;
}



void ButtonManage::touchesCancelled(CCSet * touchs,CCEvent * event)
{
    if (_nowIndext>=0) {
        ((Button*) getActor()->objectAtIndex(_nowIndext))->touchesCancelled(touchs,event);
    }
}

void ButtonManage::touchesMoved(CCSet * touchs,CCEvent * event)
{
    if (_nowIndext>=0) {
        ((Button*) getActor()->objectAtIndex(_nowIndext))->touchesMoved(touchs,event);
    }
}

void ButtonManage::touchesEnded(CCSet * touchs,CCEvent * event)
{
    if (_nowIndext>=0) {
        if (!((Button*) getActor()->objectAtIndex(_nowIndext))->touchesEnded(touchs,event)) {
            _nowIndext=-1;
        }
        
    }
    
    
    
}

int ButtonManage::getNowID()
{
    if (_nowIndext <0) {
        return -1;
    }
    return ((Button*) getActor()->objectAtIndex(_nowIndext))->getID();
}

bool ButtonManage::toucheBegan(CCTouch *pTouch,CCEvent * event)
{
    
    CCArray* buttonSet = getActor();
    
    for (int i = 0; i<buttonSet->count(); ++i) {
        Button* button = (Button*) buttonSet->objectAtIndex(i);
        if(button->toucheBegan(pTouch, event)){
            _nowIndext = i;
            return true;
        }
    }
    
    _nowIndext = -1;
    return false;

    
//    return true;?
}

void ButtonManage::toucheCancelled(CCTouch *pTouch,CCEvent * event)
{
    if (_nowIndext>=0) {
        ((Button*) getActor()->objectAtIndex(_nowIndext))->toucheCancelled(pTouch,event);
    }
}

void ButtonManage::toucheMoved(CCTouch *pTouch,CCEvent * event)
{
    if (_nowIndext>=0) {
        ((Button*) getActor()->objectAtIndex(_nowIndext))->toucheMoved(pTouch, event);
    }
}

void ButtonManage::toucheEnded(CCTouch *pTouch,CCEvent * event)
{
    
    if (_nowIndext>=0) {
        if (!((Button*) getActor()->objectAtIndex(_nowIndext))->toucheEnded(pTouch, event)) {
            _nowIndext = -1;
        }
    }
}
