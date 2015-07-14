//
//  ActorManage.h
//  GetFish
//  Created by zs on 14-4-28.
//
//

#ifndef __GetFish__ActorManage__
#define __GetFish__ActorManage__

#include "cocos2d.h"

#include "Actor.h"

USING_NS_CC;


class ActorManage : public CCNode
{
public:
    
    CREATE_FUNC(ActorManage);
    
    ActorManage();
    
    virtual bool init();
    
    virtual ~ActorManage();
    
    void addActor(Actor* actor);
    
    void addActor(Actor* actor,int z);
    
    void addActorForChild(Actor* actor);
    
    void addActorForChild(Actor* actor,int z);
    
    CCArray* getActor() const;
    
    virtual void onEnter();
    
    virtual void onExit();

    virtual void cycle(float delta);
    
    void manageCycle(float delta);
    
    void setAutoDead(bool at);
    
    void removeActor(Actor* actor);
    
private:
    
    
    
protected:
    
    bool _isAutoDead;
    
    CCArray* _actorSet;
    CCBatchNode* _actorNode;
};

#endif /* defined(__Run__ActorManage__) */
