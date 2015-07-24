//
//  MapElement.cpp
//  GetFish
//
//  Created by zhusu on 15/2/4.
//
//

#include "MapElement.h"
#include "Tools.h"

MapElement* MapElement::create(int star, int lev)
{
    MapElement* map = new MapElement();
    
    if(map && map->init(star,lev)) {
        map->autorelease();
        return map;
    }
    
    CC_SAFE_DELETE(map);
    return NULL;
}


MapElement::MapElement()
{
    
}

MapElement::~MapElement()
{
    
    
}

bool MapElement::init(int star,int lev)
{
    if(!CCSprite::init()) {
        return false;
    }
    
    CCSpriteBatchNode* batch = CCSpriteBatchNode::create("ui/ui_map.png");
    
    
    
    addChild(batch);
    
     _lev = lev;
   
    _back= CCSprite::createWithSpriteFrameName(("ui_mapkuang"+(Tools::intToString((lev/12)+1))+".png").c_str());
    
    batch->addChild(_back);
   
    
    for (int i = 0; i<star; ++i) {
        CCSprite* s = CCSprite::createWithSpriteFrameName("ui_star1.png");
        
            s->setPosition(ccp(i*37-37+i, 10+i*3));
        
        
        batch->addChild(s);
        
    }
    
    if (star == 3) {
        
    }
    
    int bigLev =(lev/12)+1;
    
    
   
    _levLabel = CCLabelAtlas::create( (Tools::intToString(bigLev)+ "-"+Tools::intToString(lev-(lev/12)*12+1)).c_str(), "ui/shuzi4.png", 21, 28, 43);
    
    _levLabel->setAnchorPoint(ccp(0.5, 0.5));
    
    _levLabel->setPosition(ccp(0, -25));
    //    _goldLabel->setPosition(CCPointMake(_screenSize.width*0.5, _screenSize.height*0.5));
    addChild(_levLabel);
    
    return true;
}

CCRect MapElement::getBody()
{
    return CCRectMake(this->getPositionX()+ _back->boundingBox().origin.x, this->getPositionY()+ _back->boundingBox().origin.y, _back->boundingBox().size.width, _back->boundingBox().size.height);
}

int MapElement::getLev()
{
    return _lev;
}