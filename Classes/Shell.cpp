//
//  Shell.cpp
//  GetFish
//
//  Created by zhusu on 15/3/11.
//
//

#include "Shell.h"
#include "Tools.h"
#include "GameScene.h"

Shell* Shell::create(const char* name,CCPoint pos,std::vector<int> item,int openTime,int closeTime)
{
    Shell* shell = new Shell();
    
    if(shell && shell->init(name,pos,  item, openTime, closeTime)) {
        shell->autorelease();
        return shell;
    }
    
    CC_SAFE_DELETE(shell);
    return NULL;
}



Shell::Shell():_closeTimeMax(120),_openTimeMax(120), _closeTime(120),_openTime(120),_state(STATE_CLOSE)
{
    
}

Shell::~Shell()
{
    
}



bool Shell::init(const char* name,CCPoint pos,std::vector<int> item,int openTime,int closeTime)
{
    
    if(!Actor::init(name)) {
        
        return false;
    }
    
    _itemInfo = item;
    _openTimeMax = _openTime = openTime;
    _closeTimeMax = _closeTime = closeTime;
    
//    addChild(CCSprite::createWithSpriteFrameName("item_2.png"));
    
    setPosition(pos);
    
    return true;
    
}

void Shell::cycle(float delta)
{
    
    if (_state == STATE_CLOSE) {
        _closeTime--;
        
        if (_closeTime <=0) {
            _closeTime = _closeTimeMax;
            _state = STATE_OPEN;
            playWithIndex(2);
            
            int indext = Tools::randomIntInRange(0, _itemInfo.size()*0.5);
            
            addItem(_itemInfo[indext*2+1], _itemInfo[indext*2]);
        }
        
        
    }else if (_state == STATE_OPEN){
        _openTime--;
        
        if (_openTime <=0) {
            _openTime = _openTimeMax;
            _state = STATE_CLOSE;
            playWithIndex(0);

        }
    }
    
}

void Shell::addItem(int type , int v)
{
    
    GameScene::instance()->addItem(("item_"+Tools::intToString(type)).c_str(), ccpAdd(this->getPosition(), ccp(0, 50)), type,v,_openTimeMax);
}
