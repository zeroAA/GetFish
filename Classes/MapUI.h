//
//  MapUI.h
//  GetFish
//
//  Created by zhusu on 15/2/3.
//
//

#ifndef __GetFish__MapUI__
#define __GetFish__MapUI__

#include "cocos2d.h"
#include "MapElement.h"
#include "ButtonWithSpriteManage.h"
#include "ScrollView.h"

USING_NS_CC;

class MapUI : public CCLayer
{
public:
    
    static MapUI* create(int lev);
    
    virtual bool init(int lev);
    
    MapUI();
    
    virtual ~MapUI();
    
    virtual void onExit();
    
    virtual void onEnter();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    int getNowSelect() const;
    
    bool isToGame() const;
private:
    
    void cycle(float delta);
    
    void setChooseIC();
protected:
    
    CCArray* _mapE;

    CCSize _screenSize;
    
    ButtonWithSpriteManage* _buttons;
    
     CCLayer* _container;
    
    ScrollView* _scroll;
    
    CCScrollView* _sc;
    
    CCLayer* _levE;
    
    CCSprite* _chooseIc;
    
    int _nowSelect;
};

#endif /* defined(__GetFish__MapUI__) */
