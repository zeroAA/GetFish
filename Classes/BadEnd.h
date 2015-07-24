//
//  BadEnd.h
//  GetFish
//
//  Created by zhusu on 15/7/22.
//
//

#ifndef __GetFish__BadEnd__
#define __GetFish__BadEnd__

#include "cocos2d.h"
#include "ButtonWithSpriteManage.h"

USING_NS_CC;

class BadEnd : public CCLayer
{
public:
    
    static const int DEAD_TYPE_REST = 0;
    
    static const int DEAD_TYPE_BACK = 1;
    
    static const int DEAD_TYPE_PLAY = 2;
    
    CREATE_FUNC(BadEnd);
    
    virtual bool init();
    
    BadEnd();
    
    virtual ~BadEnd();
    
    void touchesBegan(CCSet * touchs,CCEvent * event);
    
    void touchesMoved(CCSet * touchs,CCEvent * event);
    
    void touchesEnded(CCSet * touchs,CCEvent * event);
    
    CC_SYNTHESIZE(int, _dead, Dead);
    
protected:
    
    CCLabelAtlas* _numLabel;
    
    ButtonWithSpriteManage* _buttons;
};


#endif /* defined(__GetFish__BadEnd__) */
