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
#include "ButtonWithSpriteManage.h"

USING_NS_CC;

class Set : public CCLayer
{
public:
    CREATE_FUNC(Set);
    
    virtual bool init();
    
    Set();
    
    virtual ~Set();

};


#endif /* defined(__GetFish__Set__) */
