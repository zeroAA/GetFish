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

const static int CHOOSE_Z = -5;

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
    
     CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/ui_icon.plist");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/ui_map.plist");
    
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* back = CCSprite::create("bg/map_back.jpg");
    
    back->setPosition(ccp(_screenSize.width*0.5, _screenSize.height*0.5));
    
    addChild(back,BACK_Z);
    
    
//    _mapUI = MapUI::create(3);
//    
//    addChild(_mapUI,MAPUI_Z);
    
    _choose = ChoosePlayer::create();
    addChild(_choose,CHOOSE_Z);
    
    CCSprite* _goldback = CCSprite::createWithSpriteFrameName("ui_qianback.png");
    _goldback->setAnchorPoint(ccp(0, 0.5));
    
    _goldback ->setPosition(ccp(_screenSize.width*0.06, _screenSize.height*0.93));
    
    addChild(_goldback);
    
    
    CCSprite* _gold = CCSprite::createWithSpriteFrameName("ui_jinbi.png");
    _gold->setAnchorPoint(ccp(0.5, 0.5));
    _gold->setPosition(ccp(_goldback->getPositionX(), _goldback->getPositionY()));
    
    addChild(_gold);
    
    
    _buttons = ButtonWithSpriteManage::create("ui/button.png");
    
    addChild(_buttons);
    
    
    
    
    ButtonWithSprite* _shop = ButtonWithSprite::create(BUTTON_MAP_SHOP, "button_jia.png");
    _shop->setAnchorPoint(ccp(0, 0.5));
    _shop->setPosition(ccp(_goldback->getPositionX()+_goldback->boundingBox().size.width-_shop->boundingBox().size.width, _goldback->getPositionY()));
    
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


    
//    _screenSize = CCDirector::sharedDirector()->getWinSize();
//    
//    CCSprite* back = CCSprite::create("main/main.jpg");
//    
//    back->setPosition(ccp(_screenSize.width*0.5, _screenSize.height*0.5));
//    
//    addChild(back);
//    
//    CCFadeIn* in = CCFadeIn::create(1);
//    CCFadeOut* out = CCFadeOut::create(1);
//    
//    CCSequence* sq = CCSequence::create(out,in,NULL);
//    
//    CCRepeatForever* re = CCRepeatForever::create(sq);
//    
//    CCSprite* zi = CCSprite::create("main/mainzi.png");
//    
//    zi->runAction(re);
//    
//    zi->setPosition(ccp(_screenSize.width*0.5, _screenSize.height*0.2));
//    
//    addChild(zi);
    
        
    
//    this->setTouchEnabled(true);

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
    return _buttons->toucheBegan(pTouch, pEvent);
}

void MapScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
     _buttons->toucheMoved(pTouch, pEvent);
}

void MapScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
     _buttons->toucheEnded(pTouch, pEvent);

    
//    removeAllChildren();
//    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f, LoadingScreen::create(KScreenGame, 0)));
}

