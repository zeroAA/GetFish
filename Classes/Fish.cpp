//
//  Fish.cpp
//  GetFish
//
//  Created by zs on 14-12-8.
//
//

#include "Fish.h"
#include "Common.h"
#include "Tools.h"
//#include "FishingPlayLayer.h"

Fish* Fish::create(int type,float speed , int dir ,const char* name)
{
    Fish* fish = new Fish();
    
    if(fish && fish->init(type,speed , dir, name)) {
        fish->autorelease();
        return fish;
    }
    
    CC_SAFE_DELETE(fish);
    return NULL;
}



Fish::Fish():_deadType(HOOK_DEAD),_volume(1),_aY(0),_isDead(false),_exitDead(EXIT_DEAD_NORMAL),_startX(0),_startY(0),_stayTime(0),_tortoiseC(0),_deadTime(0),_changeTime(0),_shipID(-1)
{
    
}

Fish::~Fish()
{
    
}



bool Fish::init(int type,float speed , int dir ,const char* name)
{
    
    if(Actor::init(name)) {
        
        _screenSize = CCDirector::sharedDirector()->getWinSize();
        _id = type;
        setSpeed(speed,0);
        _dir = dir;
        this->initData();
        
        setState(ACT_STATE_WALK);
        return true;
    }
    
    return false;
}


void Fish::initData()
{
    
    
    if (_dir==DIR_RIGHT) {


        playWithIndex(ANIM_RIGHT);
        _x =-getBodyRect().size.width/2+1;
    } else {
       
        playWithIndex(ANIM_LEFT);
        _x =_screenSize.width+getBodyRect().size.width/2-1;

    }
    
    this->_y = Tools::randomFloatInRange( _screenSize.height-this->FISH_Y_MIN,this->FISH_Y_MAX);
    
    
   
    this->setPosition(ccp(_x, _y));
    
    
    
}

void Fish::cycle(float delta)
{
    
    if (_state == STATE_DEAD) {
        return;
    }
    
    
    switch (_exitDead) {
        case EXIT_DEAD_NORMAL:
            if (isExitMap()) {
                setDead(true);
            }
            break;
            
        case EXIT_DEAD_LEFT:
            if (isExitMapLeft()) {
                setDead(true);
            }
            
            break;
            
        case EXIT_DEAD_RIGHT:
            if (isExitMapRight()) {
                setDead(true);
            }
            
            break;
            
        default:
            if (isExitMap()) {
                
                setDead(true);
            }
            break;
    }
    
    
    switch (_state) {
        case ACT_STATE_GO:
        case ACT_STATE_DOLPHIN_ATK:
        case ACT_STATE_WALK:
            
            if (getType() == SWORDFISH) {
                _changeTime--;
                if (_changeTime==0) {
                    _speedx=2*_speedx;
                }
            }
            
            if(_dir == DIR_RIGHT){
                _x +=_speedx;
            }else{
                _x -=_speedx;
            }
            
            setSharkAnim();
            
            break;
            
        case ACT_STATE_TURN:
        
            _speedy-=2;
        
            _x -= 6.0f;
        
            _y += _speedy;
        
//            if (_speedy <0 && _y <= _screenSize.height - FishingPlayLayer::_kegY) {
//                _y = _screenSize.height - FishingPlayLayer::_kegY;
//                setDead(true);
//            }
        
            break;
            
        case ACT_STATE_DOLPHIN_READY:
        
            if (!getAnimation()->getIsPlaying()) {
                setState(ACT_STATE_DOLPHIN_ATK);
            
                setSpeedX(20);
                
                this->setAnim(ANIM_ATK);
            }
        
            break;
            
        case ACT_STATE_LIGHT_READY:
            
            if (!getAnimation()->getIsPlaying()) {
                setState(ACT_STATE_LIGHT);
               
                this->setAnim(6);
            }
            
            break;
        case ACT_STATE_LIGHT:
            
            if (!getAnimation()->getIsPlaying()) {
                this->setAnim(0);
                setGo();
            }
            
            break;
            
        case ACT_STATE_TORTOISE_READY:
            if (!getAnimation()->getIsPlaying()) {
                setState(ACT_STATE_TORTOISE);
                
                this->setAnim(6);
                
                setTortoiseC(3);
                
                int r = Tools::randomIntInRange(0, 3);
                
                if (r==0) {
                    
                    setSpeed(15, -10);
                    
                }else if(r == 1){
                    
                    setSpeed(-15, 10);
                    
                }else if(r == 2){
                    
                    setSpeed(15, 10);
                   
                }else{
                    
                    setSpeed(-15, -10);
            
                }
            }
            break;
            
        case ACT_STATE_TORTOISE:
            
            
            _x +=_speedx;
            _y +=_speedy;

            if (_x > _screenSize.width-getBodyRect().size.width/2 && _tortoiseC > 0) {
                
				_tortoiseC--;
                
				_x = _screenSize.width-getBodyRect().size.width/2;
				_speedx = -_speedx;
			}
            
			if (_x < getBodyRect().size.width/2 && _tortoiseC > 0) {
				_tortoiseC--;
				_x = getBodyRect().size.width/2;
				_speedx = -_speedx;
			}
            
			if (_y < 50) {
				_tortoiseC--;
                
				_y = 50;
                
				_speedy = -_speedy;
			}
            
			if (_y > _screenSize.height-this->FISH_Y_MIN) {
                
				_tortoiseC--;
                
				_y = _screenSize.height-this->FISH_Y_MIN;
                
				_speedy = -_speedy;
			}
            setTortoiseR();
            break;
        case ACT_STATE_GOTOSHIP:
        
            _x = getPositionX();
            _y = getPositionY();
        
            if (this->numberOfRunningActions()==0) {
                setState(ACT_STATE_ZHUANG_STAY);
                _stayTime = 40;
                
                setAnim(Fish::ANIM_ATK_READY);
                
            }
        
            break;
        
        case ACT_STATE_ZHUANG_STAY:
        
//            _stayTime--;
        
//            if (_stayTime<=0) {
            
            if (getAnimation()->getIsComplete()) {
            
            
                setDes(_startX,_startY,2);
                setState(ACT_STATE_ZHUANG_END);
                setAnim(Fish::ANIM_RIGHT);
                
            }
        
            break;
        
        case ACT_STATE_ZHUANG_END:
            _x = getPositionX();
            _y = getPositionY();
            if (this->numberOfRunningActions()==0) {
                setState(ACT_STATE_WALK);
//                CCLOG("end???");
            }
        
            break;
            
        case ACT_STATE_ZHUANG_ATK:
            
            if (getAnimation()->getIsComplete()) {
                setDes(_startX,_startY,2);
                setState(ACT_STATE_ZHUANG_END);
                setAnim(0);
            }
            
            break;
        case ACT_STATE_HAN_UP:
            
                if (getDir() == DIR_LEFT) {
                    _x -= 7;
                } else {
                    _x += 7;
                    
                }
                
                _speedy -= _aY;
                _y += _speedy;
            
            if (getDir() == DIR_LEFT) {
                if (getRotation() == 90 && _speedy<0) {
                    setRotation(-90);
                }
            }else{
                if (getRotation() == -90 && _speedy<0) {
                    setRotation(90);
                }
            }
            
            
                
                if (_y <= _oldy) {
                    _y = _oldy;
                    
                    setSpeedY(0);
                    
                    setRotation(0);
    
                    setAnim(ANIM_RIGHT);
                    setState(ACT_STATE_WALK);
                    
                   
                }
            
                break;
            
        case ACT_STATE_HAN_ATK:
            
            _deadTime--;
            if (_deadTime<=0) {
               setDead(true);
            }
            
            break;
            
        case ACT_STATE_DEN:
            if(_dir == DIR_RIGHT){
                _x +=15;
            }else{
                _x -=15;
            }
            break;
            
        case ACT_STATE_SHOCK:
            
            _stayTime--;
            if (_stayTime<0) {
                setGo();
                setAnim(ANIM_RIGHT);
            }
            
            break;
        case ACT_STATE_FALL:
            
            _y -=15;
            
            if (_y<_screenSize.height-this->FISH_Y_MIN-30) {
                setGo();
            }
            
            break;
        default:
            break;
    }
   
    
    this->setPosition(ccp(_x, _y));
}

