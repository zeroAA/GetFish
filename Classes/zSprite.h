//
//  zSprite.h
//  GetFish
//
//  Created by zhusu on 15/7/30.
//
//

#ifndef __GetFish__zSprite__
#define __GetFish__zSprite__

#include "cocos2d.h"


USING_NS_CC;


class zSprite : public CCSprite
{
public:
    
    const static int STATE_NORMAL = 100;
    
    const static int STATE_DEAD = 101;
    
    static zSprite* createWithSpriteFrameName(const char *name);
    
    virtual bool init(const char *name);
    
    zSprite();
    
    virtual ~zSprite();
    
    void setState(int state);
    
    int getState() const;
    
    virtual void cycle(float delta);
    
    virtual CCRect getBodyRect() ;
    
    void setAutoDead(bool isDead);
    
private:
    
    
    
protected:
    
    bool _isAutoDead;
    
    int _state;
    
    int _proState;
    
};

#endif /* defined(__GetFish__zSprite__) */
