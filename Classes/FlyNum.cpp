//
//  FlyNum.cpp
//  GetFish
//
//  Created by zhusu on 15/7/14.
//
//

#include "FlyNum.h"
#include "Tools.h"

FlyNum* FlyNum::create(int type,int num)
{
    FlyNum* ref = new FlyNum();
    
    if(ref && ref->init(type,num)) {
        ref->autorelease();
        return ref;
    }
    
    CC_SAFE_DELETE(ref);
    return NULL;
}



FlyNum::FlyNum():_type(TYPE_NORMAL),_state(STATE_NORMAL),_shipID(-1),_stayTime(0)
{
    
}

FlyNum::~FlyNum()
{
}

bool FlyNum::init(int type ,int num)
{
    
    
    if(CCNode::init()) {
        
        _type = type;
        _num = num;
        if (_type == TYPE_NORMAL2) {
            _numLabel = CCLabelAtlas::create(Tools::intToString(num).c_str(), "ui/shuzi1.png", 21, 28, 43);
        }else{
            _numLabel = CCLabelAtlas::create(Tools::intToString(num).c_str(), "ui/shuzi4.png", 21, 28, 43);
        }
        
        _numLabel->setAnchorPoint(ccp(0.5, 0.5));
        
        addChild(_numLabel);
        
        schedule(schedule_selector(FlyNum::cycle));
        
        return true;
    }
    return  false;
}

void FlyNum::cycle(float delta)
{
    switch (_state) {
        case STATE_STAY:
           
            _stayTime--;
            if (_stayTime<=0) {
               
                _state = STATE_NORMAL;
                this->setVisible(true);
                CCMoveTo* to = CCMoveTo::create(ccpDistance(this->getPosition(), _des)/500, _des);
                runAction(to);
            }
            
            break;
        case STATE_NORMAL:
            if (this->numberOfRunningActions() == 0) {
                _state = STATE_DEAD;
            }
            break;
            
        default:
            break;
    }
}

int FlyNum::getNum() const
{
    return _num;
}

int FlyNum::getState() const
{
    return _state;
}

void FlyNum::setShipID(int shipID)
{
    this->_shipID = shipID;
}

int FlyNum::getShipID() const
{
    return _shipID;
}

void FlyNum::setStayTime(int time) 
{
    _stayTime = time;
    _state = STATE_STAY;
    this->stopAllActions();
    this->setVisible(false);
}

void FlyNum::setDes(cocos2d::CCPoint des)
{
    _des = des;
}