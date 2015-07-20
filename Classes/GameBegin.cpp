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
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/button.plist");
    
    CCSprite* back = CCSprite::createWithSpriteFrameName("ui_tishi_back.png");
    
    addChild(back);
    
    CCSprite* wan = CCSprite::createWithSpriteFrameName("ui_c_wanmei.png");
    
    wan->setPosition(ccp(-60, -15));
    addChild(wan);
    
    CCSprite* star1 = CCSprite::createWithSpriteFrameName("ui_c_xing_di.png");
    
    star1->setRotation(-30);
    star1->setPosition(ccp(50, 30));
    addChild(star1);
    
    
    CCSprite* star2 = CCSprite::createWithSpriteFrameName("ui_c_xing_di.png");
   
    star2->setPosition(ccp(120, 40));
    addChild(star2);
    
    CCSprite* star3 = CCSprite::createWithSpriteFrameName("ui_c_xing_di.png");
    
    star3->setRotation(30);
    star3->setPosition(ccp(190, 30));
    addChild(star3);
    
    CCSprite* zi0 = CCSprite::createWithSpriteFrameName("ui_tishi_guanka.png");
    zi0->setAnchorPoint(ccp(0, 0));
    zi0->setPosition(ccp(-back->boundingBox().size.width*0.5+15, 122));
    addChild(zi0);
    CCSprite* zi1 = CCSprite::createWithSpriteFrameName("ui_tishi_zi.png");
    zi1->setAnchorPoint(ccp(0, 0));
    zi1->setPosition(ccp(-back->boundingBox().size.width*0.5+20, 60));
    
    addChild(zi1);
    
    CCSprite* zi2 = CCSprite::createWithSpriteFrameName("ui_tishi_zi2.png");
    zi2->setAnchorPoint(ccp(0, 0));
    zi2->setPosition(ccp(-back->boundingBox().size.width*0.5+25, 25));
    
    addChild(zi2);
    
    CCSprite* zi3 = CCSprite::createWithSpriteFrameName("ui_tishi_zi3.png");
    zi3->setAnchorPoint(ccp(0, 0));
    zi3->setPosition(ccp(-back->boundingBox().size.width*0.5+20, -30));
    
    addChild(zi3);
    
    CCSprite* zi4 = CCSprite::createWithSpriteFrameName(("ui_tishi_zi4_"+Tools::intToString(type+1)+".png").c_str());
    zi4->setAnchorPoint(ccp(0, 0));
    zi4->setPosition(ccp(-back->boundingBox().size.width*0.5+20, -60));
    
    addChild(zi4);
    
    if(type == 0){
        
        zi4->setPosition(ccp(-back->boundingBox().size.width*0.5+30, -80));
        
        fish = CCArmature::create(("fish_"+Tools::intToString(fishID)).c_str());
        fish->setPosition(ccp(-back->boundingBox().size.width*0.5+100, -70));
        fish->setScale(0.5);
        addChild(fish);
        
        
        _num = CCLabelAtlas::create((","+Tools::intToString(num)).c_str(), "ui/shuzi3.png", 14, 20, 43);
        _num->setAnchorPoint(ccp(0, 0));
        
        _num->setPosition(ccp(-back->boundingBox().size.width*0.5+130, -80));
        
        addChild(_num);

    }
    
    _button_begin = ButtonWithSprite::create(BUTTON_GAME_BEGIN, "button_kaishi.png",0.8);
    
    _button_begin->setPosition(ccp(100, -132));
    
    addChild(_button_begin);
    
    _score = CCLabelAtlas::create( Tools::intToString(score).c_str(), "ui/shuzi3.png", 14, 20, 43);
    _score->setAnchorPoint(ccp(0, 0));
   
    _score->setPosition(ccp(-back->boundingBox().size.width*0.5+zi2->boundingBox().size.width+30, 25));
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