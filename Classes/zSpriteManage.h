//
//  zSpriteManage.h
//  GetFish
//
//  Created by zhusu on 15/7/30.
//
//

#ifndef __GetFish__zSpriteManage__
#define __GetFish__zSpriteManage__

#include "cocos2d.h"

#include "zSprite.h"

USING_NS_CC;


class zSpriteManage : public CCNode
{
public:
    
    static zSpriteManage* create(const char *name);
    
    zSpriteManage();
    
    virtual bool init(const char *name);
    
    virtual ~zSpriteManage();
    
    void addSprite(zSprite* actor);
    
    void addSprite(zSprite* actor,int z);
    
    void addSpriteForChild(zSprite* actor);
    
    void addSpriteForChild(zSprite* actor,int z);
    
    CCArray* getSprite() const;
    
    void cycle(float delta);

    void setAutoDead(bool at);
    
    void removeSprite(zSprite* actor);
    
private:
    
    
    
protected:
    
    bool _isAutoDead;
    
    CCArray* _spriteSet;
    CCSpriteBatchNode* _spriteNode;
};

#endif /* defined(__GetFish__zSpriteManage__) */
