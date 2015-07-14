//
//  GameBegin.cpp
//  GetFish
//
//  Created by zhusu on 15/5/12.
//
//

#include "GameBegin.h"
#include "Common.h"
#include "Tools.h"

GameBegin* GameBegin::create(int score,int type,int fishID,int num)
{
    GameBegin* map = new GameBegin();
    
    if(map && map->init( score, type,fishID, num)) {
        map->autorelease();
        return map;
    }
    
    CC_SAFE_DELETE(map);
    return NULL;
}


GameBegin::GameBegin():_dead(false)
{
    
}

GameBegin::~GameBegin()
{
   
}

bool GameBegin::init(int score,int type,int fishID,int num)
{
    if(!CCLayer::init()) {
        
        return false;
    }
    
    
    CCSprite* back = CCSprite::createWithSpriteFrameName("ui_tishi_back.png");
    
    addChild(back);
    
    CCSprite* zi1 = CCSprite::createWithSpriteFrameName("ui_tishi_zi.png");
    
    zi1->setPosition(ccp(0, 100));
    
    addChild(zi1);
    
    CCSprite* zi2 = CCSprite::createWithSpriteFrameName("ui_tishi_zi2.png");
    
    zi2->setPosition(ccp(0, 50));
    
    addChild(zi2);
    
    CCSprite* zi3 = CCSprite::createWithSpriteFrameName("ui_tishi_zi3.png");
    
    zi3->setPosition(ccp(0, 0));
    
    addChild(zi3);
    
    CCSprite* zi4 = CCSprite::createWithSpriteFrameName(("ui_tishi_zi4_"+Tools::intToString(type+1)+".png").c_str());
    
    zi4->setPosition(ccp(0, -50));
    
    addChild(zi4);
    
    if(type == 0){
        
        zi4->setPosition(ccp(-50, -50));
        
        fish = CCArmature::create(("fish_"+Tools::intToString(fishID)).c_str());
        fish->setPosition(ccp(0, -50));
        fish->setScale(0.5);
        addChild(fish);
        
        
        _num = CCLabelAtlas::create((","+Tools::intToString(num)).c_str(), "ui/shuzi3.png", 14, 20, 43);
        _num->setAnchorPoint(ccp(0.5, 0.5));
        
        _num->setPosition(ccp(60, -50));
        
        addChild(_num);

    }
    
    _button_begin = ButtonWithSprite::create(BUTTON_GAME_BEGIN, "button_kaishi.png",0.8);
    
    _button_begin->setPosition(ccp(0, -110));
    
    addChild(_button_begin);
    
    _score = CCLabelAtlas::create( Tools::intToString(score).c_str(), "ui/shuzi3.png", 14, 20, 43);
    _score->setAnchorPoint(ccp(0.5, 0.5));
   
    _score->setPosition(ccp(55, 50));
    //    _goldLabel->setPosition(CCPointMake(_screenSize.width*0.5, _screenSize.height*0.5));
    addChild(_score);

    
    return true;
    
}

void GameBegin::touchesBegan(CCSet * touchs,CCEvent * event)
{
    _button_begin->touchesBegan(touchs, event);
}

void GameBegin::touchesCancelled(CCSet * touchs,CCEvent * event)
{
    _button_begin->touchesCancelled(touchs, event);
}

void GameBegin::touchesMoved(CCSet * touchs,CCEvent * event)
{
    _button_begin->touchesMoved(touchs, event);
}

void GameBegin::touchesEnded(CCSet * touchs,CCEvent * event)
{
    
    if(_button_begin->touchesEnded(touchs, event)){
        setDead(true);
    }
}