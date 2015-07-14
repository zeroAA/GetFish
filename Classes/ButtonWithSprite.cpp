//
//  ButtonWithSpriteWithSprite.cpp
//  Zengine
//
//  Created by zhusu on 15/1/27.
//
//

#include "ButtonWithSprite.h"

ButtonWithSprite::ButtonWithSprite():_pressScale(0.8),_buttonScale(1),_add(CCSizeMake(0, 0))
{
    
}

ButtonWithSprite::~ButtonWithSprite()
{
    
}

ButtonWithSprite* ButtonWithSprite::create(int id,const char* name)
{
    return create(id,name,1);
}

ButtonWithSprite* ButtonWithSprite::create(int id,const char* name,float scale)
{
    ButtonWithSprite* pRet = new ButtonWithSprite();
    
    if(pRet && pRet->init(id,name,scale)) {
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
    
}

bool ButtonWithSprite::init(int id, const char *name,float scale)
{
    if(CCSprite::initWithSpriteFrameName(name)) {
        
        setID(id);
        
        setButtonScale(scale);
        this->setScale(_buttonScale);
        return true;
    }
    return false;
}

bool ButtonWithSprite::touchesBegan(CCSet * touchs,CCEvent * event)
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



bool ButtonWithSprite::touchesCancelled(CCSet * touchs,CCEvent * event)
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

bool ButtonWithSprite::touchesMoved(CCSet * touchs,CCEvent * event)
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

bool ButtonWithSprite::touchesEnded(CCSet * touchs,CCEvent * event)
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

bool ButtonWithSprite::toucheBegan(CCTouch *pTouch,CCEvent * event)
{
//    return toucheBeganAction(convertTouchToNodeSpaceAR(pTouch));
    return toucheBeganAction(pTouch->getLocation());
    
}

bool ButtonWithSprite::toucheCancelled(CCTouch *pTouch,CCEvent * event)
{
    return toucheCancelledAction(pTouch->getLocation());
}

bool ButtonWithSprite::toucheMoved(CCTouch *pTouch,CCEvent * event)
{
    return toucheMovedAction(pTouch->getLocation());
}

bool ButtonWithSprite::toucheEnded(CCTouch *pTouch,CCEvent * event)
{
    end();
    return toucheEndedAction(pTouch->getLocation());
}

bool ButtonWithSprite::toucheBeganAction(cocos2d::CCPoint pos)
{

    if (getBodyRect().containsPoint(pos)) {
        
    
        this->setScale(_pressScale);
        
        return true;
    }
    
    return false;
}

bool ButtonWithSprite::toucheCancelledAction(cocos2d::CCPoint pos)
{
    if (getBodyRect().containsPoint(pos)) {
        return  true;
    }
    
    return false;
}

bool ButtonWithSprite::toucheMovedAction(cocos2d::CCPoint pos)
{
    if (getBodyRect().containsPoint(pos)) {
        return  true;
    }
    
    return false;
    
}

bool ButtonWithSprite::toucheEndedAction(cocos2d::CCPoint pos)
{
    
    if (getBodyRect().containsPoint(pos)) {
        return  true;
    }
    
    return false;
}

void ButtonWithSprite::end()
{
    this->setScale(_buttonScale);
}

CCRect ButtonWithSprite::getBodyRect() 
{
    CCPoint pos = boundingBox().origin;
    
    if (getParent()) {
        
       pos  = getParent()->convertToWorldSpace(boundingBox().origin);
    }
    
    
    
    return CCRectMake(pos.x-_add.width*0.5, pos.y+_add.height*0.5, boundingBox().size.width+ _add.width, boundingBox().size.height+_add.height);
}

void ButtonWithSprite::draw()
{
    CCSprite::draw();
//    ccDrawColor4B(0xff, 0xff, 0x00, 0);
//    glLineWidth(1.0f);
//    CCRect rect1 = getBodyRect();
//    ccDrawRect(ccp(rect1.origin.x,rect1.origin.y), ccp(rect1.origin.x+rect1.size.width, rect1.origin.y+rect1.size.height));

}