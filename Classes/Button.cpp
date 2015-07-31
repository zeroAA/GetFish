//
//  Button.cpp
//  Zengine
//
//  Created by zs on 14-6-13.
//
//

#include "Button.h"
#include "GameScene.h"



        Button::Button():_font(NULL),_fontScale(1),_sprite(NULL)
{
    
}

Button::~Button()
{
    
}

Button* Button::create(int id,const char* name)
{
    Button* pRet = new Button();
    
    if(pRet && pRet->init(id,name)) {
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;

}

bool Button::init(int id, const char *name)
{
    if(Actor::init(name)) {
        setID(id);
        
        return true;
    }
    
    return false;
}

Button* Button::createWithFont(int id, const char *name, cocos2d::CCLabelBMFont *font,float fontScale)
{
    Button* pRet = new Button();
    
    if(pRet && pRet->initWithFont(id, name, font , fontScale)) {
        pRet->autorelease();
        return pRet;
    }
   
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool Button::initWithFont(int id, const char *name, cocos2d::CCLabelBMFont *font,float fontScale)
{
    if (Actor::init(name)) {
        
        setID(id);
        
        _font = font;
        _fontScale=fontScale;
        _font->setScale(_fontScale);

        addChild(_font,100);
        
        return true;
    }
    
    return false;
}

Button* Button::createWithSprite(int id, const char *name, CCSprite *sprite,float spriteScale,CCPoint pos)
{
    Button* pRet = new Button();
    
    if(pRet && pRet->initWithSprite(id, name, sprite , spriteScale,pos)) {
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool Button::initWithSprite(int id, const char *name, CCSprite *sprite,float spriteScale,CCPoint pos)
{
    if (Actor::init(name)) {
        
        setID(id);
        
        _sprite = sprite;
        _spriteScale = spriteScale;
        _sprite->setScale(_spriteScale);
        _sprite->setPosition(ccp(getBodyRect().size.width*pos.x, getBodyRect().size.height*pos.y));
        addChild(_sprite,100);
        
        return true;
    }
    
    return false;
}

//void Button::setAdd(float addX, float addY)
//{
//    
//    
//    _addX = addX;
//    _addY = addY;
//    
//    setBody();
//}
//
//void Button::setAdd(float add)
//{
//    setAdd(add, add);
//    
//}

bool Button::touchesBegan(CCSet * touchs,CCEvent * event)
{
    
    for(CCSetIterator iter=touchs->begin();iter!=touchs->end();iter++){
        
        CCTouch * mytouch=(CCTouch *)(* iter);
        
        CCPoint pos=mytouch->getLocation();
        
        if (toucheBeganAction(pos)) {
            
            return true;
        }
        
        
    }
    
    
    return false;
}



bool Button::touchesCancelled(CCSet * touchs,CCEvent * event)
{
    for(CCSetIterator iter=touchs->begin();iter!=touchs->end();iter++){
        
        CCTouch * mytouch=(CCTouch *)(* iter);
        
        CCPoint pos=mytouch->getLocation();
        
        
        if (toucheCancelledAction(pos)) {
            
            
            
            
            
            return true;
        }
        
        
    }
    
    
    return false;
}

bool Button::touchesMoved(CCSet * touchs,CCEvent * event)
{
    for(CCSetIterator iter=touchs->begin();iter!=touchs->end();iter++){
        
        CCTouch * mytouch=(CCTouch *)(* iter);
        
        CCPoint pos=mytouch->getLocation();
        
        
        if (toucheMovedAction(pos)) {
            
            
            
            
            
            return true;
        }
        
        
    }
    
    
    return false;
}

bool Button::touchesEnded(CCSet * touchs,CCEvent * event)
{
    end();
    for(CCSetIterator iter=touchs->begin();iter!=touchs->end();iter++){
        
        CCTouch * mytouch=(CCTouch *)(* iter);
        
        CCPoint pos=mytouch->getLocation();
        
        
        if (toucheEndedAction(pos)) {
                        
            return true;
        }
        
        
    }
    
    
    return false;
   
}

//void Button::setBody()
//{
//    _body = CCRectMake(this->boundingBox().origin.x-_addX, boundingBox().origin.y+_addY, boundingBox().size.width+_addX*2, boundingBox().size.height+_addY*2);
//    
//}

bool Button::toucheBegan(CCTouch *pTouch,CCEvent * event)
{
    
    
    
    return toucheBeganAction(pTouch->getLocation());
        
}

bool Button::toucheCancelled(CCTouch *pTouch,CCEvent * event)
{
    return toucheCancelledAction(pTouch->getLocation());
}

bool Button::toucheMoved(CCTouch *pTouch,CCEvent * event)
{
    return toucheMovedAction(pTouch->getLocation());
}

bool Button::toucheEnded(CCTouch *pTouch,CCEvent * event)
{
    end();
    return toucheEndedAction(pTouch->getLocation());
}

bool Button::toucheBeganAction(cocos2d::CCPoint pos)
{
    if (this->isVisible()) {
        if (getBodyRect().containsPoint(pos)) {
            this->getAnimation()->playByIndex(1);
            if (_font) {
                _font->setScale(_fontScale*0.8);
            }
            if (_sprite) {
                _sprite->setScale(_spriteScale*0.8);
            }
            
            return true;
        }
    }
    return false;
}

bool Button::toucheCancelledAction(cocos2d::CCPoint pos)
{
    if (getBodyRect().containsPoint(pos)) {
        return  true;
    }
    
    return false;
}

bool Button::toucheMovedAction(cocos2d::CCPoint pos)
{
    if (getBodyRect().containsPoint(pos)) {
        return  true;
    }
    
    return false;

}

bool Button::toucheEndedAction(cocos2d::CCPoint pos)
{
    
    if (getBodyRect().containsPoint(pos)) {
        return  true;
    }
    
    return false;

}

void Button::end()
{
    this->getAnimation()->playByIndex(0);
    if (_font) {
        _font->setScale(_fontScale);
    }
    if (_sprite) {
        _sprite->setScale(_spriteScale);
    }
}