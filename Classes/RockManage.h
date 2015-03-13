//
//  RockManage.h
//  GetFish
//
//  Created by zhusu on 15/3/11.
//
//

#ifndef __GetFish__RockManage__
#define __GetFish__RockManage__

#include "cocos2d.h"

#include "Rock.h"

#include "ActorManage.h"

USING_NS_CC;

class RockManage : public ActorManage
{
public:
    CREATE_FUNC(RockManage);
    
    RockManage();
    
    virtual bool init();
    
    virtual ~RockManage();
    
    void addRock(const char* name,int hp,CCPoint pos);

};

#endif /* defined(__GetFish__RockManage__) */
