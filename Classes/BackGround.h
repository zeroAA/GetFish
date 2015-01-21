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
    CREATE_FUNC(BackGround);
    
    BackGround();
    
    virtual bool init();
    
    virtual ~BackGround();
    
protected:
    
    CCSize _screenSize;
    
    CCSprite* _bg;
};

#endif /* defined(__GetFish__BackGround__) */
