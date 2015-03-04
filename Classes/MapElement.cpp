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
    
    CCSprite* di = CCSprite::createWithSpriteFrameName(("ui_mapkuang"+(Tools::intToString((lev/12)+1))+".png").c_str());
    
    batch->addChild(di);
    
    
    
    for (int i = 0; i<star; ++i) {
        CCSprite* s = CCSprite::createWithSpriteFrameName("ui_star1.png");
        
            s->setPosition(ccp(i*37-37+i, 10+i*3));
        
        
        batch->addChild(s);
        
    }
    
    if (star == 3) {
        
    }
    
    return true;
}