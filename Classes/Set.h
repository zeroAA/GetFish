//
//  Set.h
//  GetFish
//
//  Created by zhusu on 15/5/6.
//
//

#ifndef __GetFish__Set__
#define __GetFish__Set__

#include "cocos2d.h"

USING_NS_CC;

class Set : public CCLayer
{
public:
    CREATE_FUNC(Set);
    
    virtual bool init();
    
    Set();
    
    virtual ~Set();
    
    virtual void onExit();
    
    virtual void onEnter();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
protected:
    
    
    CCSprite* yinxiaoon;
    
    CCSprite* yinyuon;
    
    CCSprite* anniuon;
    
    CCSprite* anniuoff;

};


#endif /* defined(__GetFish__Set__) */
