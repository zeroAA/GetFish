//
//  Item.h
//  GetFish
//
//  Created by zhusu on 15/7/28.
//
//

#ifndef __GetFish__Item__
#define __GetFish__Item__

#include "cocos2d.h"
#include "Actor.h"
USING_NS_CC;

class Item : public Actor
{
public:
    
    static const int STATE_HOOK = 1;
    
    static const int TYPE_JIFEN = 1;
    static const int TYPE_ZHENZHU = 2;
    static const int TYPE_CITIE = 3;
    
    static Item* create(const char* name,int type);
    
    virtual bool init(const char* name,int type);
    
    Item();
    
    virtual ~Item();
    
    virtual void cycle(float delta);
    
    CC_SYNTHESIZE(int, _score, Score);
    
    CC_SYNTHESIZE(int, _time, Time);
    
    void setDead();
    
private:
    
    
protected:
    int _type;
  
    
};

#endif /* defined(__GetFish__Item__) */
