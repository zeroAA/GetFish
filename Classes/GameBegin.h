//
//  GameBegin.h
//  GetFish
//
//  Created by zhusu on 15/5/12.
//
//

#ifndef __GetFish__GameBegin__
#define __GetFish__GameBegin__

#include "cocos2d.h"
#include "ButtonWithSpriteManage.h"
#include "Fish.h"

USING_NS_CC;

class GameBegin : public CCLayer
{
public:
    static GameBegin* create(int score,int type,int fishID,int num);
    
    virtual bool init(int score,int type,int fishID,int num);
    
    GameBegin();
    
    virtual ~GameBegin();
    
    void touchesBegan(CCSet * touchs,CCEvent * event);
    
    void touchesMoved(CCSet * touchs,CCEvent * event);
    
    void touchesCancelled(CCSet * touchs,CCEvent * event);
    
    void touchesEnded(CCSet * touchs,CCEvent * event);
    
    CC_SYNTHESIZE(bool, _dead, Dead);
    
protected:
    
    ButtonWithSprite* _button_begin;
    
    CCArmature* fish;
    
    CCLabelAtlas* _score;
    
    CCLabelAtlas* _num;

};

#endif /* defined(__GetFish__GameBegin__) */
