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
    
    _star = star;
    
    _lev = lev;
    
    CCSpriteBatchNode* batch = CCSpriteBatchNode::create("ui/ui_map.png");
    
    addChild(batch);
   
    _back= CCSprite::createWithSpriteFrameName(("ui_mapkuang"+(Tools::intToString((lev/12)+1))+".png").c_str());
    
    batch->addChild(_back);
    int s =star-1;
    if (s>3) {
        s=3;
    }
    for (int i = 0; i<s; ++i) {
        CCSprite* s = CCSprite::createWithSpriteFrameName("ui_star1.png");
        
            s->setPosition(ccp(i*37-37+i, 10+i*3));
        
        
        batch->addChild(s);
        
    }
    
    if (star == 5) {
        CCSprite* pf = CCSprite::createWithSpriteFrameName("ui_mapp.png");
        pf->setPosition(ccp(-26, 2));
        batch->addChild(pf);
    }
    
    if (star == 0) {
//        CCSprite* di = CCSprite::createWithSpriteFrameName("ui_mapkuangbantou.png");
//        di->setPosition(ccp(0, 0));
//        batch->addChild(di);
        
        CCSprite* suo = CCSprite::createWithSpriteFrameName("ui_mapsuo.png");
        suo->setPosition(ccp(0, 0));
        batch->addChild(suo);
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

int MapElement::getStar()
{
    return _star;
}