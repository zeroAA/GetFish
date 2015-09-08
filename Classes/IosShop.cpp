//
//  IosIosIosShop.cpp
//  GetFish
//
//  Created by zhusu on 15/8/11.
//
//

#include "IosShop.h"
#include "Common.h"
#include "Tools.h"
#include "ButtonWithSprite.h"
#include "Data.h"
#include "MapScene.h"
#include "GameSaveData.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "IOSiAP_Bridge.h"
#endif

IosShop* IosShop::create(int type)
{
    IosShop* map = new IosShop();
    
    if(map && map->init(type)) {
        map->autorelease();
        return map;
    }
    
    CC_SAFE_DELETE(map);
    return NULL;
}

IosShop::IosShop()
{
    
}

IosShop::~IosShop()
{
}

bool IosShop::init(int type)
{
    if(CCLayer::init()) {
        
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shop.plist");
        
        
        
        _num.push_back(5);
        _num.push_back(50);
        _num.push_back(23000);
        _num.push_back(75000);
        
        _jiage.push_back(15000);
        _jiage.push_back(75000);
        _jiage.push_back(6);
        _jiage.push_back(12);
        _jiage.push_back(30);
        _jiage.push_back(6);
        
        
        if (GameSaveData::loadNewGif()&&GameSaveData::loadVipGif()) {
            setType(IosShop_TYPE_GOLD);
        }else{
            setType(type);
        }
        
        return true;
    }
    
    return false;
}

void IosShop::onEnter()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, KEY_SHOP, true);
    
    CCLayer::onEnter();
}

void IosShop::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("ui/shop.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("ui/shop.png");
    
    
    CCLayer::onExit();
}

bool IosShop::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    //    CCPoint pos = pTouch->getLocation();
    
    
    return _buttons->toucheBegan(pTouch, pEvent);
}

void IosShop::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    _buttons->toucheMoved(pTouch, pEvent);
    
}

void IosShop::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    _buttons->toucheEnded(pTouch, pEvent);
    
    if (_buttons->getNowID() == BUTTON_SHOP_GOLD&&_type!=IosShop_TYPE_GOLD) {
        setType(IosShop_TYPE_GOLD);
    }else if (_buttons->getNowID() == BUTTON_SHOP_VIP&&_type != IosShop_TYPE_VIP){
        setType(IosShop_TYPE_VIP);
    }else if (_buttons->getNowID() == BUTTON_SHOP_BUY1){
        if (player_gold>=_jiage[0]) {
            player_gold-=_jiage[0];
            getAll+=_num[0];
            GameSaveData::saveAllData();
            GameSaveData::saveGoldData();
            MapScene::instance()->setGold();
            MapScene::instance()->addMessage(1, "ui_ti_30.png");
        }else{
            MapScene::instance()->addMessage(1, "ui_ti_2.png");
        }
    }else if (_buttons->getNowID() == BUTTON_SHOP_BUY2){
        if (player_gold>=_jiage[1]) {
            player_gold-=_jiage[1];
            getAll+=_num[1];
            GameSaveData::saveAllData();
            GameSaveData::saveGoldData();
            MapScene::instance()->setGold();
            MapScene::instance()->addMessage(1, "ui_ti_30.png");
        }else{
            
            MapScene::instance()->addMessage(1, "ui_ti_2.png");
        }
        
    }else if (_buttons->getNowID() == BUTTON_SHOP_BUY3){
        #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        MapScene::instance()->addBuy();
        IOSiAP_Bridge::instance()->requestProducts(IOSiAP_Bridge::IAP_SMALL_GOLD);
        CCLOG("buy23000");
#else
        player_gold+=23000;
        
        MapScene::instance()->setGold();
        
        GameSaveData::saveGoldData();
#endif

    }else if (_buttons->getNowID() == BUTTON_SHOP_BUY4){
        #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        MapScene::instance()->addBuy();
        IOSiAP_Bridge::instance()->requestProducts(IOSiAP_Bridge::IAP_BIG_GOLD);
        CCLOG("buy75000");
#else
        player_gold+=75000;
        
        MapScene::instance()->setGold();
        
        GameSaveData::saveGoldData();
#endif
        
    }else if (_buttons->getNowID() == BUTTON_SHOP_BUY5){
        
        if (!GameSaveData::loadVipGif()) {
            #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
            MapScene::instance()->addBuy();
            IOSiAP_Bridge::instance()->requestProducts(IOSiAP_Bridge::IAP_VIP_GIF);
            CCLOG("buyVIP");
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
            
            MapScene::instance()->setShopButton(2);
#endif
        }
        
        
    }else if (_buttons->getNowID() == BUTTON_SHOP_BUY6){
        if (!GameSaveData::loadNewGif()) {
            #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
            MapScene::instance()->addBuy();
            IOSiAP_Bridge::instance()->requestProducts(IOSiAP_Bridge::IAP_NEW_GIF);
            CCLOG("buyGIF");
#else
            GameSaveData::savePlayer(4);
            
            getAll+=5;
            
            GameSaveData::saveAllData();
            GameSaveData::saveNewGif();
            
            
            MapScene::instance()->setShopButton(3);
#endif
        }
        
    }
    
}