void Fish::setSpeed(float  spdx, float spdy)
{
    setSpeedX(spdx);
    setSpeedY(spdy);
}

bool Fish::isExitMap()
{
    float dx = 0;
    
    if (isStrong()) {
        dx = 100;
    }
    
    return  ((this->getPositionX() + getBodyRect().size.width/2) < -dx || this->getPositionX()- getBodyRect().size.width/2> _screenSize.width+dx);
}

bool Fish::isExitMapLeft()
{
    
    float dx = 0;
    
    if (isStrong()) {
        dx = 100;
    }
    
    return  ((this->getPositionX() + getBodyRect().size.width/2) < -dx);
}

bool Fish::isExitMapRight()
{
    
    float dx = 0;
    
    if (isStrong()) {
        dx = 100;
    }
    
    
    return (this->getPositionX()- getBodyRect().size.width/2> _screenSize.width+dx);
}

//void Fish::draw()
//{
////    ccDrawColor4B(0xff, 0xff, 0xff, 0);
////    glLineWidth(1.0f);
////    
////    CCRect*rect =_anim->bodyRectInWorld();
////
////    ccDrawRect(ccp(rect->origin.x, rect->origin.y), ccp(rect->origin.x+rect->size.width, rect->origin.y+rect->size.height));
////    
//////    ccDrawColor4B(0x00, 0x00, 0x00, 0);
//////    glLineWidth(1.0f);
////    rect =_anim->attackRectInWorld();
////    
////    ccDrawRect(ccp(rect->origin.x, rect->origin.y), ccp(rect->origin.x+rect->size.width, rect->origin.y+rect->size.height));
//
//}

bool Fish::isFishDead()
{
    return _isDead;
}

bool Fish::isState(int state)
{
    return _state == state;
}

void Fish::setState(int state)
{
    _state = state;
}

void Fish::setShipID(int id)
{
    _shipID = id;
}



