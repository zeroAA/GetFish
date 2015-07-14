//
//  Shell.cpp
//  GetFish
//
//  Created by zhusu on 15/3/11.
//
//

#include "Shell.h"

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
            playWithIndex(1);
        }
        
        
    }else if (_state == STATE_OPEN){
        _openTime--;
        
       
        
        if (_openTime <=0) {
            _openTime = _openTimeMax;
            _state = STATE_CLOSE;
            playWithIndex(3);
        }
    }
    
}
