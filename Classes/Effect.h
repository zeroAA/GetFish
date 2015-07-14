//
//  Effect.h
//  GetFish
//
//  Created by zhusu on 15/1/5.
//
//

#ifndef __GetFish__Effect__
#define __GetFish__Effect__

#include "cocos2d.h"
#include "Actor.h"

USING_NS_CC;


class Effect : public Actor
{
public:
    
    static const int TYPE_OVER_DEAD = 1;//播放完就消失
    static const int TYPE_OVER_STATE = 2;//播放完置状态
    
    static const int STATE_BE_DEAD = 1;//完成状态
    
    static Effect* create(int type ,const char* name);
    
    virtual bool init(int type ,const char* name);
    
    Effect();
    
    virtual ~Effect();
    
    virtual void cycle(float delta);
    
protected:
    
    int _type;
    
    
    

};

#endif /* defined(__GetFish__Effect__) */
