//
//  ButtonManage.h
//  Zengine
//
//  Created by zs on 14-6-16.
//
//

#ifndef __Zengine__ButtonManage__
#define __Zengine__ButtonManage__

#include "cocos2d.h"

#include "Button.h"

#include "ActorManage.h"

USING_NS_CC;

class ButtonManage : public ActorManage
{
public:
    CREATE_FUNC(ButtonManage);
    
    ButtonManage();
    
    virtual bool init();
    
    virtual ~ButtonManage();
    
    void addButton(int id ,const char* name , CCPoint pos);
    
    void addButton(int id ,const char* name, cocos2d::CCLabelBMFont *font,float fontScale , CCPoint pos);
    
    void addButton(Button* button);
    
    virtual bool touchesBegan(CCSet * touchs,CCEvent * event);
    
    virtual void touchesMoved(CCSet * touchs,CCEvent * event);
    
    virtual void touchesCancelled(CCSet * touchs,CCEvent * event);
    
    virtual void touchesEnded(CCSet * touchs,CCEvent * event);
    
    
    virtual bool toucheBegan(CCTouch *pTouch,CCEvent * event);
    
    virtual void toucheMoved(CCTouch *pTouch,CCEvent * event);
    
    virtual void toucheCancelled(CCTouch *pTouch,CCEvent * event);
    
    virtual void toucheEnded(CCTouch *pTouch,CCEvent * event);
    
    int getNowID();
    
private:
    
    int _nowIndext;
    
 
};


#endif /* defined(__Zengine__ButtonManage__) */
