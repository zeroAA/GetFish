//
//  MapUI.h
//  GetFish
//
//  Created by zhusu on 15/2/3.
//
//

#ifndef __GetFish__MapUI__
#define __GetFish__MapUI__

#include "cocos2d.h"
#include "MapElement.h"

USING_NS_CC;

class MapUI : public CCLayer
{
public:
    
    static MapUI* create(int lev);
    
    virtual bool init(int lev);
    
    MapUI();
    
    virtual ~MapUI();
    
    virtual void onExit();
    
    virtual void onEnter();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
protected:
    
    CCArray* _mapE;

    CCSize _screenSize;
};

#endif /* defined(__GetFish__MapUI__) */
