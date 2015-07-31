//
//  MapElement.h
//  GetFish
//
//  Created by zhusu on 15/2/4.
//
//

#ifndef __GetFish__MapElement__
#define __GetFish__MapElement__

#include "cocos2d.h"

USING_NS_CC;

class MapElement : public CCSprite
{
public:
    
    static MapElement* create(int star,int lev);
    
    virtual bool init(int star,int lev);
    
    MapElement();
    
    virtual ~MapElement();
    
    CCRect getBody() ;
    
    int getLev();
    
    int getStar();
protected:
    
    int _lev;
    
    int _star;
    
    CCSprite* _back;
    
    CCLabelAtlas* _levLabel;

};

#endif /* defined(__GetFish__MapElement__) */
