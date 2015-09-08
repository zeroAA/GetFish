//
//  Shop.cpp
//  GetFish
//
//  Created by zhusu on 15/8/3.
//
//

#include "Shop.h"
#include "Common.h"
#include "Tools.h"
#include "ButtonWithSprite.h"
#include "Data.h"
#include "MapScene.h"
#include "GameSaveData.h"


Shop* Shop::create(int type)
{
    Shop* map = new Shop();
    
    if(map && map->init(type)) {
        map->autorelease();
        return map;
    }
    
    CC_SAFE_DELETE(map);
    return NULL;
}

Shop::Shop()
{
    
}

Shop::~Shop()
{
}

bool Shop::init(int type)
{
    if(CCLayer::init()) {
        
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shop.plist");
        
        
        
        _num.push_back(1);
        _num.push_back(20);
        _num.push_back(99);
        _num.push_back(99999);
        
        setType(type);
        return true;
    }
    
    return false;
}

void Shop::onEnter()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, KEY_SHOP, true);
    
    CCLayer::onEnter();
}

void Shop::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("ui/shop.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("ui/shop.png");

    
    CCLayer::onExit();
}

bool Shop::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
//    CCPoint pos = pTouch->getLocation();
    
    
    return _buttons->toucheBegan(pTouch, pEvent);
}

void Shop::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    _buttons->toucheMoved(pTouch, pEvent);
    
}

void Shop::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    _buttons->toucheEnded(pTouch, pEvent);
    
    if (_buttons->getNowID() == BUTTON_SHOP_GOLD&&_type!=SHOP_TYPE_GOLD) {
        setType(SHOP_TYPE_GOLD);
    }else if (_buttons->getNowID() == BUTTON_SHOP_VIP&&_type != SHOP_TYPE_VIP){
        setType(SHOP_TYPE_VIP);
    }else if (_buttons->getNowID() == BUTTON_SHOP_BUY1){
        if (player_gold>=GETALL_GOLD) {
            player_gold-=GETALL_GOLD;
            getAll+=_num[0];
            GameSaveData::saveAllData();
            GameSaveData::saveGoldData();
            MapScene::instance()->setGold();
        }else{
            MapScene::instance()->addMessage(1, "ui_ti_2.png");
        }
    }else if (_buttons->getNowID() == BUTTON_SHOP_BUY2){
        
        getAll+=_num[1];
        GameSaveData::saveAllData();
    }else if (_buttons->getNowID() == BUTTON_SHOP_BUY3){
        getAll+=_num[2];
        GameSaveData::saveAllData();
    }else if (_buttons->getNowID() == BUTTON_SHOP_BUY4){
        
        player_gold+=_num[3];
        
        MapScene::instance()->setGold();
        
        GameSaveData::saveGoldData();
        
    }else if (_buttons->getNowID() == BUTTON_SHOP_BUY5){
        
    }else if (_buttons->getNowID() == BUTTON_SHOP_BUY6){
        
    }
    
}

