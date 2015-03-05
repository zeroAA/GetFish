//
//  ButtonWithSpriteManage.cpp
//  Zengine
//
//  Created by zhusu on 15/1/27.
//
//

#include "ButtonWithSpriteManage.h"

ButtonWithSpriteManage::ButtonWithSpriteManage():_nowIndext(-1)
{
    
}

ButtonWithSpriteManage::~ButtonWithSpriteManage()
{
    if (_buttons) {
        _buttons->release();
        _buttons=NULL;
    }
}

ButtonWithSpriteManage* ButtonWithSpriteManage::create(const char* name)
{
    ButtonWithSpriteManage* pRet = new ButtonWithSpriteManage();
    
    if(pRet && pRet->init(name)) {
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
    
}


bool ButtonWithSpriteManage::init(const char* pngName)
{
    if(CCNode::init()) {
        
        _buttons = CCArray::create();
        _buttons->retain();
        
        _batch = CCSpriteBatchNode::create(pngName);
        
        addChild(_batch);
        
        return true;
    }
    return false;
}

void ButtonWithSpriteManage::addButton(int id , const char* name, CCPoint pos)
{
    ButtonWithSprite* button = ButtonWithSprite::create(id, name);
    
    button->setPosition(pos);
    
    addButton(button);
}

void ButtonWithSpriteManage::addButton(ButtonWithSprite *button)
{
    _buttons->addObject(button);
    _batch->addChild(button);
}

bool ButtonWithSpriteManage::touchesBegan(CCSet * touchs,CCEvent * event)
{
    
    for (int i = 0; i<_buttons->count(); ++i) {
        ButtonWithSprite* button = (ButtonWithSprite*) _buttons->objectAtIndex(i);
        if(button->touchesBegan(touchs, event)){
            _nowIndext = i;
            return true;
        }
    }
    _nowIndext = -1;
    return false;
}



void ButtonWithSpriteManage::touchesCancelled(CCSet * touchs,CCEvent * event)
{
    if (_nowIndext>=0) {
        ((ButtonWithSprite*) _buttons->objectAtIndex(_nowIndext))->touchesCancelled(touchs,event);
    }
}

void ButtonWithSpriteManage::touchesMoved(CCSet * touchs,CCEvent * event)
{
    if (_nowIndext>=0) {
        ((ButtonWithSprite*) _buttons->objectAtIndex(_nowIndext))->touchesMoved(touchs,event);
    }
}

void ButtonWithSpriteManage::touchesEnded(CCSet * touchs,CCEvent * event)
{
    if (_nowIndext>=0) {
        if (!((ButtonWithSprite*) _buttons->objectAtIndex(_nowIndext))->touchesEnded(touchs,event)) {
            _nowIndext=-1;
        }
        
    }
}

int ButtonWithSpriteManage::getNowID()
{
    if (_nowIndext <0) {
        return -1;
    }
    return ((ButtonWithSprite*) _buttons->objectAtIndex(_nowIndext))->getID();
}

bool ButtonWithSpriteManage::toucheBegan(CCTouch *pTouch,CCEvent * event)
{
    
    for (int i = 0; i<_buttons->count(); ++i) {
        ButtonWithSprite* button = (ButtonWithSprite*) _buttons->objectAtIndex(i);
        if(button->toucheBegan(pTouch, event)){
            _nowIndext = i;
            return true;
        }
    }
    _nowIndext = -1;
    return false;
    
    
//    return true;?
}

void ButtonWithSpriteManage::toucheCancelled(CCTouch *pTouch,CCEvent * event)
{
    if (_nowIndext>=0) {
        ((ButtonWithSprite*) _buttons->objectAtIndex(_nowIndext))->toucheCancelled(pTouch,event);
    }
}

void ButtonWithSpriteManage::toucheMoved(CCTouch *pTouch,CCEvent * event)
{
    if (_nowIndext>=0) {
        ((ButtonWithSprite*) _buttons->objectAtIndex(_nowIndext))->toucheMoved(pTouch, event);
    }
}

void ButtonWithSpriteManage::toucheEnded(CCTouch *pTouch,CCEvent * event)
{
    
    if (_nowIndext>=0) {
        if (!((ButtonWithSprite*) _buttons->objectAtIndex(_nowIndext))->toucheEnded(pTouch, event)) {
            _nowIndext = -1;
        }
    }
}
