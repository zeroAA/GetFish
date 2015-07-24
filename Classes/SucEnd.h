//
//  SucEnd.h
//  GetFish
//
//  Created by zhusu on 15/7/24.
//
//

#ifndef __GetFish__SucEnd__
#define __GetFish__SucEnd__

#include "cocos2d.h"
#include "ButtonWithSpriteManage.h"

USING_NS_CC;

class SucEnd : public CCLayer
{
public:
    
    static const int DEAD_TYPE_REST = 0;
    
    static const int DEAD_TYPE_BACK = 1;
    
    static const int DEAD_TYPE_NEXT = 2;
    
    CREATE_FUNC(SucEnd);
    
    virtual bool init();
    
    SucEnd();
    
    virtual ~SucEnd();
    
    void touchesBegan(CCSet * touchs,CCEvent * event);
    
    void touchesMoved(CCSet * touchs,CCEvent * event);
    
    void touchesEnded(CCSet * touchs,CCEvent * event);
    
    CC_SYNTHESIZE(int, _dead, Dead);
    
protected:
    
    CCLabelAtlas* _numLabel;
    
    ButtonWithSpriteManage* _buttons;
};


#endif /* defined(__GetFish__SucEnd__) */
