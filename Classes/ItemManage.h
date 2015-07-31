//
//  ItemManage.h
//  GetFish
//
//  Created by zhusu on 15/7/28.
//
//

#ifndef __GetFish__ItemManage__
#define __GetFish__ItemManage__

#include "cocos2d.h"

#include "Item.h"

#include "ActorManage.h"

USING_NS_CC;

class ItemManage : public ActorManage
{
public:
    CREATE_FUNC(ItemManage);
    
    ItemManage();
    
    virtual bool init();
    
    virtual ~ItemManage();
    
    void addItem(const char* name,CCPoint pos,int type,int v,int time);
    
};

#endif /* defined(__GetFish__ItemManage__) */
