//
//  Pause.h
//  GetFish
//
//  Created by zhusu on 15/7/20.
//
//

#ifndef __GetFish__Pause__
#define __GetFish__Pause__

#include "cocos2d.h"
#include "ButtonWithSpriteManage.h"
#include "Fish.h"

USING_NS_CC;

class Pause : public CCLayer
{
public:
    
    static const int DEAD_TYPE_NODEAD = 0;
    
    static const int DEAD_TYPE_BACK = 1;
    
    static const int DEAD_TYPE_TOGAME = 2;
    
   
    static Pause* create(int score,int type,int fishID,int num);
    
    virtual bool init(int score,int type,int fishID,int num);
    
    Pause();
    
    virtual ~Pause();
    
    void touchesBegan(CCSet * touchs,CCEvent * event);
    
    void touchesMoved(CCSet * touchs,CCEvent * event);
    
    void touchesCancelled(CCSet * touchs,CCEvent * event);
    
    void touchesEnded(CCSet * touchs,CCEvent * event);
    
    CC_SYNTHESIZE(int, _dead, Dead);
    
protected:
    
    ButtonWithSpriteManage* _buttons;
    
    CCArmature* fish;
    
    CCLabelAtlas* _score;
    
    CCLabelAtlas* _num;
    
};

#endif /* defined(__GetFish__Pause__) */
