//
//  Ship.cpp
//  GetFish
//
//  Created by zs on 14-12-9.
//
//

#include "Ship.h"
#include "Fish.h"
#include "Common.h"
#include "Tools.h"
#include "GameScene.h"

//#include "AudioController.h"






#define Z_HOOK     999
#define Z_TURN     1000


Ship* Ship::create(int type,int ID ,const char* name)
{
    Ship* ship = new Ship();
    
    if(ship && ship->init(type,ID,name)) {
        ship->autorelease();
        return ship;
    }
    
    CC_SAFE_DELETE(ship);
    return NULL;
}



Ship::Ship():_type(TYPE_PLAYER),_timeC(0),_hit(0),_HOOK_MOVE_DISTANCE(0),_testTime(0),_noHurtTime(0),_hookCurAngle(0),_stopTime(0),_speed(10),_volume(0),_volumeMax(1000),_hoolSpeed(12),_hookSpeed(10),_score(0),_moveCD(120),_moveCD_MAX(120),_w_Fish(NULL),_getC(0),_getTime(0),_getTimeMax(0)
{
    
}

Ship::~Ship()
{
    if (_anims) {
        _anims->release();
        _anims=NULL;
    }
    
    if (_fishSetHooked) {
        _fishSetHooked->release();
        _fishSetHooked=NULL;
    }
    
    CC_SAFE_DELETE(_items);
    
    if (_TurnFish) {
        _TurnFish->release();
        _TurnFish = NULL;
    }
}

bool Ship::init(int type,int ID ,const char* name)
{
    
   
    if(Actor::init(name)) {
        
        _state = ACT_STAND;
        
        ANGLE_TAN.push_back(0);
        ANGLE_TAN.push_back(17);
        ANGLE_TAN.push_back(35);
        ANGLE_TAN.push_back(52);
        ANGLE_TAN.push_back(70);
        ANGLE_TAN.push_back(87);
        ANGLE_TAN.push_back(176);
        
        _anims = CCArray::create();
        
        _anims -> retain();
        
        _fishSetHooked = CCArray::create();
        
        _fishSetHooked->retain();
        
        _items = CCArray::create();
        
        _items -> retain();
        
        _TurnFish = CCArray::create();
        
        _TurnFish -> retain();
        
        _screenSize = CCDirector::sharedDirector()->getWinSize();
        
        _HOOK_MOVE_DISTANCE = _screenSize.height-HOOK_DES;
        
        _type = type;
        
        setID(ID);
        
        if(type == TYPE_AI){
            this->setScaleX(-1);
        }
        
        this->initData();
        
        _ct = CCSprite::createWithSpriteFrameName("citieshi_23.png");
        _ct->setPosition(ccp(0, getBodyRect().size.height*0.5));
        _ct->setOpacity(0);
        addChild(_ct,999);
        
//        this->schedule(schedule_selector(Ship::cycle));
        
//        this->setZOrder(-10);
        
        return true;
    }
    
    return false;
}

void Ship::addCTEffe()
{
    _ct->setOpacity(255);
    _ct->setScale(0.2);
    CCFadeOut* out = CCFadeOut::create(0.5);
    CCScaleTo* st = CCScaleTo::create(0.5, 2);
    
    _ct->runAction(CCSequence::create(st,out,NULL));
}

void Ship::initData()
{
        
    setHook(_id);

    if (_type == TYPE_PLAYER) {
        _x =_screenSize.width/3;
    }else{
        _x =_screenSize.width*2/3;
    }
    
    _y = _screenSize.height-SHIP_INIT_Y;
    
    this->setPosition(ccp(_x, _y));
    
    runUpDown();
    
}

void Ship::setGetTime(int time,int c){
    _getC = c;
    _getTime = _getTimeMax = time;
}

