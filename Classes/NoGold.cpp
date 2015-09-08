//
//  NoGold.cpp
//  GetFish
//
//  Created by zhusu on 15/8/17.
//
//

#include "NoGold.h"
#include "Common.h"
#include "Tools.h"
#include "Data.h"
#include "MapScene.h"
#include "GameSaveData.h"
#include "GameScene.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "IOSiAP_Bridge.h"
#endif

NoGold* NoGold::create(int type)
{
    NoGold* map = new NoGold();
    
    if(map && map->init(type)) {
        map->autorelease();
        return map;
    }
    
    CC_SAFE_DELETE(map);
    return NULL;
}

NoGold::NoGold()
{
    
}

NoGold::~NoGold()
{
}

bool NoGold::init(int type)
{
    if(CCLayer::init()) {
        
        CCLayerColor* layerColor = CCLayerColor::create();
        layerColor->setPosition(ccp(-CCDirector::sharedDirector()->getWinSize().width*0.5, -CCDirector::sharedDirector()->getWinSize().height*0.5));
        layerColor->setColor(ccc3(0, 0, 0));
        layerColor->setOpacity(150);
        
        addChild(layerColor);
        
        _type = type;
        
        CCSprite* back = CCSprite::createWithSpriteFrameName("ui_tishi_back.png");
        
        addChild(back);
        if(_type>=TYPE_KAI_2){
            
            CCSprite* name = CCSprite::createWithSpriteFrameName("ui_noname_10.png");
            
            name->setPosition(ccp(0, 140));
            
            addChild(name);
            
            CCSprite* zi = CCSprite::createWithSpriteFrameName(("ui_nozi_"+Tools::intToString(type)+".png").c_str());
            zi->setPosition(ccp(0, 50));
            addChild(zi);
            
            CCSprite* zi1 = CCSprite::createWithSpriteFrameName("ui_nozi_100.png");
            zi1->setPosition(ccp(0, -30));
            addChild(zi1);
            
        }else{
        
        CCSprite* name = CCSprite::createWithSpriteFrameName(("ui_noname_"+Tools::intToString(type)+".png").c_str());
        
        name->setPosition(ccp(0, 140));
        
        addChild(name);
        
        CCSprite* zi = CCSprite::createWithSpriteFrameName(("ui_nozi_"+Tools::intToString(type)+".png").c_str());
        
        addChild(zi);
        }
        
        _buttons = ButtonWithSpriteManage::create("ui/button.png");
        this->addChild(_buttons);
        _buttons->addButton(BUTTON_NOGOLD_BACK, "button_fanhui2.png", ccp(-144, -128));
        
        if (type == TYPE_GOLD) {
            _buttons->addButton(BUTTON_NOGOLD_GET, "button_buyGold.png", ccp(144, -128));
        }else if(_type>=TYPE_KAI_2){
            _buttons->addButton(BUTTON_NOGOLD_GET, "button_open.png", ccp(144, -128));
        }else{
            _buttons->addButton(BUTTON_NOGOLD_GET, "button_buyGet.png", ccp(144, -128));
        }
        
        
        this->setTouchEnabled(true);
        
        return true;
    }
    
    return false;
}

void NoGold::onEnter()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, KEY_NOGOLD, true);
    
    CCLayer::onEnter();
}

void NoGold::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CCLayer::onExit();
}

bool NoGold::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    //    CCPoint pos = pTouch->getLocation();
    _buttons->toucheBegan(pTouch, pEvent);
    
    return true;
}

void NoGold::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    _buttons->toucheMoved(pTouch, pEvent);
    
}

void NoGold::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    _buttons->toucheEnded(pTouch, pEvent);
    
    if (_buttons->getNowID() == BUTTON_NOGOLD_BACK) {
        removeFromParentAndCleanup(true);
        CCDirector::sharedDirector()->resume();
    }else if (_buttons->getNowID() == BUTTON_NOGOLD_GET){
        
        removeFromParentAndCleanup(true);
        
        if (_type == TYPE_GOLD) {
            #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
            MapScene::instance()->addBuy();
            IOSiAP_Bridge::instance()->requestProducts(IOSiAP_Bridge::IAP_BIG_GOLD);
            #else
            player_gold+=75000;
            
            MapScene::instance()->setGold();
            
            GameSaveData::saveGoldData();
            #endif
        }else if (_type == TYPE_GET){
            CCDirector::sharedDirector()->resume();
            
            if (player_gold>=3000) {
                player_gold-=3000;
                GameSaveData::saveGoldData();
                getAll+=1;
                GameSaveData::saveAllData();
                GameScene::instance()->setCiTie(getAll);
            }
        }else if (_type == TYPE_GOLD_GET){
            #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
            GameScene::instance()->addBuy();
            IOSiAP_Bridge::instance()->requestProducts(IOSiAP_Bridge::IAP_GAME_BIG_GOLD);
#else
                player_gold+=75000;
                player_gold-=3000;
                GameSaveData::saveGoldData();
                getAll+=1;
            
                GameSaveData::saveAllData();
                GameScene::instance()->setCiTie(getAll);
#endif
            
        }else if(_type >= TYPE_KAI_2){
    #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
            MapScene::instance()->addBuy();
            IOSiAP_Bridge::instance()->requestProducts(IOSiAP_Bridge::IAP_OPEN_VIP);
    #else
            
            for (int i = 0; i<72; ++i) {
                if (GameSaveData::loadLevelData(i)<=0) {
                    GameSaveData::saveLevelData(i, 1);
                }
            }
            
            for (int i = 0; i<6; ++i) {
                GameSaveData::savePlayer(i);
            }
            
            getAll+=99;
            
            GameSaveData::saveAllData();
            GameSaveData::saveVipGif();
            
            select_player = 5;
                
            MapScene::instance()->changeToMap();
    #endif
        }
    }
}