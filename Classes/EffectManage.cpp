//
//  EffectManage.cpp
//  GetFish
//
//  Created by zhusu on 15/1/5.
//
//

#include "EffectManage.h"
#include "Effect.h"

EffectManage::EffectManage()
{
    
}

EffectManage::~EffectManage()
{
    
}

bool EffectManage::init()
{
    if(ActorManage::init()) {
        
        return true;
    }
    
    return false;
}



void EffectManage::addEffect(int type, const char *name,  CCPoint pos , bool isMirror)
{
    Effect* effect = Effect::create(type, name);
    effect->playWithIndex(0);
    effect->setPosition(pos);
    
    if (isMirror) {
        effect->setScaleX(-getScaleX());
    }
    
    addActor(effect);
}