void Ship::cycle(float delta)
{
    
    if (_noHurtTime >0) {
        _noHurtTime--;
//        if((int)(_noHurtTime*0.3)%2 == 0){
//            setVisible(false);
//        }else{
//            setVisible(true);
//        }
    }else{
//        if (!isVisible()) {
//            setVisible(true);
//        }
    }
    
    if (_type == TYPE_AI) {
        _moveCD--;
        if (_moveCD<=0) {
            _moveCD = _moveCD_MAX;
            setShipTo(Tools::randomIntInRange(_screenSize.width*0.2, _screenSize.width*0.8));
        }
       
        if (_getC>0) {
            _getTime--;
            if (_getTime<=0) {
                _getC--;
                _getTime = _getTimeMax;
                GameScene::instance()->allFishToDead(1);
            }
        }
    }
    
    if (_state == ACT_WALK) {
        
        if (_x == _desX) {
            _state = ACT_STAND;
            
        }
        
        if (_x > _desX) {
            
            _dir = DIR_LEFT;
            if ((_x - _speed) < _desX) {
                _x = _desX;
                
            } else {
                _x -= _speed;
                
                if (_type == TYPE_PLAYER) {
                    if (_x  <= LEFT_BORDER) {
                        _x = LEFT_BORDER;
                        
                    }
                }
            }
        } else if (_x < _desX) {
            _dir = DIR_RIGHT;
            
            if ((_x + _speed) > _desX) {
                _x = _desX;
                
            } else {
                _x += _speed;
                
                if (_type == TYPE_PLAYER) {
                    if (_x  >=_screenSize.width- RIGHT_BORDER) {
                        _x =_screenSize.width- RIGHT_BORDER;
                        
                    }
                }
            }
        }
        
       
    }else if (_state == ACT_TURN_FISH){
        
        _timeC++;
        if (_timeC%9==0) {
            bool ishasfish = false;
            for (int i = 0; i < _TurnFish->count(); ++i) {
                Fish* fish =(Fish*) _TurnFish->objectAtIndex(i);
                if (!fish->isState(Fish::ACT_STATE_TURN)) {
                    fish->setVisible(true);
                    fish->setState(Fish::ACT_STATE_TURN);
                    fish->setXY(_x,_y+10);
                    
                    fish->setSpeedY(25);
                    
                    fish->playWithIndex(Fish::ANIM_TURN);
                    
                    CCRotateBy* action = CCRotateBy::create(1, -360);
                    
                    CCRepeatForever* repeat = CCRepeatForever::create(action);
                    
                    fish->runAction(repeat);
                    
                    _volume -= fish->getVolume();
                    ishasfish = true;
                    
                    _TurnFish->removeObject(fish);
                    break;
                }
                
            }
            
            if (!ishasfish) {
                _volume = 0;
                _TurnFish->removeAllObjects();
            }
            
            if (_volume <= 0) {
                _volume = 0;
                _state = ACT_STAND;
                _TurnFish->removeAllObjects();
            }
        }
        
        
    }else if(_state == ACT_FLY){
        
        if (_w_Fish) {
            
            if (_w_Fish->isState(Fish::ACT_STATE_ZHUANG_ATK)) {
//                CCDirector::sharedDirector()->getActionManager()->pauseTarget(this);
                this->stopAllActions();
                _y =_w_Fish->getPositionY()+_w_Fish->getBone("whale")->getWorldInfo()->y;
                this->setPositionY(_y);
            }else{
//                CCDirector::sharedDirector()->getActionManager()->resumeTarget(this);
                
                _w_Fish = NULL;
                runFall();
                
                setState(ACT_FALL);
            }
            
        }else{
            _w_Fish = NULL;
            runFall();
            setState(ACT_FALL);
        }
        
    }else if(_state == ACT_FALL){
        
        if (this->numberOfRunningActions()==0) {
            _y = _screenSize.height-SHIP_INIT_Y;
            
            this->setPositionY(_y);
            
            //            CCDirector::sharedDirector()->getActionManager()->resumeTarget(this);
            setState(ACT_STAND);
            changeToNohurt();
            runUpDown();

        }
        
    }else if(_state == ACT_EATED){
        
        _stopTime--;
        if (_stopTime<=0) {
            setState(ACT_STAND);
            changeToNohurt();
        }
        
    }else if(_state == ACT_CUT_LINE){
        
        _cut_Pos.y -= 2.5;
        
        _cut_hook.y -=2.5;

        _hook_anim->setPosition(_cut_hook);
        
        _stopTime--;
        if (_stopTime<=0) {
            initHook();
            setState(ACT_STAND);
            changeToNohurt();
        }
        
    }else if(_state == ACT_PULL){
        if (_w_Fish!=NULL) {
            if (_w_Fish->getDir() == DIR_LEFT) {
                _hook_anim->setRotation(-60*this->getScaleX());
                _hook_anim->setPosition(ccpAdd(ccp(_pull_pos.x*this->getScaleX(),_pull_pos.y), ccp(30*this->getScaleX(), -40)));
            }else{
                _hook_anim->setRotation(60*this->getScaleX());
                _hook_anim->setPosition(ccpAdd(ccp(_pull_pos.x*this->getScaleX(),_pull_pos.y), ccp(-30*this->getScaleX(), -40)));
            }
        }else{
            
            _hook_anim->setPosition(ccp(_pull_pos.x*this->getScaleX(),_pull_pos.y));
            
        }
        
        
    }else if(_state == ACT_ELE){
        _stopTime -- ;
        if (_stopTime<=0) {
            playWithIndex(0);
            setState(ACT_STAND);
            changeToNohurt();
        }
    }
    
    
    if (_state != ACT_SHOCKED &&_state != ACT_ELE && _state != ACT_PULL&& _state != ACT_CUT_LINE) {
        
        cycleHook();
        
    }
    
//    if (_x >= 180 && _x < 190+_speed) {
//        if (_type == TYPE_PLAYER && _volume > 0) {
//            
//            setState(ACT_TURN_FISH);
//        }
//    }
    
    this->setPositionX(_x);
    
    
    
}