bool Fish::isCanHooked() {
    return _state == ACT_STATE_NORMAL || _state == ACT_STATE_WALK || _state == ACT_STATE_GO || _state == ACT_STATE_GO_TIME || _state == ACT_STATE_GO_TIME_DOWN;
}

bool Fish::isHooked() {
    
    if (isCanHooked()) {
        
        
        playWithIndex(ANIM_HOOK);
        _state = ACT_STATE_HOOKED;
        
        return true;
        
    }
    
    return false;
    
}

bool Fish::issetXY() {
    return _state == ACT_STATE_HOOKED || _state == ACT_STATE_ESCAPE;
}

int Fish::getShipID()
{
    return _shipID;
}


void Fish::setDead(bool isdead)
{
    _isDead = isdead;
    if (_isDead) {
        setState(STATE_DEAD);
    }
    
   
}

void Fish::setSpeedX(float sx)
{
    _speedx = sx;
}

void Fish::setSpeedY(float sy)
{
    _speedy = sy;
}



int Fish::getVolume()
{
    return _volume;

}

void Fish::setXY(float x,float y)
{
    _x = x;
    _y = y;
    setPosition(ccp(_x, _y));
}

void Fish::setTurn()
{
    
}

bool Fish::isNormalFish()
{
    return _id<=NORMAL_E;
}

bool Fish::isDolphin()
{
    return  _id == DOLPHIN;
}

bool Fish::isLightFish()
{
    return  _id == LIGHTFISH;
}

bool Fish::isTortoise()
{
    return _id == TORTOISE;
}

void Fish::setAnim(int anim)
{
    
    if (anim != ANIM_HOOK && anim != ANIM_TURN && _dir == DIR_LEFT) {
       
        anim++;
        
        
    }
    
     
    playWithIndex(anim);
}

int Fish::getID()
{
    return _id;
}

bool Fish::isUseFish()
{
    return isDolphin() || isLightFish() || isTortoise();
}

bool Fish::isHook()
{
    return _state == ACT_STATE_HOOKED || _state == ACT_STATE_ESCAPE;
}

bool Fish::isShark()
{
    return _id == SHARK;
}

bool Fish::isSword()
{
    return _id == SWORDFISH;
}

bool Fish::isStrong()
{
    return _id == STRONGFISH;
}

bool Fish::isEle()
{
    return _id == ELEFISH;
}

void Fish::setGo()
{
    _exitDead = EXIT_DEAD_NORMAL;
 
    if (_y>_screenSize.height-this->FISH_Y_MIN) {
        setState(ACT_STATE_FALL);
    }else{
        _state = ACT_STATE_GO;
    
        setSpeedX(20);
        
        setAnim(ANIM_RIGHT);
        
        getAnimation()->setSpeedScale(1.5);
    }
}

void Fish::setTortoiseC(int c)
{
    _tortoiseC = c;
}

void Fish::setTortoiseR()
{
    if (_speedx < 0) {
        
        if (getCurrentMovementID()!="Animation8") {
            playWithIndex(7);
        }
        
        
        if (_speedy < 0) {
            setRotation(-30);
        } else {
            setRotation(30);
        }
    } else {
        if (getCurrentMovementID()!="Animation7") {
            playWithIndex(6);

        }
        if (_speedy < 0) {
            setRotation(30);
        } else {
            setRotation(-30);
        }
    }
}

bool Fish::isWhale()
{
    return _id == WHALE;
}

bool Fish::isEat()
{
    return _id == EATFISH;
}



int Fish::getDir()
{
    return _dir;
}

float Fish::getX()
{
    return _x;
}

float Fish::getY()
{
    return _y;
}

void Fish::setStartPos(float x,float y)
{
    _startX = x;
    _startY = y;
}

void Fish::setDes(float desX,float desY, float time)
{
		
//    if (_dir == DIR_RIGHT) {
//        if (_x > desX) {
//            _dir = DIR_LEFT;
//                
//            setAnim(_anim->getCurAnimationIndex());
//                
//        }
//    } else {
//        if (_x < desX) {
//            _dir = DIR_RIGHT;
//                
//            setAnim(_anim->getCurAnimationIndex());
//        }
//    }
    
    CCMoveTo* move = CCMoveTo::create(time, ccp(desX, desY));
    
    this->runAction(move);

}

void Fish::setOLDY(float y)
{
    _oldy = y;
}

void Fish::setAY(float a)
{
    _aY = a;
}

float Fish::getSpeedY() const
{
    return _speedy;
}

void Fish::setDeadTime(float time)
{
    _deadTime = time;
}

int Fish::getType() const
{
    return _id;
}

void Fish::setDeadType(int type)
{
    _deadType = type;
}

void Fish::setSharkAnim()
{
    if (_id == SHARK&&(getCurrentMovementID()=="Animation8"||getCurrentMovementID()=="Animation7")&&getAnimation()->getIsComplete()) {
        
        setAnim(ANIM_RIGHT);
    }
    
}

void Fish::setChangeTime(float time)
{
    _changeTime = time;
}

void Fish::setStayTime(float time)
{
    _stayTime = time;
}