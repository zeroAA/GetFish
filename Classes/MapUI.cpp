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


MapUI::MapUI():_nowSelect(-1)
{
    
}

MapUI::~MapUI()
{
    CC_SAFE_RELEASE_NULL(_mapE);
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
        for (int i = 0; i<3; ++i) {
            for (int j = 0; j<4; ++j) {
                
                MapElement* me = MapElement::create(3, j+i*4+k*12);
                me->setPosition(ccp(_screenSize.width*k+_screenSize.width*0.2+_screenSize.width*0.2*j, _screenSize.height-_screenSize.height*0.26-_screenSize.height*0.23*i));
                _levE->addChild(me);
                _mapE->addObject(me);
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
    
    for (int i = 0; i<6; ++i) {
        CCSprite* dian = CCSprite::createWithSpriteFrameName("ui_dian1.png");
        
        dian->setPosition(ccp(_screenSize.width*0.5-125+i*50, _screenSize.height*0.10));
        
        addChild(dian);
        
    }
    _chooseIc = CCSprite::createWithSpriteFrameName("ui_dian2.png");
    setChooseIC();
    addChild(_chooseIc);
    return true;
}

void MapUI::cycle(float delta)
{
    
    _levE->setPosition(ccp(_scroll->getContentOffset().x, 0));
    setChooseIC();
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
    
    if (CCRectMake(_screenSize.width*0.1, _screenSize.height*0.2, _screenSize.width*0.8, _screenSize.height*0.6).containsPoint(pos)) {
        
        _nowSelect= 1000;
        return true;
    }
    
    if (_buttons->toucheBegan(pTouch, pEvent)) {
        return true;
    }
    
    return false;
}

void MapUI::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    _buttons->toucheMoved(pTouch, pEvent);
}

void MapUI::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    _buttons->toucheEnded(pTouch, pEvent);
    if (_nowSelect == 1000&&_scroll-> isMoveEnd()) {
        for (int i = _scroll->getNowPage()*12; i<_scroll->getNowPage()*12+12; ++i) {
            
            MapElement* me = (MapElement*) _mapE->objectAtIndex(i);
         
            if (CCRectMake(me->getBody().origin.x+(int)_scroll->getContentOffset().x, me->getBody().origin.y, me->getBody().size.width, me->getBody().size.height).containsPoint(pTouch->getLocation())) {
//                CCLOG("se : %i ",me->getLev());
                _nowSelect =me->getLev();
                return;
                
            }
        }
        
    }
    if(_nowSelect == 1000){
        _nowSelect =-1;

    }
}

void MapUI::setChooseIC()
{
    _chooseIc->setPosition(ccp(_screenSize.width*0.5-125+_scroll->getNowPage()*50, _screenSize.height*0.10));
}

int MapUI::getNowSelect() const
{
    return _nowSelect;
}

bool MapUI::isToGame() const
{
    
    return 0<=_nowSelect&&_nowSelect<_mapE->count();
    
//    return true;
}
