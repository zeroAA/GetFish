//
//  FishManage.h
//  GetFish
//
//  Created by zhusu on 14/12/14.
//
//

#ifndef __GetFish__FishManage__
#define __GetFish__FishManage__

#include "cocos2d.h"


#include "ActorManage.h"

USING_NS_CC;

class FishManage : public ActorManage
{
public:
    CREATE_FUNC(FishManage);
    
    FishManage();
    
    virtual bool init();
    
    virtual ~FishManage();
    
    void addFish(int type,float speed ,int dir, const char* name);
    
protected:
    
    CCSize _screenSize;
};

#endif /* defined(__GetFish__FishManage__) */
