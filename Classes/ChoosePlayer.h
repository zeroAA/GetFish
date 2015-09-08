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
#include "NoGold.h"

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
    
    bool getIsDead() const;
    
    int getNowPlayer() const;
    
    void setChoose(int choose);
    
    void setBuyV(bool buy);
    
    
    
private:
    
    void setChooseIC();
    
    void changePlayer();
    
protected:
    ButtonWithSpriteManage* _buttons;
    
    CCSize _screenSize;
    
    
   
    
    CCArray* _small_players;
    
    CCSprite* _left;
    CCSprite* _right;
    
    CCSprite* _chooseIc;
    
    int _nowSelect;
    
    CCNode* _buy;
    
    ButtonWithSprite* _buy_button;
    
    CCArray* _players;
    
    bool _isDead;
    CCLabelAtlas* _goldLabel;
    
    CCSprite* zi1;
    CCSprite* zi2;
    
    std::vector<int> _player_gold;
    
    NoGold* _tishi;
    
};

#endif /* defined(__GetFish__ChoosePlayer__) */
