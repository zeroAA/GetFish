//
//  MessageManage.h
//  GetFish
//
//  Created by zhusu on 15/7/30.
//
//

#ifndef __GetFish__MessageManage__
#define __GetFish__MessageManage__

#include "cocos2d.h"

#include "zSpriteManage.h"

USING_NS_CC;

class MessageManage : public zSpriteManage
{
public:
    static MessageManage* create(const char *name);
    
    MessageManage();
    
    virtual bool init(const char *name);
    
    virtual ~MessageManage();
    
    void addMessage(int type ,const char* name);
};

#endif /* defined(__GetFish__MessageManage__) */
