//
//  Rock.h
//  GetFish
//
//  Created by zhusu on 15/3/11.
//
//

#ifndef __GetFish__Rock__
#define __GetFish__Rock__

#include "cocos2d.h"

#include "Actor.h"

USING_NS_CC;

class Rock : public Actor
{
public:
    
    static Rock* create(const char* name,int hp);
    
    virtual bool init(const char* name,int hp);
    
    Rock();
    
    virtual ~Rock();
    
    void setNowAnim();
    
    void movementCallback(CCArmature * armature, MovementEventType type, const char * name);
    
    void subHp();
    
    int getHp() const;
    
private:
    
    int _hp;
    int _maxHp;
    
    
};

#endif /* defined(__GetFish__Rock__) */
