//
//  Leaf.h
//  GetFish
//
//  Created by zhusu on 15/3/11.
//
//

#ifndef __GetFish__Leaf__
#define __GetFish__Leaf__

#include "cocos2d.h"

#include "Actor.h"

USING_NS_CC;

class Leaf : public Actor
{
public:
    
    const static int DIR_LEFT = 0;
    const static int DIR_RIGHT =1 ;

    
    static Leaf* create(const char* name,int hp,int dir,float speedx,float speedy);
    
    virtual bool init(const char* name,int hp,int dir,float speedx,float speedy);
    
    Leaf();
    
    virtual ~Leaf();
    
    virtual void cycle(float delta);
    
    void subHp();
    
    int getHp() const;
    
private:
    
    int _hp;
    int _maxHp;
    
    int _dir;
    
    float _speedx;
    float _speedy;
    
};


#endif /* defined(__GetFish__Leaf__) */
