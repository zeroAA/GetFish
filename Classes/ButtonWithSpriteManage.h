//
//  ButtonWithSpriteManage.h
//  Zengine
//
//  Created by zhusu on 15/1/27.
//
//

#ifndef __Zengine__ButtonWithSpriteManage__
#define __Zengine__ButtonWithSpriteManage__

#include "cocos2d.h"
#include "ButtonWithSprite.h"

USING_NS_CC;

class ButtonWithSpriteManage :public CCNode
{
public:
    static ButtonWithSpriteManage* create(const char* pngName);
    
    virtual bool init(const char* pngName);
    
    ButtonWithSpriteManage();
    
    virtual ~ButtonWithSpriteManage();
    
    void addButton(int id ,const char* name , CCPoint pos);
    
    void addButton(ButtonWithSprite* button);
    
    virtual bool touchesBegan(CCSet * touchs,CCEvent * event);
    
    virtual void touchesMoved(CCSet * touchs,CCEvent * event);
    
    virtual void touchesCancelled(CCSet * touchs,CCEvent * event);
    
    virtual void touchesEnded(CCSet * touchs,CCEvent * event);
    
    
    virtual bool toucheBegan(CCTouch *pTouch,CCEvent * event);
    
    virtual void toucheMoved(CCTouch *pTouch,CCEvent * event);
    
    virtual void toucheCancelled(CCTouch *pTouch,CCEvent * event);
    
    virtual void toucheEnded(CCTouch *pTouch,CCEvent * event);
    
    int getNowID();

    ButtonWithSprite* getButton(int indext);
protected:
    
    CCSpriteBatchNode* _batch;
    CCArray* _buttons;
    
    int _nowIndext;
    
};

#endif /* defined(__Zengine__ButtonWithSpriteManage__) */
