//
//  ShellManage.h
//  GetFish
//
//  Created by zhusu on 15/3/11.
//
//

#ifndef __GetFish__ShellManage__
#define __GetFish__ShellManage__

#include "cocos2d.h"

#include "Leaf.h"

#include "ActorManage.h"

USING_NS_CC;

class ShellManage : public ActorManage
{
public:
    CREATE_FUNC(ShellManage);
    
    ShellManage();
    
    virtual bool init();
    
    virtual ~ShellManage();
    
    void addShell(const char* name,CCPoint pos,std::vector<int> item,int openTime,int closeTime);
    
};


#endif /* defined(__GetFish__ShellManage__) */
