//
//  ActorManage.cpp
//
//  Created by zs on 14-4-28.
//
//

#include "ActorManage.h"
#include "Actor.h"

ActorManage::ActorManage():_isAutoDead(true)
{
    
}

ActorManage::~ActorManage()
{
    if (_actorSet) {
        _actorSet->release();
        _actorSet=NULL;
    }
}

bool ActorManage::init()
{
    if(CCNode::init()) {
        
        _actorSet = CCArray::create();
        _actorSet->retain();
        
        _actorNode=CCBatchNode::create();
        addChild(_actorNode);
        
//        schedule(schedule_selector(ActorManage::manageCycle));
        
        
        return true;
    }
    
    return false;
}

void ActorManage::setAutoDead(bool at){
    if (!at) {
//        unschedule(schedule_selector(ActorManage::manageCycle));
    }
}

void ActorManage::addActor(Actor* actor)
{
    
    addActor(actor,0);
    
}

void ActorManage::addActor(Actor *actor, int z)
{
//    actor->setVisible(false);
    
//    CCLOG("???");
    _actorSet->addObject(actor);
    
    _actorNode->addChild(actor,z);
    actor->update(0);
//    actor->setBodyPonit();
}

void ActorManage::addActorForChild(Actor* actor)
{
    addActorForChild(actor, 0);
}

void ActorManage::addActorForChild(Actor* actor,int z)
{
//    actor->setVisible(false);
    _actorSet->addObject(actor);
    
    this->addChild(actor,z);
    //    _actorNode->addChild(actor);
    actor->update(0);
//    actor->setBodyPonit();
    
}

void ActorManage::cycle(float delta)
{
   
    
    
}

void ActorManage::manageCycle(float delta)
{
    
    for (int i =0; i<_actorSet->count(); ++i) {
        
        Actor* actor =(Actor*) (_actorSet->objectAtIndex(i));
        
            
            actor->cycle(delta);
            actor->actorCycle(delta);
            
            if (actor->getState() == Actor::STATE_DEAD) {
                
                removeActor(actor);
                i--;
                continue;
            }
        
        
    }
}

void ActorManage::removeActor(Actor *actor)
{
    _actorSet->removeObject(actor);
    _actorNode->removeChild(actor, true);
    this->removeChild(actor, true);
}

CCArray* ActorManage::getActor() const
{
    return _actorSet;
}

