//
//  MapUI.cpp
//  GetFish
//
//  Created by zhusu on 15/2/3.
//
//

#include "MapUI.h"
#include "Common.h"

const int MAPE_Z = -10;


MapUI* MapUI::create(int lev)
{
    MapUI* map = new MapUI();
    
    if(map && map->init(lev)) {
        map->autorelease();
        return map;
    }
    
    CC_SAFE_DELETE(map);
    return NULL;
}


MapUI::MapUI()
{
    
}

MapUI::~MapUI()
{
    
    if (_mapE) {
        _mapE->release();
        _mapE = NULL;
    }
}

bool MapUI::init(int lev)
{
    if(!CCLayer::init()) {
        return false;
    }
    
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    
    _mapE = CCArray::create();
    
    _mapE->retain();
    
   
    
    
    for (int i = 0; i<4; ++i) {
        for (int j = 0; j<3; ++j) {
            MapElement* me = MapElement::create(3, 2);
            me->setPosition(ccp(_screenSize.width*0.2+_screenSize.width*0.2*i, _screenSize.height-_screenSize.height*0.23-_screenSize.height*0.25*j));
            addChild(me);
        }
    }
    
    
    this->setTouchEnabled(true);
    
    return true;
}

void MapUI::onEnter()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, KEY_MAP, true);
    
    CCLayer::onEnter();
}

void MapUI::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CCLayer::onExit();
}

bool MapUI::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint pos = pTouch->getLocation();
    
    CCLOG("mapbegan");
    
    return true;
}

void MapUI::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    CCLOG("mapMove");
}

void MapUI::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCLOG("mapend");
}
