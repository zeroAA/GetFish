//
//  SucEnd.cpp
//  GetFish
//
//  Created by zhusu on 15/7/24.
//
//

#include "SucEnd.h"
#include "Common.h"
#include "GameScene.h"

SucEnd::SucEnd():_dead(-1)
{
    
}

SucEnd::~SucEnd()
{
}

bool SucEnd::init()
{
    if(CCLayer::init()) {
        
        CCSize win = CCDirector::sharedDirector()->getWinSize();
        CCNode* node = CCNode::create();
        
        node->setPosition(ccp(win.width*0.5, win.height*0.5));
        addChild(node);
        
        CCSprite* back = CCSprite::createWithSpriteFrameName("ui_tishi_back.png");
        
        node->addChild(back);
        
        
        CCSprite* name = CCSprite::createWithSpriteFrameName("ui_c_shengli.png");
        name->setPosition(ccp(0, 140));
        node->addChild(name);
        
        
        CCSprite* xing = CCSprite::createWithSpriteFrameName("ui_c_xing.png");
        xing->setScale(5);
        xing->setRotation(-30);
        xing->setPosition(ccp(-100, 30));
        CCRotateBy* rb = CCRotateBy::create(0.5, 360);
        CCScaleTo* sc = CCScaleTo::create(0.5, 1);
        
        xing->runAction(CCSpawn::create(rb,sc,NULL));
        
        node->addChild(xing);
        
        if (GameScene::instance()->getStar()>=2) {
            CCSprite* xing1 = CCSprite::createWithSpriteFrameName("ui_c_xing.png");
            xing1->setScale(5);
            xing1->setOpacity(0);
            xing1->setPosition(ccp(0, 50));
            CCDelayTime* dt = CCDelayTime::create(0.5);
            CCFadeIn* in = CCFadeIn::create(0);
            CCRotateBy* rb = CCRotateBy::create(0.5, 360);
            CCScaleTo* sc = CCScaleTo::create(0.5, 1);
            
            xing1->runAction(CCSequence::create(dt,CCSpawn::create(in,rb,sc,NULL),NULL));
            
            node->addChild(xing1);
        }else{
        
            CCSprite* xing1 = CCSprite::createWithSpriteFrameName("ui_c_xing_di.png");
            xing1->setPosition(ccp(0, 50));
            node->addChild(xing1);
        }
        
        
        if (GameScene::instance()->getStar()>=3) {
            CCSprite* xing2 = CCSprite::createWithSpriteFrameName("ui_c_xing.png");
            xing2->setScale(5);
            xing2->setOpacity(0);
            xing2->setRotation(30);
            xing2->setPosition(ccp(100, 30));
            CCDelayTime* dt = CCDelayTime::create(1);
            CCFadeIn* in = CCFadeIn::create(0);
            CCRotateBy* rb = CCRotateBy::create(0.5, 360);
            CCScaleTo* sc = CCScaleTo::create(0.5, 1);
            
            xing2->runAction(CCSequence::create(dt,CCSpawn::create(in,rb,sc,NULL),NULL));
            
            node->addChild(xing2);
        }else{
            CCSprite* xing2 = CCSprite::createWithSpriteFrameName("ui_c_xing_di.png");
            xing2->setRotation(30);
            xing2->setPosition(ccp(100, 30));
            node->addChild(xing2);
        }
        
        CCSprite* wan = CCSprite::createWithSpriteFrameName("ui_c_wanmei.png");
        wan->setPosition(ccp(0, -40));
        wan->setOpacity(0);
        wan->setScale(3);
        CCDelayTime* dt = CCDelayTime::create((GameScene::instance()->getStar())*0.5);
        wan->runAction(CCSequence::create(dt,CCSpawn::create(CCFadeIn::create(0),CCScaleTo::create(0.3, 1),NULL),NULL));
        node->addChild(wan);
        
        _buttons = ButtonWithSpriteManage::create("ui/button.png");
        
        addChild(_buttons);
        
        ButtonWithSprite* button_play = ButtonWithSprite::create(BUTTON_END_NEXT, "buttion_chongwan.png");
        
        button_play->setPosition(ccp(win.width*0.65, win.height*0.30));
        
        _buttons->addButton(button_play);
        
        ButtonWithSprite* button_back = ButtonWithSprite::create(BUTTON_END_BACK, "buttion_fanhuiguanka.png");
        
        button_back->setPosition(ccp(win.width*0.35, win.height*0.30));
        
        _buttons->addButton(button_back);

        
        
        
        return true;
    }
    
    return false;
}

void SucEnd::touchesBegan(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesBegan(touchs, event);
}


void SucEnd::touchesMoved(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesMoved(touchs, event);
}

void SucEnd::touchesEnded(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesEnded(touchs, event);
    
    if(_buttons->getNowID() == BUTTON_END_BACK){
        setDead(DEAD_TYPE_BACK);
        
    }else if(_buttons->getNowID() == BUTTON_END_NEXT){
        setDead(DEAD_TYPE_NEXT);
    }
}