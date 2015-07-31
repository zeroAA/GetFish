//
//  Message.cpp
//  GetFish
//
//  Created by zhusu on 15/7/30.
//
//

#include "Message.h"

Message* Message::create(int type,const char* name)
{
    Message* ref = new Message();
    
    if(ref && ref->init(type,name)) {
        ref->autorelease();
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return NULL;
}



Message::Message():_type(TYPE_OVER_DEAD)
{
    
}

Message::~Message()
{
}

bool Message::init(int type ,const char* name)
{
    
    
    if(zSprite::init(name)) {
        
        _type = type;
        
        return true;
    }
    return  false;
}

void Message::cycle(float delta)
{
    switch (_type) {
        case TYPE_OVER_DEAD:
            if (this->numberOfRunningActions() == 0) {
                setState(STATE_DEAD);
            }
            break;
        default:
            break;
    }
}