void Shop::setType(int type)
{
    _type = type;
    removeAllChildren();
    
    if (type == SHOP_TYPE_GOLD) {
        
        CCSprite* shopBack = CCSprite::create("ui/ui_shop_back3.png");
        
        addChild(shopBack);
        
        _buttons = ButtonWithSpriteManage::create("ui/button.png");
        addChild(_buttons,10);
        
        _buttons -> addButton(BUTTON_SHOP_GOLD, "button_jinbi_xuan.png", ccp(-193, 150));
        _buttons -> addButton(BUTTON_SHOP_VIP, "button_vip_buxuan.png", ccp(193, 150));
        
        
        
        for (int i = 0; i<4; ++i) {
            
            CCSprite* back = CCSprite::createWithSpriteFrameName("ui_shop_back.png");
            back->setPosition(ccp(-289+193*i, -25));
            addChild(back);
            CCSprite* ti;
            if (i<3) {
                ti = CCSprite::createWithSpriteFrameName("shop_ctzi.png");
                ti->setPosition(ccp(-315+193*i, 85));
                addChild(ti);
                
                
            }else{
                ti = CCSprite::createWithSpriteFrameName("ui_jinbi.png");
                ti->setScale(0.55);
                ti->setPosition(ccp(-350+193*i, 85));
                addChild(ti);
            }
        
            if (i<3) {
            CCLabelAtlas* citie_num = CCLabelAtlas::create((","+Tools::intToString(_num[i])).c_str(), "ui/shuzi6.png", 20, 33, 43);
            citie_num->setAnchorPoint(ccp(0, 0.5));
            citie_num->setPosition(ccp(ti->boundingBox().getMaxX(), 85));
            addChild(citie_num);
            }else{
                CCLabelAtlas* citie_num = CCLabelAtlas::create((","+Tools::intToString(_num[i])).c_str(), "ui/shuzi4.png", 21, 28, 43);
                citie_num->setAnchorPoint(ccp(0, 0.5));
                citie_num->setPosition(ccp(ti->boundingBox().getMaxX(), 85));
                addChild(citie_num);
            }
            
            CCSprite* jin1 = CCSprite::createWithSpriteFrameName(("ui_shop_"+Tools::intToString(i+1)+".png").c_str());
            
            jin1->setPosition(ccp(-289+193*i, -15));
            
            addChild(jin1);
            
            ButtonWithSprite* _button;
            if (i==0) {
                _button = ButtonWithSprite::create(BUTTON_SHOP_BUY1+i,"button_jingoumai.png");
                
                CCLabelAtlas* citie_num = CCLabelAtlas::create((Tools::intToString(GETALL_GOLD)).c_str(), "ui/shuzi4.png", 21, 28, 43);
                citie_num->setAnchorPoint(ccp(0.5, 0.5));
                citie_num->setPosition(80, 25);
                _button->addChild(citie_num);
                
            }else{
                _button = ButtonWithSprite::create(BUTTON_SHOP_BUY1+i,"button_goumai.png");
                CCSprite* biao = CCSprite::createWithSpriteFrameName("ui_qian.png");
                biao->setPosition(ccp(10, 34));
                _button->addChild(biao);
                
                
                CCLabelAtlas* citie_num = CCLabelAtlas::create((Tools::intToString(i*5)).c_str(), "ui/shuzi1.png", 21, 28, 43);
                citie_num->setScale(0.9);
                citie_num->setAnchorPoint(ccp(0.5, 0.5));
                citie_num->setPosition(40, 30);
                _button->addChild(citie_num);
            }
            
            _button->setPosition(ccp(-289+193*i, -125));
            
            
            _buttons->addButton(_button);
            
        }
        
    }else {
        
        CCSprite* shopBack = CCSprite::create("ui/ui_shop_back3.png");
        
        addChild(shopBack);
        
        _buttons = ButtonWithSpriteManage::create("ui/button.png");
        addChild(_buttons,10);
        
        _buttons -> addButton(BUTTON_SHOP_GOLD, "button_jinbi_buxuan.png", ccp(-193, 150));
        _buttons -> addButton(BUTTON_SHOP_VIP, "button_vip_xuan.png", ccp(193, 150));
        
        for (int i = 0; i<2; ++i) {
            CCSprite* back = CCSprite::createWithSpriteFrameName("ui_shop_back2.png");
            back->setPosition(ccp(-195+390*i, -25));
            addChild(back);
            
            CCSprite* tiao = CCSprite::createWithSpriteFrameName(("ui_shop_libao_"+Tools::intToString(i)+".png").c_str());
            tiao->setPosition(ccp(-300+390*i, -30));
            addChild(tiao);
            
            ButtonWithSprite* _button = ButtonWithSprite::create(BUTTON_SHOP_BUY5+i,"button_goumai.png");
            
            CCSprite* biao = CCSprite::createWithSpriteFrameName("ui_qian.png");
            
            biao->setPosition(ccp(10, 34));
            _button->addChild(biao);
            _button->setPosition(ccp(-113+390*i, -125));
            
            
            CCLabelAtlas* citie_num = CCLabelAtlas::create((Tools::intToString(10)).c_str(), "ui/shuzi1.png", 21, 28, 43);
            citie_num->setScale(0.9);
            citie_num->setAnchorPoint(ccp(0.5, 0.5));
            citie_num->setPosition(40, 30);
            _button->addChild(citie_num);

            
            _buttons->addButton(_button);
            
            
            
        }
        
        
        
    }

}