//
//  Gif7.cpp
//  GetFish
//
//  Created by zhusu on 15/8/25.
//
//

#include "Gif7.h"
#include "Common.h"
#include "Tools.h"
#include "ButtonWithSprite.h"
#include "Data.h"
#include "GameSaveData.h"
#include "MapScene.h"

Gif7* Gif7::create(int type)
{
    Gif7* map = new Gif7();
    
    if(map && map->init(type)) {
        map->autorelease();
        return map;
    }
    
    CC_SAFE_DELETE(map);
    return NULL;
}

Gif7::Gif7()
{
    
}

Gif7::~Gif7()
{
}

bool Gif7::init(int type)
{
    if(CCLayer::init()) {
        
        _type = type;
        
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/gif7.plist");
        
        CCLayerColor* layerColor = CCLayerColor::create();
        layerColor->setPosition(ccp(-CCDirector::sharedDirector()->getWinSize().width*0.5, -CCDirector::sharedDirector()->getWinSize().height*0.5));
        layerColor->setColor(ccc3(0, 0, 0));
        layerColor->setOpacity(150);
        
        addChild(layerColor);
        
        
        CCSprite* back = CCSprite::createWithSpriteFrameName("ui_tishi_back.png");
        back->setScale(1.5);
        addChild(back);
        
        CCSprite* t = CCSprite::createWithSpriteFrameName("ui_gif7_t.png");
        t->setPosition(ccp(0, 210));
        addChild(t);
        
        _buttons = ButtonWithSpriteManage::create("ui/gif7.png");
        
        addChild(_buttons);
        
        for (int i = 0; i<3; ++i) {
            
            ButtonWithSprite* button = ButtonWithSprite::create(BUTTON_GIF_1+i,("ui_gif7_d"+Tools::intToString(i+1)+".png").c_str());
            button->setPosition(ccp(-200+i*200, 60));
//            button->setColor(ccc3(150, 150,150));
            if (GameSaveData::loadGif7(i)) {
                CCSprite* sp = CCSprite::createWithSpriteFrameName("ui_gif7_has.png");
                sp->setPosition(ccp(button->boundingBox().size.width*0.5, button->boundingBox().size.height*0.5));
                button->addChild(sp);
            }else if(day<i){
                button->setColor(ccc3(150, 150,150));
            }
            
            _buttons->addButton(button);
        }
        
        for (int i = 0; i<4; ++i) {
            ButtonWithSprite* button = ButtonWithSprite::create(BUTTON_GIF_1+i+3,("ui_gif7_d"+Tools::intToString(i+3+1)+".png").c_str());
            button->setPosition(ccp(-273+i*180, -140));
            
            if (GameSaveData::loadGif7(i+3)) {
                CCSprite* sp = CCSprite::createWithSpriteFrameName("ui_gif7_has.png");
                sp->setPosition(ccp(button->boundingBox().size.width*0.5, button->boundingBox().size.height*0.5));
                button->addChild(sp);
            }else if(day<i+3){
                button->setColor(ccc3(150, 150,150));
            }
            
            _buttons->addButton(button);
        }
        
        ButtonWithSprite* button = ButtonWithSprite::create(BUTTON_GIF_BACK,("ui_gif7_quxiao.png"),1.5,1.5);
        button->setPosition(ccp(310, 210));
        
        _buttons->addButton(button);
        
        this->setTouchEnabled(true);
        
        return true;
    }
    
    return false;
}

void Gif7::onEnter()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, KEY_NOGOLD, true);
    
    CCLayer::onEnter();
}

void Gif7::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("ui/gif7.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("ui/gif7.png");
    
    CCLayer::onExit();
}

bool Gif7::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    //    CCPoint pos = pTouch->getLocation();
    _buttons->toucheBegan(pTouch, pEvent);
    
    return true;
}

void Gif7::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    _buttons->toucheMoved(pTouch, pEvent);
    
}

void Gif7::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    _buttons->toucheEnded(pTouch, pEvent);
    
    if (_buttons->getNowID() == BUTTON_GIF_BACK){
        
        removeFromParentAndCleanup(true);
        
    }else{
        for (int i = 0; i<7; ++i) {
            
            if (_buttons->getNowID() == BUTTON_GIF_1+i&&!GameSaveData::loadGif7(i)&&i<=day) {
                
                if (_buttons->getNowID() == BUTTON_GIF_1) {
                    
                    player_gold+=2000;
                    GameSaveData::saveGoldData();
                    
                    MapScene::instance()->setGold();
                    
                }else if (_buttons->getNowID() == BUTTON_GIF_2) {
                    
                    getAll+=1;
                    GameSaveData::saveAllData();
                    
                    
                    
                }else if (_buttons->getNowID() == BUTTON_GIF_3) {
                    
                    player_gold+=3000;
                    GameSaveData::saveGoldData();
                    
                    MapScene::instance()->setGold();
                    
                    
                    
                }else if (_buttons->getNowID() == BUTTON_GIF_4) {
                    
                    getAll+=2;
                    GameSaveData::saveAllData();
                    
                    
                    
                }else if (_buttons->getNowID() == BUTTON_GIF_5) {
                    player_gold+=4000;
                    GameSaveData::saveGoldData();
                    
                    MapScene::instance()->setGold();
                    
                    
                    
                }else if (_buttons->getNowID() == BUTTON_GIF_6) {
                    getAll+=3;
                    GameSaveData::saveAllData();
                }else if (_buttons->getNowID() == BUTTON_GIF_7) {
                    player_gold+=5000;
                    GameSaveData::saveGoldData();
                    
                    MapScene::instance()->setGold();
                    
                }
                
                ButtonWithSprite* button = _buttons->getButton(i);
                CCSprite* sp = CCSprite::createWithSpriteFrameName("ui_gif7_has.png");
                sp->setPosition(ccp(button->boundingBox().size.width*0.5, button->boundingBox().size.height*0.5));
                button->addChild(sp);
                
                GameSaveData::saveGif7(i);
                MapScene::instance()->addMessage(1, "ui_ti_4.png");
                CCLOG("_type: %i",_type);
                if (_type == TYPE_AUTO_DEAD) {
                    
                    bool isExit = true;
                    
                    for (int j = 0; j<7; ++j) {
                        
                        if (!GameSaveData::loadGif7(j)&&day>=j) {
                            
                            CCLOG("j: %i",j);
                            isExit = false;
                            break;
                        }
                    }
                    
                    if (isExit) {
                        removeFromParentAndCleanup(true);
                    }
                }
                
                
                
            }
        }
        
    }
    
}