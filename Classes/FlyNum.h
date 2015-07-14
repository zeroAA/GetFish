//
//  FlyNum.h
//  GetFish
//
//  Created by zhusu on 15/7/14.
//
//

#ifndef __GetFish__FlyNum__
#define __GetFish__FlyNum__

#include "cocos2d.h"

USING_NS_CC;

class FlyNum : public CCNode
{
public:
    
    static const int TYPE_NORMAL = 0;
    
    static const int STATE_NORMAL = 0;
    
    static const int STATE_DEAD = 1;
    
    static const int STATE_STAY = 2;
    
    static FlyNum* create(int type ,int num);
    
    virtual bool init(int type ,int num);
    
    FlyNum();
    
    virtual ~FlyNum();
    
    virtual void cycle(float delta);

    int getNum() const;
    
    int getState() const;
    
    void setShipID(int shipID);
    int getShipID() const;
    
    void setStayTime(int time);
    
    void setDes(CCPoint des);
    
protected:
    
    int _type;
    
    int _state;
    
    int _num;
    
    int _shipID;
    
    int _stayTime;
    
    CCPoint _des;
    
    CCLabelAtlas* _numLabel;
};


#endif /* defined(__GetFish__FlyNum__) */
