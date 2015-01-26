//
//  Actor.cpp
//  GetFish
//
//  Created by zs on 14-4-18.
//
//

#include "Actor.h"
#include "Common.h"
#include "GameScene.h"
#include "Tools.h"


Actor* Actor::create(const char *name)
{
    Actor* pRet = new Actor();
    
    if(pRet && pRet->init(name)) {
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
}

Actor::Actor():_state(STATE_NORMAL),_isAutoDead(true)
{
    
}

Actor::~Actor()
{
}
bool Actor::init(const char *name)
{
    if(CCArmature::init(name)) {
        
        _screenSize = CCDirector::sharedDirector()->getWinSize();
        
        //        schedule(schedule_selector(Actor::cycle));
        
       
        
        setBodyPonit();
        
        return true;
    }
    
    return false;
}

void Actor::setState(int state)
{
    _state = state;
}

int Actor::getState() const
{
    return _state;
}

std::string Actor::getCurrentMovementID()
{
    
    return getAnimation()->m_strMovementID;
}

void Actor::onEnter()
{
    CCArmature::onEnter();
}

void Actor::onExit()
{
    CCArmature::onExit();
}

void Actor::cycle(float delta)
{
    CCLOG("actir");
}

void Actor::actorCycle(float delta)
{
    
    //    if (_isAutoDead) {
    //        if (this->getPositionY()+getBodyRect().size.height<0||
    //            this->getPositionY()-getBodyRect().size.height>_screenSize.height) {
    //            _state = STATE_DEAD;
    //            return;
    //        }
    //    }
    
    
}

CCRect Actor::getBodyRect()
{
    return getBodyRect(0);
}

CCRect Actor::getBodyRect(int indext)
{
    if (_body1.size() == 0) {
        CCLOG("%s body is none!",getName().c_str());
        return CCRectMake(0, 0, 0, 0);
    }
    
    if (indext>=_body1.size()) {
        CCLOG("%s indext is over!",getName().c_str());
        return CCRectMake(0, 0, 0, 0);
    }
    
    float x = (int)_body1[indext].x+getPositionX();
    float y = (int)_body1[indext].y+getPositionY();
    float w = (int)_body2[indext].x-(int)_body1[indext].x;
    float h = (int)_body1[indext].y-(int)_body2[indext].y;
    
    y = y-h;
    
    return CCRectMake(x, y, w, h);
}

void Actor::setBodyPonit()
{
    _body1.clear();
    _body2.clear();
    for(int i = 1 ; i < 100;++i){
        
        string str = "body"+Tools::intToString(i)+"_1";
        
      
        
        if (this->getBone(str.c_str())) {
            
            
           
            
            _body1.push_back(CCPointMake((int)(this->getBone(str.c_str())->getWorldInfo()->x*this->getScaleX()), this->getBone(str.c_str())->getWorldInfo()->y*this->getScaleY()));
            
            string str2 = "body"+Tools::intToString(i)+"_2";
            _body2.push_back(CCPointMake((int)(this->getBone(str2.c_str())->getWorldInfo()->x*this->getScaleX()), this->getBone(str2.c_str())->getWorldInfo()->y*this->getScaleY()));
        }
        else{
            break;
        }
        
    }
    
    
    //    else{
    //        CCLOG("%s no have body bone",getName().c_str());
    //    }
    
    //    this->boundingBox();
    
    boundingBox();
    
}

//void Actor::draw()
//{
//    CCLOG("????!!!");
//}

void Actor::setAutoDead(bool isDead)
{
    _isAutoDead = isDead;
}

void Actor::play(const char *animationName)
{
    getAnimation()->play(animationName);
    setBodyPonit();
}

void Actor::playWithIndex(int index)
{
    getAnimation()->playWithIndex(index);
    setBodyPonit();
}