void IosShop::setType(int type)
{
    _type = type;
    removeAllChildren();
    
    if (type == IosShop_TYPE_GOLD) {
        
        CCSprite* IosShopBack = CCSprite::create("ui/ui_shop_back3.png");
        
        addChild(IosShopBack);
        
        _buttons = ButtonWithSpriteManage::create("ui/button.png");
        addChild(_buttons,10);
        
        _buttons -> addButton(BUTTON_SHOP_GOLD, "button_jinbi_xuan.png", ccp(-193, 150));
        _buttons -> addButton(BUTTON_SHOP_VIP, "button_vip_buxuan.png", ccp(193, 150));
        
        
        
        for (int i = 0; i<4; ++i) {
            
            CCSprite* back = CCSprite::createWithSpriteFrameName("ui_shop_back.png");
            back->setPosition(ccp(-289+193*i, -25));
            addChild(back);
            CCSprite* ti;
            if (i<2) {
                ti = CCSprite::createWithSpriteFrameName("shop_ctzi.png");
                ti->setPosition(ccp(-315+193*i, 85));
                addChild(ti);
                
                
            }else{
                ti = CCSprite::createWithSpriteFrameName("ui_jinbi.png");
                ti->setScale(0.55);
                ti->setPosition(ccp(-350+193*i, 85));
                addChild(ti);
            }
            
            if (i<2) {
                CCLabelAtlas* citie_num = CCLabelAtlas::create((","+Tools::intToString(_num[i])).c_str(), "ui/shuzi6.png", 20, 33, 43);
                
                citie_num->setAnchorPoint(ccp(0, 0.5));
                citie_num->setPosition(ccp(ti->boundingBox().getMaxX(), 85));
                addChild(citie_num);
            }else{
                CCLabelAtlas* citie_num = CCLabelAtlas::create((","+Tools::intToString(_num[i])).c_str(), "ui/shuzi4.png", 21, 28, 43);
                citie_num->setScale(0.9);
                citie_num->setAnchorPoint(ccp(0, 0.5));
                citie_num->setPosition(ccp(ti->boundingBox().getMaxX(), 85));
                addChild(citie_num);
            }
            
            CCSprite* jin1;
            
            if(i == 1){
                jin1 = CCSprite::createWithSpriteFrameName("ui_shop_3.png");
                
            }else if(i == 2){
                jin1 = CCSprite::createWithSpriteFrameName("ui_shop_5.png");
                
            }else{
               
                jin1 = CCSprite::createWithSpriteFrameName(("ui_shop_"+Tools::intToString(i+1)+".png").c_str());
                    
                
            }
            
            jin1->setPosition(ccp(-289+193*i, -15));
            
            addChild(jin1);
            
            ButtonWithSprite* _button;
            if (i<2) {
                _button = ButtonWithSprite::create(BUTTON_SHOP_BUY1+i,"button_jingoumai.png");
                
                CCLabelAtlas* citie_num = CCLabelAtlas::create((Tools::intToString(_jiage[i])).c_str(), "ui/shuzi4.png", 21, 28, 43);
                citie_num->setScale(0.8);
                citie_num->setAnchorPoint(ccp(0.5, 0.5));
                citie_num->setPosition(86, 25);
                _button->addChild(citie_num);
                
            }else{
                _button = ButtonWithSprite::create(BUTTON_SHOP_BUY1+i,"button_goumai.png");
                CCSprite* biao = CCSprite::createWithSpriteFrameName("ui_qian.png");
                biao->setPosition(ccp(10, 34));
                _button->addChild(biao);
                
                
                CCLabelAtlas* citie_num = CCLabelAtlas::create((Tools::intToString(_jiage[i])).c_str(), "ui/shuzi1.png", 21, 28, 43);
                citie_num->setScale(0.9);
                citie_num->setAnchorPoint(ccp(0.5, 0.5));
                citie_num->setPosition(40, 30);
                _button->addChild(citie_num);
            }
            
            _button->setPosition(ccp(-289+193*i, -125));
            
            
            _buttons->addButton(_button);
            
        }
        
    }else {
        
        CCSprite* IosShopBack = CCSprite::create("ui/ui_shop_back3.png");
        
        addChild(IosShopBack);
        
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
            
            
            ButtonWithSprite* _button ;
            
            if (i == 0&&GameSaveData::loadVipGif()) {
                _button = ButtonWithSprite::create(BUTTON_SHOP_BUY5+i,"button_yigoumai.png");
            }else if (i == 1&&GameSaveData::loadNewGif()) {
                _button = ButtonWithSprite::create(BUTTON_SHOP_BUY5+i,"button_yigoumai.png");
            }else{
                _button = ButtonWithSprite::create(BUTTON_SHOP_BUY5+i,"button_goumai.png");
            
            CCSprite* biao = CCSprite::createWithSpriteFrameName("ui_qian.png");
            
            biao->setPosition(ccp(10, 34));
            _button->addChild(biao);
            
            
            
            CCLabelAtlas* citie_num = CCLabelAtlas::create((Tools::intToString(_jiage[4+i])).c_str(), "ui/shuzi1.png", 21, 28, 43);
            citie_num->setScale(0.9);
            citie_num->setAnchorPoint(ccp(0.5, 0.5));
            citie_num->setPosition(40, 30);
            _button->addChild(citie_num);
                
            }
            
            _button->setPosition(ccp(-130+390*i, -130));
            _buttons->addButton(_button);
            CCSprite* libao = CCSprite::createWithSpriteFrameName("ui_shp_bao.png");
            libao->setAnchorPoint(ccp(0.5, 0.2));
            CCDelayTime* dt = CCDelayTime::create(Tools::randomFloatInRange(2, 4));
            CCDelayTime* dt1 = CCDelayTime::create(Tools::randomFloatInRange(2, 6));
            CCRotateTo* sto = CCRotateTo::create(0.2, -30);
            CCRotateTo* sto1 = CCRotateTo::create(0.5, 30);
            CCRotateTo* sto2 = CCRotateTo::create(0.2, 0);
            libao->runAction(CCRepeatForever::create( CCSequence::create(dt,sto,sto1,sto2,dt1,NULL)));
            libao->setPosition(ccp(-300+390*i, -20));
            addChild(libao);
            
            CCSprite* neirong = CCSprite::createWithSpriteFrameName(("libao"+Tools::intToString(i+1)+".png").c_str());
            neirong->setPosition(ccp(-130+400*i, 0));
            neirong->setScale(0.9);
            addChild(neirong);
            
        }
        
        
        
    }
    
}

void IosShop::setButton(int indext)
{
    ButtonWithSprite* _button = _buttons->getButton(indext);
    _button->removeAllChildren();
    _button->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_yigoumai.png"));
}