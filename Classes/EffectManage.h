//
//  EffectManage.h
//  GetFish
//
//  Created by zhusu on 15/1/5.
//
//

#ifndef __GetFish__EffectManage__
#define __GetFish__EffectManage__

#include "cocos2d.h"

#include "ActorManage.h"

USING_NS_CC;

class EffectManage : public ActorManage
{
public:
    CREATE_FUNC(EffectManage);
    
    EffectManage();
    
    virtual bool init();
    
    virtual ~EffectManage();
    
    void addEffect(int type ,const char* name,  CCPoint pos,bool isMirror);
};

#endif /* defined(__GetFish__EffectManage__) */
