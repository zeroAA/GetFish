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
            me->setPosition(ccp(_screenSize.width*0.2+_screenSize.width*0.2*i, _screenSize.height-_screenSize.height*0.26-_screenSize.height*0.23*j));
            addChild(me);
        }
    }
    
    
    
    
    CCSprite* _goldback = CCSprite::createWithSpriteFrameName("ui_jinback.png");
    _goldback->setAnchorPoint(ccp(0, 0.5));
    _goldback ->setPosition(ccp(_screenSize.width*0.04, _screenSize.height*0.93));
    
    addChild(_goldback);

    
    CCSprite* _gold = CCSprite::createWithSpriteFrameName("ui_jinbi.png");
    _gold->setAnchorPoint(ccp(0, 0.5));
    _gold->setPosition(ccp(_goldback->getPositionX()-20, _goldback->getPositionY()));
    
    addChild(_gold);
    
    
    _buttons = ButtonWithSpriteManage::create("ui/button.png");
    
    addChild(_buttons);
    
    
    ButtonWithSprite* _cup = ButtonWithSprite::create(BUTTON_MAP_CUP, "button_mapbei.png");
    
    _cup->setPosition(ccp(_screenSize.width*0.93, _screenSize.height*0.11));
    
    _buttons->addButton(_cup);
    
    ButtonWithSprite* _shop = ButtonWithSprite::create(BUTTON_MAP_SHOP, "button_jia.png");
    _shop->setAnchorPoint(ccp(0, 0.5));
    _shop->setPosition(ccp(_goldback->getPositionX()+100, _goldback->getPositionY()));
    
    _buttons->addButton(_shop);
    
    ButtonWithSprite* _set = ButtonWithSprite::create(BUTTON_MAP_SET, "button_shezhi.png");
    
    _set->setPosition(ccp(_screenSize.width*0.95, _screenSize.height*0.92));
    
    _buttons->addButton(_set);
    
    ButtonWithSprite* _back = ButtonWithSprite::create(BUTTON_MAP_BACK, "button_fanhui.png");

    _back->setPosition(ccp(_screenSize.width*0.06, _screenSize.height*0.08));
    
    _buttons->addButton(_back);
    
    ButtonWithSprite* _shop2 = ButtonWithSprite::create(BUTTON_MAP_SHOP, "button_shangcheng.png");
    
    _shop2->setPosition(ccp(_screenSize.width*0.85, _screenSize.height*0.92));
    
//    _buttons->addChild(_shop2);
    
    ButtonWithSprite* _vip = ButtonWithSprite::create(BUTTON_MAP_VIP, "button_libao.png");
    
    _vip->setPosition(ccp(_screenSize.width*0.8, _screenSize.height*0.92));
    
    _buttons->addButton(_vip);
    
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
//    CCPoint pos = pTouch->getLocation();
    
    _buttons->toucheBegan(pTouch, pEvent);
    
    
    
    return true;
}

void MapUI::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    _buttons->toucheMoved(pTouch, pEvent);
}

void MapUI::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    _buttons->toucheEnded(pTouch, pEvent);
}
