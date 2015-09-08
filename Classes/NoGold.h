//
//  NoGold.h
//  GetFish
//
//  Created by zhusu on 15/8/17.
//
//

#ifndef __GetFish__NoGold__
#define __GetFish__NoGold__

#include "cocos2d.h"
#include "ButtonWithSpriteManage.h"

USING_NS_CC;

class NoGold : public CCLayer
{
public:
    
    static const int TYPE_GOLD = 0;
    static const int TYPE_GET = 1;
    static const int TYPE_GOLD_GET = 2;
    
    static const int TYPE_KAI_2 = 10;
    static const int TYPE_KAI_3 = 11;
    static const int TYPE_KAI_4 = 12;
    static const int TYPE_KAI_5 = 13;
    static const int TYPE_KAI_6 = 14;
    
    static const int TYPE_KAI_NO = 20;
    
    static NoGold* create(int type);
    
    virtual bool init(int type);
    
    NoGold();
    
    virtual ~NoGold();
    
    virtual void onExit();
    
    virtual void onEnter();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    
    
protected:
    
    ButtonWithSpriteManage* _buttons;
    
    int _type;
    
    
};

#endif /* defined(__GetFish__NoGold__) */
