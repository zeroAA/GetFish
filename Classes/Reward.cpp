//
//  Reward.cpp
//  GetFish
//
//  Created by zhusu on 15/8/3.
//
//

#include "Reward.h"
#include "Common.h"
#include "Tools.h"

Reward* Reward::create(bool can, int gold,int get)
{
    Reward* map = new Reward();
    
    if(map && map->init(can,gold,get)) {
        map->autorelease();
        return map;
    }
    
    CC_SAFE_DELETE(map);
    return NULL;
}


Reward::Reward()
{
    
}

Reward::~Reward()
{
    
}

bool Reward::init(bool can,int gold,int get)
{
    if(!CCLayer::init()) {
        
        return false;
    }
    
    _isCan = can;
    
    CCSprite* back = CCSprite::createWithSpriteFrameName("ui_tishi_back.png");
    
    addChild(back);
    
    CCSprite* tile = CCSprite::createWithSpriteFrameName("ui_wanmeijiangli.png");
    
    tile->setPosition(ccp(0, back->boundingBox().getMaxY()-28));
    
    addChild(tile);
    
    CCSprite* zi = CCSprite::createWithSpriteFrameName("ui_wan_zi.png");
    zi->setPosition(ccp(0, 40));
    addChild(zi);
    
    
    CCSprite* jinbi = CCSprite::createWithSpriteFrameName("ui_jinbi.png");
    jinbi->setScale(0.7);
    jinbi->setPosition(ccp(-195, -40));
    addChild(jinbi);
    
    CCLabelAtlas* jinbi_num = CCLabelAtlas::create((","+Tools::intToString(gold)).c_str(), "ui/shuzi4.png", 21, 28, 43);
    jinbi_num->setAnchorPoint(ccp(0, 0.5));
    jinbi_num->setPosition(ccp(jinbi->boundingBox().getMaxX()+10, jinbi->getPositionY()-5));
    addChild(jinbi_num);
    
    CCSprite* citie = CCSprite::createWithSpriteFrameName("item_3.png");
    citie->setPosition(ccp(45, -40));
    addChild(citie);
    
    CCLabelAtlas* citie_num = CCLabelAtlas::create((","+Tools::intToString(get)).c_str(), "ui/shuzi4.png", 21, 28, 43);
    citie_num->setAnchorPoint(ccp(0, 0.5));
    citie_num->setPosition(ccp(citie->boundingBox().getMaxX()+10, citie->getPositionY()-5));
    addChild(citie_num);
    
    _buttons = ButtonWithSpriteManage::create("ui/button.png");
    
    addChild(_buttons);
    
    if (_isCan) {
        _buttons->addButton(BUTTON_GET_GET, "button_ling.png", ccp(144, -128));
    }else{
        _buttons->addButton(BUTTON_GET_GET, "button_noling.png", ccp(144, -128));
    }
    
    
    _buttons->addButton(BUTTON_GET_BACK, "button_fanhui2.png", ccp(-144, -128));
    
    return true;
    
}


bool Reward::touchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return _buttons->toucheBegan(pTouch, pEvent);
}


void Reward::touchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    _buttons->toucheMoved(pTouch, pEvent);
}

void Reward::touchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
    _buttons->toucheEnded(pTouch, pEvent);
    
}

int Reward::getButtonID()
{
    return _buttons->getNowID();
}
