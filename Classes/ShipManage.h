//
//  ShipManage.h
//  GetFish
//
//  Created by zhusu on 14/12/19.
//
//

#ifndef __GetFish__ShipManage__
#define __GetFish__ShipManage__

#include "cocos2d.h"


#include "ActorManage.h"

USING_NS_CC;

class ShipManage : public ActorManage
{
public:
    CREATE_FUNC(ShipManage);
    
    ShipManage();
    
    virtual bool init();
    
    virtual ~ShipManage();
    
    void addShip(int type,const char* name,int ID,int sex);
    
    void addShip(int type,const char* name,int ID,int sex,int moveCD,int getTime,int getC);
    
protected:
    
    CCSize _screenSize;
};


#endif /* defined(__GetFish__ShipManage__) */
