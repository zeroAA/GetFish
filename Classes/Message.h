//
//  Message.h
//  GetFish
//
//  Created by zhusu on 15/7/30.
//
//

#ifndef __GetFish__Message__
#define __GetFish__Message__

#include "cocos2d.h"
#include "zSprite.h"

USING_NS_CC;


class Message : public zSprite
{
public:
    
    static const int TYPE_OVER_DEAD = 1;//播放完就消失
    
    static Message* create(int type ,const char* name);
    
    virtual bool init(int type ,const char* name);
    
    Message();
    
    virtual ~Message();
    
    virtual void cycle(float delta);
    
protected:
    
    int _type;
    
};

#endif /* defined(__GetFish__Message__) */
