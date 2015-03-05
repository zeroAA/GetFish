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
    
   
    _levE = CCLayer::create();
    
    for(int k = 0 ; k<6;++k){
        for (int i = 0; i<4; ++i) {
            for (int j = 0; j<3; ++j) {
                
                MapElement* me = MapElement::create(3, j+i*3+k*12);
                me->setPosition(ccp(_screenSize.width*k+_screenSize.width*0.2+_screenSize.width*0.2*i, _screenSize.height-_screenSize.height*0.26-_screenSize.height*0.23*j));
                _levE->addChild(me);
            }
        }
    }

    _levE->setContentSize(ccp(_screenSize.width, _screenSize.height));
    _scroll = ScrollView::create(_screenSize,_levE);
    _scroll->setDirection(kCCScrollViewDirectionHorizontal);
    _scroll->setTouchPriority(KEY_MAP-1);
    
    _scroll->setPosition(ccp(0,0));
    _scroll->setMate(_screenSize.width,6,ScrollView::MATE_NORMAL);
    this->addChild(_scroll,1);

    
    _buttons = ButtonWithSpriteManage::create("ui/button.png");
    
    addChild(_buttons);
  
    
    ButtonWithSprite* _cup = ButtonWithSprite::create(BUTTON_MAP_CUP, "button_mapbei.png");
    
    _cup->setPosition(ccp(_screenSize.width*0.93, _screenSize.height*0.11));
    
    _buttons->addButton(_cup);
    
    this->setTouchEnabled(true);
    
    schedule(schedule_selector(MapUI::cycle));
    
    return true;
}

void MapUI::cycle(float delta)
{
//    CCLOG("x: %f",_scroll->getContentOffset().x);
    _levE->setPosition(ccp(_scroll->getContentOffset().x, 0));
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
//    CCPoint pos = pTouch->getLocation();
    
    return _buttons->toucheBegan(pTouch, pEvent);
}

void MapUI::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    _buttons->toucheMoved(pTouch, pEvent);
}

void MapUI::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    _buttons->toucheEnded(pTouch, pEvent);
}
