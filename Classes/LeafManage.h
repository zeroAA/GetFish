//
//  LeafManage.h
//  GetFish
//
//  Created by zhusu on 15/3/11.
//
//

#ifndef __GetFish__LeafManage__
#define __GetFish__LeafManage__

#include "cocos2d.h"

#include "Leaf.h"

#include "ActorManage.h"

USING_NS_CC;

class LeafManage : public ActorManage
{
public:
    CREATE_FUNC(LeafManage);
    
    LeafManage();
    
    virtual bool init();
    
    virtual ~LeafManage();
    
    void addLeaf(const char* name,int dir,float speed,float y);
    
};

#endif /* defined(__GetFish__LeafManage__) */