void Ship::addVolume(int v) {
    
    _volume += v;
   
}

bool Ship::isShipFull()
{
    return this->_volume >= this->_volumeMax;
}

bool Ship::isCanMove() {
    
    
    
    return _state == ACT_WALK || _state == ACT_STAND;
}

bool Ship::isShipNormal() {
 
    return isCanMove() && _noHurtTime <= 0;
}

bool Ship::isPlayer()
{
    return _type == TYPE_PLAYER;
}

void Ship::setState(int state)
{
    _state = state;
}

void Ship::setDesX(float x)
{
    _desX = x;
}

void Ship::setHook(int type)
{
    if (_type == TYPE_AI) {
        _hook_anim =CCSprite::create(("ship/hook100.png"));
    }else{
        _hook_anim =CCSprite::create(("ship/hook"+Tools::intToString(type-1)+".png").c_str());
    }
    
    _hookDx = _hookInitDx = getBone("hook")->getWorldInfo()->x;
    _hookDy = _hookInitDy = getBone("hook")->getWorldInfo()->y;
    
    _hookDir = HOOK_DIR_UP;
    
    _bHasFishHooked = false;
    if (type == 1) {
        _hook_anim->setAnchorPoint(ccp(0.6, 1));
    }else{
        _hook_anim->setAnchorPoint(ccp(0.5, 1));
    }
    _hook_anim->setPosition(ccp(_hookDx,_hookDy));
    
    this->addChild(_hook_anim,Z_HOOK);
    
//    _hook_anim->getAnimation()->playByIndex(type);
}

void Ship::initHook()
{
   
    _hookDx = _hookInitDx;
    _hookDy = _hookInitDy;
    _hookDir = HOOK_DIR_UP;
    
    _bHasFishHooked = false;
    
    _hook_anim->setPosition(ccp(_hookDx,_hookDy));
}

void Ship::hookFish() {
    
    _bHasFishHooked = true;
    
    _hookDir = HOOK_DIR_UP;
}

void Ship::setNormal() {
    if (_state == ACT_SHOCKED || _state == ACT_FLY || _state == ACT_FALL || _state == ACT_FALL_END || _state == ACT_EATED || _state == ACT_CUT_LINE || _state == ACT_PULL) {
        _state = ACT_STAND;
        changeToNohurt();
    }
}

void Ship::changeToNohurt() {
    
    CCFadeOut* out = CCFadeOut::create(0.1);
    
    CCFadeIn* in = CCFadeIn::create(0.1);
    
    CCSequence* sq = CCSequence::create(out,in,NULL);
    
    CCRepeat* re = CCRepeat::create(sq, 4);
    
    this->runAction(re);
    
    _hook_anim->setRotation(0);
    
    playWithIndex(ANIM_FISHMAN_NORMAL);
    _noHurtTime = NO_HURT_TIME_MAX;
}

