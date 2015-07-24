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
    
    CCLOG("type : %i",type);
    
    CCSprite* back = CCSprite::createWithSpriteFrameName("ui_tishi_back.png");
    
    addChild(back);
    
    CCSprite* back1 = CCSprite::createWithSpriteFrameName("ui_c_tishi.png");
    back1->setPosition(ccp(back->boundingBox().size.width*0.5+back1->boundingBox().size.width*0.5-5, -2));
    addChild(back1);
    
    int tinum = 2;
    
    CCSprite* tishi1 = CCSprite::create("ui/ui_ctishi_1.png");
    tishi1->setPosition(ccp(back1->getPositionX(), back1->getPositionY()+40*(tinum-1)));
    addChild(tishi1);
    
    if (tinum>1) {
        CCSprite* tishi2 = CCSprite::create("ui/ui_ctishi_2.png");
        tishi2->setPosition(ccp(back1->getPositionX(), back1->getPositionY()-90));
        addChild(tishi2);
    }
    
    
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
    CCSprite* zi2;
    
    if (type == 3){
        zi2 = CCSprite::createWithSpriteFrameName("ui_tishi_zi4_4.png");
    }else{
        zi2 = CCSprite::createWithSpriteFrameName("ui_tishi_zi2.png");
    }
    
    zi2->setAnchorPoint(ccp(0, 0));
    zi2->setPosition(ccp(-back->boundingBox().size.width*0.5+25, 25));
    
    addChild(zi2);
    
    CCSprite* zi3 = CCSprite::createWithSpriteFrameName("ui_tishi_zi3.png");
    zi3->setAnchorPoint(ccp(0, 0));
    zi3->setPosition(ccp(-back->boundingBox().size.width*0.5+20, -30));
    
    addChild(zi3);
    
    CCSprite* zi4 = CCSprite::createWithSpriteFrameName(("ui_tishi_zi4_"+Tools::intToString(type+1)+".png").c_str());
    zi4->setAnchorPoint(ccp(0, 0));
    zi4->setPosition(ccp(-back->boundingBox().size.width*0.5+25, -80));
    
    addChild(zi4);
    
    if(type == 0){
        
        zi4->setPosition(ccp(-back->boundingBox().size.width*0.5+25, -80));
        fish = CCArmature::create(("fish_"+Tools::intToString(fishID)).c_str());
        fish->setPosition(ccp(-back->boundingBox().size.width*0.5+100, -70));
        fish->setScale(0.5);
        addChild(fish);
        
        
        _num = CCLabelAtlas::create((","+Tools::intToString(num)).c_str(), "ui/shuzi5.png", 12, 15, 43);
        _num->setAnchorPoint(ccp(0, 0));
        
        _num->setPosition(ccp(-back->boundingBox().size.width*0.5+130, -78));
        
        addChild(_num);

    }else if(type == 3){
        _num = CCLabelAtlas::create((","+Tools::intToString(num)).c_str(), "ui/shuzi5.png", 12, 15, 43);
        _num->setAnchorPoint(ccp(0, 0));
        
        _num->setPosition(ccp(-back->boundingBox().size.width*0.5+zi2->boundingBox().size.width+30, -78));
        addChild(_num);
    }
    
    _buttons = ButtonWithSpriteManage::create("ui/button.png");
    
    addChild(_buttons);
    
    ButtonWithSprite* button_begin = ButtonWithSprite::create(BUTTON_GAME_BEGIN, "button_kaishi.png",0.8);
    
    button_begin->setPosition(ccp(120, -132));
    
    _buttons->addButton(button_begin);
    
    
    ButtonWithSprite* button_back = ButtonWithSprite::create(BUTTON_GAME_BACK, "button_fanhui2.png",0.8);
    
    button_back->setPosition(ccp(-120, -132));
    
    _buttons->addButton(button_back);
    if (type != 3){
        
        _score = CCLabelAtlas::create( Tools::intToString(score).c_str(), "ui/shuzi5.png", 12, 15, 43);
        _score->setAnchorPoint(ccp(0, 0));
        
        _score->setPosition(ccp(-back->boundingBox().size.width*0.5+zi2->boundingBox().size.width+30, 28));
        addChild(_score,100);
        
    }

    
    return true;
    
}

void GameBegin::touchesBegan(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesBegan(touchs, event);
}

void GameBegin::touchesCancelled(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesCancelled(touchs, event);
}

void GameBegin::touchesMoved(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesMoved(touchs, event);
}

void GameBegin::touchesEnded(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesEnded(touchs, event);
    
    if(_buttons->getNowID() == BUTTON_GAME_BEGIN){
        setDead(DEAD_TYPE_TOGAME);
    }else if(_buttons->getNowID() == BUTTON_GAME_BACK){
        setDead(DEAD_TYPE_BACK);
    }
}