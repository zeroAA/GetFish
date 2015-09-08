//
//  IosIosIosShop.h
//  GetFish
//
//  Created by zhusu on 15/8/11.
//
//

#ifndef __GetFish__IosShop__
#define __GetFish__IosShop__

#include "cocos2d.h"
#include "ButtonWithSpriteManage.h"

USING_NS_CC;

class IosShop : public CCLayer
{
public:
    
    static const int IosShop_TYPE_GOLD = 0;
    static const int IosShop_TYPE_VIP = 1;
    
    static IosShop* create(int type);
    
    virtual bool init(int type);
    
    IosShop();
    
    virtual ~IosShop();
    
    virtual void onExit();
    
    virtual void onEnter();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    void setButton(int indext);
    
private:
    
    void setType(int type);
    
protected:
    
    ButtonWithSpriteManage* _buttons;
    
    CCNode* _gold;
    CCNode* _vip;
    
    int _type;
    
    std::vector<int> _num;
    std::vector<int> _jiage;
    
};
#endif /* defined(__GetFish__IosShop__) */