void Ship::switchHookDir()
{
    
    if (!_bHasFishHooked) {
        if (_hookDir == HOOK_DIR_UP) {
            _hookDir = HOOK_DIR_DOWN;
//            AUDIO->playSfx("music/fishingLineDown");
        } else {
            _hookDir = HOOK_DIR_UP;
        }
    }
}

void Ship::clearHook()
{
    _hookDir = HOOK_DIR_UP;
    _hookDy = _hookInitDy;
}

void Ship::setHookUp()
{
    _hookDir = HOOK_DIR_UP;
}

bool Ship::isHookOver() {

    return _hookDir == HOOK_DIR_UP && _hookDy == _hookInitDy;
  
}

void Ship::cycleHook()  {
    
    if (_bHasFishHooked) {
        if (_hookDir == HOOK_DIR_DOWN) {
            _hookDir = HOOK_DIR_UP;
            
        }
        _hookDy += _hookSpeed + _hookSpeed*0.5;
        if (_hookDy > _hookInitDy) {
            _hookDy = _hookInitDy;
            
            _hit = 0;
            
            reapFishSetHooked();
            
            _bHasFishHooked = false;
        }
    } else {
        if (_hookDir == HOOK_DIR_UP) {
            _hookDy += _hookSpeed;
            if (_hookDy > _hookInitDy) {
                _hookDy = _hookInitDy;
                
            }
        } else if (_hookDir == HOOK_DIR_DOWN) {
            _hookDy -= _hookSpeed;
            if (_hookDy < _hookInitDy - _HOOK_MOVE_DISTANCE) {
                _hookDy = _hookInitDy - _HOOK_MOVE_DISTANCE;
                _hookDir = HOOK_DIR_UP;
            }
        }
    }
    
    
    
    if (_hookDy > _hookInitDy - _HOOK_MOVE_DISTANCE / 4) {
        _hookWaveType = HOOK_WAVE_NULL;
        _hookAngleType = ANGLE_NULL;
    }
    
    if (_state == ACT_WALK) {
        _hookWaveCount = 0;
        
        if (_dir == DIR_LEFT) {
            if (_hookAngleType == ANGLE_NULL) {
                _hookAngleType = ANGLE_PLUS;
                _hookWaveType = HOOK_WAVE_UP;
            } else if (_hookAngleType == ANGLE_PLUS) {
                _hookWaveType = HOOK_WAVE_UP;
            }
        } else if (_dir == DIR_RIGHT) {
            if (_hookAngleType == ANGLE_NULL) {
                _hookAngleType = ANGLE_MINUS;
                _hookWaveType = HOOK_WAVE_UP;
            } else if (_hookAngleType == ANGLE_MINUS) {
                _hookWaveType = HOOK_WAVE_UP;
            }
        }
    }
    
    if (_hookWaveCount < 5) {
        if (_hookWaveType == HOOK_WAVE_UP) {
            _hookCurAngle++;
            if (_hookCurAngle > ANGLE_5) {
                _hookCurAngle = ANGLE_5;
                _hookWaveType = HOOK_WAVE_DOWN;
            }
        } else if (_hookWaveType == HOOK_WAVE_DOWN) {
            _hookCurAngle--;
            if (_hookCurAngle <= ANGLE_0) {
                _hookCurAngle = ANGLE_0;
                _hookWaveCount++;
                if (_state == ACT_WALK) {
                    if (_dir == DIR_LEFT) {
                        _hookAngleType = ANGLE_PLUS;
                    } else if (_dir == DIR_RIGHT) {
                        _hookAngleType = ANGLE_MINUS;
                    }
                } else {
                    if (_hookAngleType == ANGLE_PLUS) {
                        _hookAngleType = ANGLE_MINUS;
                    } else if (_hookAngleType == ANGLE_MINUS) {
                        _hookAngleType = ANGLE_PLUS;
                    }
                }
                _hookWaveType = HOOK_WAVE_UP;
            }
        } else {
            _hookCurAngle = ANGLE_0;
        }
    }
    
    if (_hookCurAngle > ANGLE_0 && _hookCurAngle<ANGLE_TAN.size()) {
        float dx = (_hookInitDy-_hookDy) * ANGLE_TAN[_hookCurAngle] / 3000;
        if (_hookAngleType == ANGLE_MINUS) {
            _hookDx = _hookInitDx - dx;
        } else if (_hookAngleType == ANGLE_PLUS) {
            _hookDx = _hookInitDx + dx;
        }
    } else {
        _hookDx = _hookInitDx;
    }
    
    _hook_anim->setPosition(ccp(_hookDx, _hookDy));
}

