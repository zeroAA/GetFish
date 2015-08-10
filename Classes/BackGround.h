//
//  BackGround.h
//  GetFish
//
//  Created by zhusu on 14/12/17.
//
//

#ifndef __GetFish__BackGround__
#define __GetFish__BackGround__

#include "cocos2d.h"

USING_NS_CC;

class BackGround :public CCNode
{
    
public:
    
    
    static BackGround* create(int type);
    
    BackGround();
    
    virtual bool init(int type);
    
    virtual ~BackGround();
    
    
    
protected:
    
    CCSize _screenSize;
    
    CCSprite* _bg;
};

#endif /* defined(__GetFish__BackGround__) */
