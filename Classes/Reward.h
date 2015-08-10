//
//  Reward.h
//  GetFish
//
//  Created by zhusu on 15/8/3.
//
//

#ifndef __GetFish__Reward__
#define __GetFish__Reward__

#include "cocos2d.h"
#include "ButtonWithSpriteManage.h"

USING_NS_CC;

class Reward : public CCLayer
{
public:

    static Reward* create(bool can ,int gold,int get);
    
    virtual bool init(bool can ,int gold,int get);
    
    Reward();
    
    virtual ~Reward();
    
    bool touchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void touchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    void touchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    int getButtonID();
    
    CC_SYNTHESIZE(bool, _isCan, isCan);
    
protected:
    
    ButtonWithSpriteManage* _buttons;
    
    std::vector<int> _gif_gold;
    
    std::vector<int> _gif_getAll;
};

#endif /* defined(__GetFish__Reward__) */