void Ship::draw()
{
    Actor::draw();
    if(_type == TYPE_AI){
        ccDrawColor4B(0xff, 0xff, 0, 0xff);
    }else{
        ccDrawColor4B(0xff, 0xff, 0xff, 0xff);
    }
        glLineWidth(2.0f);
    
    if(_state == ACT_CUT_LINE){
        
        ccDrawLine(ccp(_hookInitDx, _hookInitDy), ccp(_hookDx, _cut_hook_y));
        
        
        ccDrawLine(_cut_Pos, _cut_hook);
    }else if (_state == ACT_PULL){
    
        ccDrawLine(ccp(_hookInitDx, _hookInitDy), ccp(_pull_pos.x*this->getScaleX(),_pull_pos.y));
        
        
        
                
        ccDrawLine(ccp(_pull_pos.x*this->getScaleX(),_pull_pos.y),ccp(_hook_anim->getPositionX(),_hook_anim->getPositionY()));
                
                
        
        
    }else{
    
        ccDrawLine(ccp(_hookInitDx, _hookInitDy), ccp(_hookDx, _hookDy));
    }
//
//    CCRect*rect =_hook_anim->bodyRectInWorld();
//    
//    ccDrawRect(ccp(rect->origin.x, rect->origin.y), ccp(rect->origin.x+rect->size.width, rect->origin.y+rect->size.height));
}


void Ship::hookFish(Fish* fish) {
    hookFish();
    _fishSetHooked->addObject(fish);
}

void Ship::addItem(Item *it)
{
    hookFish();
    _items->addObject(it);
}

int Ship::getHookDx()
{
    return _hookDx;
}

int Ship::getHookDy()
{
    return _hookDy;
}

CCSprite* Ship::getHookAnim()
{
    return _hook_anim;
}

bool Ship::isState(int state)
{
    return _state == state;
}

void Ship::reapFishSetHooked(){
    
    for (int i = 0; i < _fishSetHooked->count(); i++) {
        Fish* fish = (Fish*) _fishSetHooked->objectAtIndex(i);
       
        fish->setDead(true);
        fish->setDeadType(Fish::HOOK_DEAD);
        fish->setShipID(this->getType());
        addVolume(fish->getVolume());
//        trunFish(fish);
        
       
        _hit++;
    }
    
    
    
    
    _fishSetHooked->removeAllObjects();
    
    
    for (int i = 0; i < _items->count(); ++i) {
        Item* item = (Item*) _items->objectAtIndex(i);
        item->setDead();
        _hit++;
    }
    
    GameScene::instance()->addHitFish(_hit);
    
    _items->removeAllObjects();
}

void Ship::trunFish(Fish* fish)
{
    fish->setVisible(false);
    
    _TurnFish -> addObject(fish);
    
}

float Ship::getX()
{
    return _x;
}

float Ship::getY()
{
    return _y;
}

void Ship::setw_Fish(Fish *fish)
{
    _w_Fish = fish;
}

Fish* Ship::getw_Fish()
{
    return _w_Fish;
}

void Ship::runUpDown()
{
//    CCMoveTo *move = CCMoveTo::create(0.6, CCPoint(_x, _y-2));
//    CCMoveTo *move2 = CCMoveTo::create(0.3, CCPoint(_x, _y));
//    CCMoveTo *move3 = CCMoveTo::create(0.3, CCPoint(_x, _y+2));
//    CCMoveTo *move4 = CCMoveTo::create(0.3, CCPoint(_x, _y+4));
//    CCMoveTo *move5 = CCMoveTo::create(0.3, CCPoint(_x, _y+2));
//    CCMoveTo *move6 = CCMoveTo::create(0.3, CCPoint(_x, _y));
    
    CCMoveBy* move = CCMoveBy::create(0.6, ccp(0, -2));
    CCMoveBy* move2 = CCMoveBy::create(0.9, ccp(0, 6));
    CCMoveBy* move3 = CCMoveBy::create(0.6, ccp(0, -4));
//    CCMoveBy* move4 = CCMoveBy::create(0.3, ccp(0, 2));
    
    
    CCSequence* sequence = CCSequence::create(move,move2,move3,NULL);
    
    CCRepeatForever* repeat = CCRepeatForever::create(sequence);
    
    this->runAction(repeat);
    
    
    
}

