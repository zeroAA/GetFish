//
//  Effect.cpp
//  GetFish
//
//  Created by zhusu on 15/1/5.
//
//

#include "Effect.h"

Effect* Effect::create(int type,const char* name)
{
    Effect* effect = new Effect();
    
    if(effect && effect->init(type,name)) {
        effect->autorelease();
        return effect;
    }
    
    CC_SAFE_DELETE(effect);
    return NULL;
}



Effect::Effect():_type(TYPE_OVER_DEAD)
{
    
}

Effect::~Effect()
{
}

bool Effect::init(int type ,const char* name)
{
    
    
    if(Actor::init(name)) {
        
        _type = type;
        
        schedule(schedule_selector(Effect::cycle));
        
        return true;
    }
    return  false;
}

void Effect::cycle(float delta)
{
    switch (_type) {
        case TYPE_OVER_DEAD:
            if (getAnimation()->getIsComplete()) {
                setState(STATE_DEAD);
            }
            break;
            case TYPE_OVER_STATE:
            if (this->numberOfRunningActions()==0) {
                setState(STATE_BE_DEAD);
            }
        default:
            break;
    }
}
