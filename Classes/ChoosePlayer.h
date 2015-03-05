//
//  ChoosePlayer.h
//  GetFish
//
//  Created by zhusu on 15/3/5.
//
//

#ifndef __GetFish__ChoosePlayer__
#define __GetFish__ChoosePlayer__

#include "cocos2d.h"
#include "ButtonWithSpriteManage.h"

USING_NS_CC;

class ChoosePlayer : public CCLayer
{
public:
    CREATE_FUNC(ChoosePlayer);
    
    virtual bool init();
    
    ChoosePlayer();
    
    virtual ~ChoosePlayer();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void onExit();
    
    virtual void onEnter();
    
private:
    
    void setChooseIC();
    
protected:
    ButtonWithSpriteManage* _buttons;
    
    CCSize _screenSize;
    
    
    CCSprite* _player;
    
    CCSprite* _small_player;
    
    CCSprite* _left;
    CCSprite* _right;
    
    CCSprite* _chooseIc;
    
    int _nowSelect;
    
    CCNode* _buy;
    
    ButtonWithSprite* _buy_button;
};

#endif /* defined(__GetFish__ChoosePlayer__) */