void Ship::runFall()
{
    this->stopAllActions();
    CCMoveTo* move = CCMoveTo::create(0.5, ccp(_x, _screenSize.height-SHIP_INIT_Y-20));
    
    CCEaseIn* ease = CCEaseIn::create(move, 1);
    
    CCMoveTo *move2 = CCMoveTo::create(0.3, ccp(_x, _screenSize.height-SHIP_INIT_Y));
    
    CCSequence* sequence = CCSequence::create(ease,move2,NULL);
    
    this->runAction(sequence);
}

void Ship::setShipTo(float px)
{
    
    if (!isCanMove() ) {
        return;
    }
    
    
        
    if (isHookOver() && !isShipFull()) {
        switchHookDir();
    }
    
    
    setState(Ship::ACT_WALK);
    
    setDesX(px);
}

void Ship::hook()
{
    if (isHookOver() && !isShipFull()) {
        switchHookDir();
    }
}

void Ship::setShipToNoHook(float px)
{
    
    if (!isCanMove() ) {
        return;
    }
    
    setState(Ship::ACT_WALK);
    
    setDesX(px);
}

void Ship::setStop(float time)
{
    _stopTime = time;
}

void Ship::shipOnAtk()
{
    _bHasFishHooked = false;
    
    for (int i = 0; i < _fishSetHooked->count(); ++i) {
        Fish* fish = (Fish*) _fishSetHooked->objectAtIndex(i);
        
        fish->setState(Fish::ACT_STATE_NORMAL);
        
        fish->setGo();
    }
    
    _fishSetHooked->removeAllObjects();
    
    
    for (int i = 0; i < _items->count(); ++i) {
        Item* item = (Item*) _items->objectAtIndex(i);
        item->setDead();
    }
    
    _items->removeAllObjects();
}

CCPoint Ship::getEatPos() 
{
    return CCPointMake(getPositionX()+ getBone("eat")->getWorldInfo()->x*this->getScaleX(),getPositionY()+ getBone("eat")->getWorldInfo()->y*this->getScaleY());
}

void Ship::setCutHookPos()
{
    _cut_hook = CCPointMake(_hookDx, _hookDy);
}



void Ship::setCutHookY(float y)
{
    _cut_hook_y = y-_y;
    
    _cut_Pos = CCPointMake(_hookDx, _cut_hook_y);
}

CCRect Ship::getHookLine()
{
    
//    CCLOG("fl : %i",abs( _hookDx-_hookInitDx));
    
    return CCRectMake(((_hookInitDx<_hookDx?_hookInitDx:_hookDx)*this->getScaleX()+_x), _hookDy+_y,Tools::int_abs( _hookDx-_hookInitDx), _hookInitDy-_hookDy);
}

CCRect Ship::getHookBody() 
{
    return CCRectMake(getPositionX()+(getHookAnim()->boundingBox().origin.x*getScaleX()), getPositionY()+getHookAnim()->boundingBox().origin.y, getHookAnim()->boundingBox().size.width, getHookAnim()->boundingBox().size.height);
}

void Ship::setPullPos(cocos2d::CCPoint pos)
{
    _pull_pos = pos;
}

void Ship::setX(float x)
{
    _x = x;
    setPositionX(_x);
}

void Ship::setY(float y)
{
    _y = y;
    setPositionY(_y);
}

void Ship::setXY(float x, float y)
{
    _x = x;
    _y = y;
    setPosition(_x, _y);
}

void Ship::addScore(int sc)
{
    _score+=sc;
}

int Ship::getType() const
{
    return _type;
}

int Ship::getHookDir() const
{
    return _hookDir;
}

void Ship::setMoveCD(int cd)
{
    _moveCD = _moveCD_MAX = cd;
}