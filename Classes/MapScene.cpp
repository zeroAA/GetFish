//
//  MapScene.cpp
//  GetFish
//
//  Created by zhusu on 15/2/3.
//
//

#include "MapScene.h"
#include "Common.h"

const static int BACK_Z = -100;

const static int MAPUI_Z = -10;



MapScene::MapScene()
{
    
}

MapScene::~MapScene()
{
}

CCScene* MapScene::scene()
{
   
    CCScene *scene = CCScene::create();
    
   
    MapScene *layer = MapScene::create();
    
    
    scene->addChild(layer);
    
    
    return scene;
}


bool MapScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/button.plist");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/ui_map.plist");
    
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* back = CCSprite::create("bg/map_back.jpg");
    
    back->setPosition(ccp(_screenSize.width*0.5, _screenSize.height*0.5));
    
    addChild(back,BACK_Z);
    
    
    _mapUI = MapUI::create(3);
    
    addChild(_mapUI,MAPUI_Z);
    
    this->setTouchEnabled(true);

    return true;
}

void MapScene::onEnter()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, KEY_MAPSC, true);
    
    CCLayer::onEnter();
}

void MapScene::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CCLayer::onExit();
}

bool MapScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint pos = pTouch->getLocation();
    
    CCLOG("began");
    
    return true;
}

void MapScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
     CCLOG("Move");
}

void MapScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
     CCLOG("end");
}

