//
//  Button.h
//  Zengine
//
//  Created by zs on 14-6-13.
//
//

#ifndef __Zengine__Button__
#define __Zengine__Button__

#include "cocos2d.h"
#include "Actor.h"

USING_NS_CC;

class Button : public Actor
{
public:
    Button();
    
    static Button* create(int id, const char* name);
        
    virtual bool init(int id, const char* name);
    
    static Button* createWithFont(int id, const char* name,CCLabelBMFont *font,float fontScale);
    
    virtual bool initWithFont(int id, const char* name,CCLabelBMFont *font,float fontScale);
    
    static Button* createWithSprite(int id, const char* name,CCSprite *sprite,float spriteScale,CCPoint pos);
    
    virtual bool initWithSprite(int id, const char* name,CCSprite *sprite,float spriteScale,CCPoint pos);

    
    
    virtual ~Button();
    
//    void setAdd(float add);
//    
//    void setAdd(float addX , float addY);
    
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
    
//    void setBody();
    
    CC_SYNTHESIZE(int, _id, ID);
    
//    const static int STATE_
    
   
    
protected:
    
    CCLabelBMFont * _font;
    
    float _fontScale;
    
    CCSprite* _sprite;
    
    float _spriteScale;
    
//    float _addX;
//    
//    float _addY;
//    CCRect _body;
};

#endif /* defined(__Zengine__Button__) */
