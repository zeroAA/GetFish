//
//  GameUI.cpp
//  GetFish
//
//  Created by zhusu on 15/1/27.
//
//

#include "GameUI.h"
#include "Common.h"

GameUI::GameUI()
{
    
}

GameUI::~GameUI()
{
}

bool GameUI::init()
{
    if(CCLayer::init()) {
        _screenSize = CCDirector::sharedDirector()->getWinSize();
        
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/button.plist");
        
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/game.plist");
        CCSprite* zuodi = CCSprite::createWithSpriteFrameName("ui_heibei.png");
        zuodi->setAnchorPoint(ccp(0, 1));
        zuodi->setPosition(ccp(_screenSize.width*0.005, _screenSize.height*0.98));
        
        addChild(zuodi);
        
        CCSprite* daojishi = CCSprite::createWithSpriteFrameName("ui_daojishi.png");
        
        daojishi->setAnchorPoint(ccp(0.5, 1));
        
        daojishi->setPosition(ccp(_screenSize.width*0.5, _screenSize.height));
        
        addChild(daojishi);
        
        CCNode* jindutiao = CCNode::create();
        jindutiao->setPosition(ccp(_screenSize.width*0.62, _screenSize.height*0.98));
        
        addChild(jindutiao);
        
        CCSprite* jindudi = CCSprite::createWithSpriteFrameName("ui_diaoyu1.png");
        
        jindudi->setAnchorPoint(ccp(0, 1));
        
        jindudi->setPosition(ccp(0, 0));
        
        jindutiao->addChild(jindudi);
        
        CCSprite* jindu = CCSprite::createWithSpriteFrameName("ui_lvshang.png");
        
        jindu->setAnchorPoint(ccp(0, 1));
        
        jindu->setPosition(ccp(2, -5));
        
        jindutiao->addChild(jindu);
        
        
        _buttons = ButtonWithSpriteManage::create("ui/button.png");
        
        addChild(_buttons);
        
        
             _buttons->addButton(BUTTON_GAME_PAUSE, "button_zanting.png", ccp(_screenSize.width*0.95, _screenSize.height*0.92));
        
       _buttons->addButton(BUTTON_GAME_PAUSE, "button_citie.png", ccp(_screenSize.width*0.06, _screenSize.height*0.09));
        
        return true;
    }
    return false;
}

void GameUI::onEnter()
{
    CCLayer::onEnter();
}

void GameUI::onExit()
{
    CCTextureCache::sharedTextureCache()->removeTextureForKey("ui/game.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("ui/game.plist");
    CCLayer::onExit();
}

bool GameUI::GameUItouchesBegan(CCSet * touchs,CCEvent * event)
{
    return _buttons->touchesBegan(touchs, event);
}

void GameUI::GameUItouchesMoved(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesMoved(touchs, event);
}

void GameUI::GameUItouchesCancelled(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesCancelled(touchs, event);
}

void GameUI::GameUItouchesEnded(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesEnded(touchs, event);
}

int GameUI::getNowButtonID() const
{
    return _buttons->getNowID();
}