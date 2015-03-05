//
//  ButtonWithSprite.h
//  Zengine
//
//  Created by zhusu on 15/1/27.
//
//

#ifndef __Zengine__ButtonWithSprite__
#define __Zengine__ButtonWithSprite__

#include "cocos2d.h"
USING_NS_CC;

class ButtonWithSprite : public CCSprite
{
public:
    
    static ButtonWithSprite* create(int id, const char* name,float scale);
    
    virtual bool init(int id, const char* name,float scale);
    
    static ButtonWithSprite* create(int id, const char* name);
    
    virtual void draw();
    
    ButtonWithSprite();
    
    virtual ~ButtonWithSprite();
    
    CC_SYNTHESIZE(int, _id, ID);
    
    CC_SYNTHESIZE(float, _pressScale, PressScale);
    
    CC_SYNTHESIZE(float, _buttonScale, ButtonScale);
    
    CC_SYNTHESIZE(CCSize, _add, Add);
    
    virtual bool touchesBegan(CCSet * touchs,CCEvent * event);
    
    virtual bool touchesMoved(CCSet * touchs,CCEvent * event);
    
    virtual bool touchesCancelled(CCSet * touchs,CCEvent * event);
    
    virtual bool touchesEnded(CCSet * touchs,CCEvent * event);
    
    virtual bool toucheBegan(CCTouch *pTouch,CCEvent * event);
    
    virtual bool toucheMoved(CCTouch *pTouch,CCEvent * event);
    
    virtual bool toucheCancelled(CCTouch *pTouch,CCEvent * event);
    
    virtual bool toucheEnded(CCTouch *pTouch,CCEvent * event);
    
    bool toucheBeganAction(CCPoint pos);
    
    bool toucheMovedAction(CCPoint pos);
    
    bool toucheCancelledAction(CCPoint pos);
    
    bool toucheEndedAction(CCPoint pos);
    
    void end();
    
    CCRect getBodyRect() ;
    
};

#endif /* defined(__Zengine__ButtonWithSprite__) */
