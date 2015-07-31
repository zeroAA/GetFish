//
//  Shell.h
//  GetFish
//
//  Created by zhusu on 15/3/11.
//
//

#ifndef __GetFish__Shell__
#define __GetFish__Shell__

#include "cocos2d.h"
#include "Item.h"
#include "Actor.h"

USING_NS_CC;

class Shell : public Actor
{
public:
    const static int STATE_OPEN = 0;
    const static int STATE_CLOSE = 1;

    static Shell* create(const char* name,CCPoint pos,std::vector<int> item,int openTime,int closeTime);
    
    virtual bool init(const char* name,CCPoint pos,std::vector<int> item,int openTime,int closeTime);
    
    Shell();
    
    virtual ~Shell();
    
    virtual void cycle(float delta);
    
private:
    
    void addItem(int type,int v);
    
protected:
    
    int _openTime;
    
    int _closeTime;
    
    int _openTimeMax;
    
    int _closeTimeMax;
    
    int _state;
    
    std::vector<int> _itemInfo;
    
};

#endif /* defined(__GetFish__Shell__) */
