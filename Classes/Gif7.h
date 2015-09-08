//
//  Gif7.h
//  GetFish
//
//  Created by zhusu on 15/8/25.
//
//

#ifndef __GetFish__Gif7__
#define __GetFish__Gif7__

#include "cocos2d.h"
#include "ButtonWithSpriteManage.h"

USING_NS_CC;

class Gif7 : public CCLayer
{
public:
    
    const static int TYPE_AUTO_DEAD = 0;
    const static int TYPE_NORMAL = 1;
    
    static Gif7* create(int type);
    
    virtual bool init(int type);
    
    Gif7();
    
    virtual ~Gif7();
    
    virtual void onExit();
    
    virtual void onEnter();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    
    
protected:
    
    ButtonWithSpriteManage* _buttons;
    
    int _type;

};


#endif /* defined(__GetFish__Gif7__) */
