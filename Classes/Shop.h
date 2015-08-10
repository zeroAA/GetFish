//
//  Shop.h
//  GetFish
//
//  Created by zhusu on 15/8/3.
//
//

#ifndef __GetFish__Shop__
#define __GetFish__Shop__

#include "cocos2d.h"
#include "ButtonWithSpriteManage.h"

USING_NS_CC;

class Shop : public CCLayer
{
public:
    
    static const int SHOP_TYPE_GOLD = 0;
    static const int SHOP_TYPE_VIP = 1;
    
    static Shop* create(int type);
    
    virtual bool init(int type);
    
    Shop();
    
    virtual ~Shop();
    
    virtual void onExit();
    
    virtual void onEnter();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    
    void setType(int type);
    
protected:
    
    ButtonWithSpriteManage* _buttons;
    
    CCNode* _gold;
    CCNode* _vip;
    
    int _type;
    
    std::vector<int> _num;
};

#endif /* defined(__GetFish__Shop__) */
