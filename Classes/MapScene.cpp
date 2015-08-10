//
//  MapScene.cpp
//  GetFish
//
//  Created by zhusu on 15/2/3.
//
//

#include "MapScene.h"
#include "AudioController.h"
#include "Common.h"
#include "GameSaveData.h"
#include "Tools.h"
#include "Data.h"
#include "Shop.h"

const static int BACK_Z = -100;

const static int MAPUI_Z = -10;

const static int CHOOSE_Z = -5;

const static int SET_Z = -1;
const static int SHOP_Z = -1;

MapScene* MapScene::_instance = NULL;

MapScene* MapScene::instance()
{
    if(NULL == _instance) {
        _instance = new MapScene();
    }
    
    return _instance;
}

MapScene::MapScene():_nowLayer(CHOOSE),_onLayer(NULL),_backLayer(CHOOSE),_login(NULL),_logo(NULL),_logo_time(FPS)
{
    
}

MapScene::~MapScene()
{
}

CCScene* MapScene::scene(int type)
{
   
    CCScene *scene = CCScene::create();
    
   
    MapScene *layer = MapScene::create(type);
    
    
    scene->addChild(layer);
    
    
    return scene;
}

MapScene* MapScene::create(int type)
{
    MapScene* game = new MapScene();
    
    if(game && game->init(type)) {
        game->autorelease();
        return game;
    }
    
    CC_SAFE_DELETE(game);
    return NULL;
}

bool MapScene::init(int type)
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    GameSaveData::loadLeveData();
    
    GameSaveData::loadSetData();
    
    GameSaveData::loadGoldData();
    GameSaveData::loadAllData();
    
    _instance = this;
    
    
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/common.plist");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/button.plist");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/ui_map.plist");

    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("item/item.plist");
    
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    if(type == 0){
        
        
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        addLogin();
#else
        _logo = CCLayer::create();
        CCLayerColor* back = CCLayerColor::create(ccc4(255, 255, 255, 255));
        _logo->addChild(back);
        CCSprite* lg = CCSprite::create("ui/logo.png");
        lg->setPosition(ccp(_screenSize.width*0.5, _screenSize.height*0.5));
        lg->setOpacity(0);
        lg->runAction(CCFadeIn::create(0.5));
        _logo->addChild(lg);
        addChild(_logo,101);
#endif
        
        
        
        
        
        
//        CCLabelAtlas* log = CCLabelAtlas::create((Tools::intToString(winW)+"+"+Tools::intToString(winH)).c_str(), "ui/shuzi4.png", 21, 28, 43);
//        log->setPosition(_screenSize.width*0.5, _screenSize.height*0.5);
//        _login->addChild(log,10);
    }
    
    CCSprite* back = CCSprite::create("bg/map_back.jpg");
    
    back->setPosition(ccp(_screenSize.width*0.5, _screenSize.height*0.5));
    
    addChild(back,BACK_Z);
    
    
//    _mapUI = MapUI::create(3);
//    
//    addChild(_mapUI,MAPUI_Z);
    
    
    
    CCSprite* _goldback = CCSprite::createWithSpriteFrameName("ui_qianback.png");
    _goldback->setAnchorPoint(ccp(0, 0.5));
    
    _goldback ->setPosition(ccp(_screenSize.width*0.06, _screenSize.height*0.93));
    
    addChild(_goldback);
    
    
    CCSprite* _gold = CCSprite::createWithSpriteFrameName("ui_jinbi.png");
    _gold->setAnchorPoint(ccp(0.5, 0.5));
    _gold->setPosition(ccp(_goldback->getPositionX(), _goldback->getPositionY()));
    
    addChild(_gold);
    
    
    _goldLabel = CCLabelAtlas::create(Tools::intToString(player_gold).c_str(), "ui/shuzi4.png", 21, 28, 43);
    _goldLabel->setAnchorPoint(ccp(0.5, 0.5));
    _goldLabel->setScale(1.2);
    _goldLabel->setPosition(ccp(_goldback->getPositionX()+_goldback->boundingBox().size.width*0.5, _goldback->getPositionY()));
//    _goldLabel->setPosition(CCPointMake(_screenSize.width*0.5, _screenSize.height*0.5));
    addChild(_goldLabel,10);
    
    _buttons = ButtonWithSpriteManage::create("ui/button.png");
    
    addChild(_buttons);
    
    ButtonWithSprite* _shop = ButtonWithSprite::create(BUTTON_MAP_SHOP, "button_jia.png");
    _shop->setAnchorPoint(ccp(0, 0.5));
    _shop->setPosition(ccp(_goldback->getPositionX()+_goldback->boundingBox().size.width-_shop->boundingBox().size.width+20, _goldback->getPositionY()));
    
    _buttons->addButton(_shop);
    
    ButtonWithSprite* _set = ButtonWithSprite::create(BUTTON_MAP_SET, "button_shezhi.png");
    
    _set->setPosition(ccp(_screenSize.width*0.95, _screenSize.height*0.92));
    
    _buttons->addButton(_set);
    
    _back = ButtonWithSprite::create(BUTTON_MAP_BACK, "button_fanhui.png");
    
    _back->setPosition(ccp(_screenSize.width*0.06, _screenSize.height*0.08));
    
    _buttons->addButton(_back);
    
//    ButtonWithSprite* _shop2 = ButtonWithSprite::create(BUTTON_MAP_SHOP, "button_shangcheng.png");
//    
//    _shop2->setPosition(ccp(_screenSize.width*0.85, _screenSize.height*0.92));
    
    //    _buttons->addChild(_shop2);
    
    ButtonWithSprite* _vip = ButtonWithSprite::create(BUTTON_MAP_VIP, "button_libao.png");
    
    _vip->setPosition(ccp(_screenSize.width*0.8, _screenSize.height*0.92));
    
    _buttons->addButton(_vip);

    this->schedule(schedule_selector(MapScene::cycle));
    
//    _screenSize = CCDirector::sharedDirector()->getWinSize();
//    
//    CCSprite* back = CCSprite::create("main/main.jpg");
//    
//    back->setPosition(ccp(_screenSize.width*0.5, _screenSize.height*0.5));
//    
//    addChild(back);
//    
//    CCFadeIn* in = CCFadeIn::create(1);
//    CCFadeOut* out = CCFadeOut::create(1);
//    
//    CCSequence* sq = CCSequence::create(out,in,NULL);
//    
//    CCRepeatForever* re = CCRepeatForever::create(sq);
//    
//    CCSprite* zi = CCSprite::create("main/mainzi.png");
//    
//    zi->runAction(re);
//    
//    zi->setPosition(ccp(_screenSize.width*0.5, _screenSize.height*0.2));
//    
//    addChild(zi);
    
        
    
//    this->setTouchEnabled(true);
    AUDIO->playBgMusic("music/back1", true);
    
    
//    _nowPlayer = select_player;
    if(type == 0){
        changeToChoose();
    }else{
        changeToMap();
    }
//    _onLayer = ChoosePlayer::create();
//    addChild(_onLayer,CHOOSE_Z);
    
    _message = MessageManage::create("ui/common.png");
    addChild(_message,100);
    
    
//    Shop* shop = Shop::create(0);
//    shop->setPosition(ccp(_screenSize.width*0.5, _screenSize.height*0.5));
//    addChild(shop);
    
    
    return true;
}

void MapScene::setBackButtonV(bool v)
{
    _back -> setVisible(v);
}

void MapScene::addMessage(int type, const char *name)
{
    _message->addMessage(type, name);
}

void MapScene::onEnter()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, KEY_MAPSC, true);
    
    CCLayer::onEnter();
}

void MapScene::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("ui/ui_map.plist");
    
    CCTextureCache::sharedTextureCache()->removeTextureForKey("ui/ui_map.png");
    
    CCTextureCache::sharedTextureCache()->removeTextureForKey("bg/map_back.jpg");
    
    CCArmatureDataManager::sharedArmatureDataManager()->purge();
    
    
    for (int i = 0; i<6; ++i) {
        CCTextureCache::sharedTextureCache()->removeTextureForKey(("ship/bp_"+Tools::intToString(i+1)+".png").c_str());
    }
    
    
    CCLayer::onExit();
}

bool MapScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    if (_login||_logo) {
        return true;
    }
    return _buttons->toucheBegan(pTouch, pEvent);
}

void MapScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (_login||_logo) {
        return;
    }
     _buttons->toucheMoved(pTouch, pEvent);
}

void MapScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    if (_logo) {
        
        
        return;
    }
    
    if (_login) {
        this->removeChild(_login);
        _login=NULL;
        
        CCTextureCache::sharedTextureCache()->removeTextureForKey("main/login.jpg");
        CCTextureCache::sharedTextureCache()->removeTextureForKey("main/login_t.png");
        CCTextureCache::sharedTextureCache()->removeTextureForKey("main/login_b.png");
        
        
        return;
    }
     _buttons->toucheEnded(pTouch, pEvent);

    if (_buttons->getNowID() == BUTTON_MAP_BACK) {
        if (_nowLayer == CHOOSE) {
            
        }else if(_nowLayer == MAP){
            changeToChoose();
        }else if(_nowLayer == SET){
            GameSaveData::saveSetData();
            if (_backLayer == MAP) {
                changeToMap();
            }else{
                changeToChoose();
            }
            
        }else if (_nowLayer == SHOP)
        {
            if (_backLayer == MAP) {
                changeToMap();
            }else{
                changeToChoose();
            }
        }
    }else if (_buttons->getNowID() == BUTTON_MAP_SET){
        changeToSet();
    }else if (_buttons->getNowID() == BUTTON_MAP_VIP){
        changeToShop(Shop::SHOP_TYPE_VIP);
    }else if (_buttons->getNowID() == BUTTON_MAP_SHOP){
        changeToShop(Shop::SHOP_TYPE_GOLD);
    }
//    removeAllChildren();
//    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f, LoadingScreen::create(KScreenGame, 0)));
}

void MapScene::setGold()
{
    _goldLabel->setString(Tools::intToString(player_gold).c_str());
}

void MapScene::changeToShop(int type)
{
    setBackButtonV(true);
    removeChild(_onLayer);
    _onLayer=NULL;
    
    _onLayer = Shop::create(type);
    _onLayer->setPosition(_screenSize.width*0.5, _screenSize.height*0.5);
    addChild(_onLayer,SHOP_Z);
    
    _nowLayer = SHOP;
}

void MapScene::changeToChoose()
{
    setBackButtonV(false);
    removeChild(_onLayer);
    _onLayer = NULL;
    
    _onLayer = ChoosePlayer::create();
    addChild(_onLayer,CHOOSE_Z);
    
    _nowLayer = CHOOSE;
    
    _backLayer = CHOOSE;
}

void MapScene::changeToSet()
{
    setBackButtonV(true);
    removeChild(_onLayer);
    _onLayer=NULL;
    
    _onLayer = Set::create();
    _onLayer->setPosition(_screenSize.width*0.5, _screenSize.height*0.5);
    addChild(_onLayer,SET_Z);
    
    _nowLayer = SET;
    
}

void MapScene::changeToMap()
{
    setBackButtonV(true);
    removeChild(_onLayer);
    _onLayer = NULL;
    
    
    _onLayer = MapUI::create(3);
    
    addChild(_onLayer,MAPUI_Z);
    
    _nowLayer = MAP;
    
    _backLayer = MAP;
}

void MapScene::cycle(float delta)
{
   
    if (_logo) {
        _logo_time--;
        
        if (_logo_time<0) {
            this->removeChild(_logo);
            _logo=NULL;
            
            CCTextureCache::sharedTextureCache()->removeTextureForKey("ui/logo.png");
            
            addLogin();
        }
        
        return;
    }
    
    if (_login) {
        return;
    }
    
    if (_nowLayer == CHOOSE) {
        ChoosePlayer* choose =dynamic_cast<ChoosePlayer*>(_onLayer);
        if(choose &&choose->getIsDead()){
            
            ChoosePlayer* choose = (ChoosePlayer*) _onLayer;
            select_player = choose->getNowPlayer();

            changeToMap();
            
        }
        
    }else if (_nowLayer == MAP)
    {
        MapUI* mapUI = dynamic_cast<MapUI*>(_onLayer);
        if (mapUI && mapUI->isToGame()) {
            _nowLayer = GAME;
            //        int lev =_mapUI->getNowSelect();
//             select_player= _nowPlayer;
            std::vector<int> lev;
            lev.push_back(select_player);
            lev.push_back(mapUI->getNowSelect());
            
            removeAllChildren();
            CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f, LoadingScreen::create(KScreenGame, lev)));
        }
        
    }
}

void MapScene::addLogin()
{
    _login = CCLayer::create();
    
    
    CCSprite* lb = CCSprite::create("main/login.jpg");
    lb->setPosition(ccp(_screenSize.width*0.5, _screenSize.height*0.5));
    _login->addChild(lb);
    
    
    CCSprite* t = CCSprite::create("main/login_t.png");
    t->setAnchorPoint(ccp(0.5, 0));
    t->setPosition(ccp(_screenSize.width*0.5, _screenSize.height));
    _login->addChild(t,10);
    
    CCMoveTo* to = CCMoveTo::create(0.3, ccp(_screenSize.width*0.5, _screenSize.height*0.6));
    CCScaleTo* sc = CCScaleTo::create(0.2, 1, 0.5);
    CCMoveTo* to2 = CCMoveTo::create(0.3, ccp(_screenSize.width*0.5, _screenSize.height*0.7));
    CCScaleTo* sc2 = CCScaleTo::create(0.3, 1, 1);
    CCSpawn* sp = CCSpawn::create(to2,sc2,NULL);
    
    CCSequence* sq1 = CCSequence::create(to,sc,sp,NULL);
    t->runAction(sq1);
    
    CCSprite* b = CCSprite::create("main/login_b.png");
    b->setAnchorPoint(ccp(0.5, 0));
    b->setPosition(ccp(_screenSize.width*0.5+20, 0));
    _login->addChild(b,10);
    
    CCFadeOut* out = CCFadeOut::create(1);
    CCFadeIn* in = CCFadeIn::create(1);
    CCSequence* sq = CCSequence::create(out,in,NULL);
    CCRepeatForever* re = CCRepeatForever::create(sq);
    b->runAction(re);
    
    CCSprite* left = CCSprite::create("ship/bp_4.png");
    left->setPosition(ccp(_screenSize.width*0.2+150, _screenSize.height*0.5));
    left->setScale(0.4);
    CCScaleTo* scl = CCScaleTo::create(0.5, 0.9);
    CCMoveTo* mtl = CCMoveTo::create(0.5, ccp(_screenSize.width*0.2, _screenSize.height*0.5));
    
    left->runAction(CCSpawn::create(scl,mtl,NULL));
    
    CCMoveBy* m = CCMoveBy::create(0.6, ccp(0, -4));
    CCMoveBy* m2 = CCMoveBy::create(0.9, ccp(0, 12));
    CCMoveBy* m3 = CCMoveBy::create(0.6, ccp(0, -8));
    
    CCSequence* s = CCSequence::create(m,m2,m3,NULL);
    
    left->runAction(CCRepeatForever::create(s));
    
    //        left->setScale(0.9);
    //        left->setPosition(ccp(_screenSize.width*0.2, _screenSize.height*0.5));
    
    CCParticleSystemQuad* numP = CCParticleSystemQuad::create("ui/saber.plist");
    numP->setScale(5);
    numP->setPosition(ccp(150, 150));
    left->addChild(numP);
    _login->addChild(left);
    
    CCSprite* right = CCSprite::create("ship/bp_3.png");
    right->setRotation(-20);
    right->setPosition(ccp(_screenSize.width*0.85-150, _screenSize.height*0.7));
    right->setScaleX(-0.2);
    right->setScaleY(0.2);
    
    
    
    CCScaleTo* str = CCScaleTo::create(0.4, -0.7, 0.7);
    CCMoveTo* mtr = CCMoveTo::create(0.4, ccp(_screenSize.width*0.85, _screenSize.height*0.7));
    right->runAction(CCSpawn::create(str,mtr,NULL));
    
    CCParticleSystemQuad* rightP = CCParticleSystemQuad::create("ui/lvjuren.plist");
    rightP->setPosition(ccp(390, 250));
    right->addChild(rightP);
    
    
    CCParticleSystemQuad* rightP2 = CCParticleSystemQuad::create("ui/lvjuren.plist");
    rightP2->setPosition(ccp(330, 260));
    right->addChild(rightP2);
    
    CCDelayTime* dtr = CCDelayTime::create(1);
    
    CCMoveBy* mr = CCMoveBy::create(0.6, ccp(0, -4));
    CCMoveBy* mr2 = CCMoveBy::create(0.9, ccp(0, 12));
    CCMoveBy* mr3 = CCMoveBy::create(0.6, ccp(0, -8));
    
    CCSequence* sr = CCSequence::create(dtr,mr,mr2,mr3,NULL);
    
    right->runAction(CCRepeatForever::create(sr));
    
    
    _login->addChild(right);
    
    CCSprite* mid = CCSprite::create("ship/bp_2.png");
    
    mid->setPosition(ccp(_screenSize.width*0.5-140, _screenSize.height*0.55));
    
    mid->setRotation(-10);
    
    mid->setScaleY(0.4);
    mid->setScaleX(-0.4);
    
    CCScaleTo* stm = CCScaleTo::create(0.6, -1.1, 1.1);
    
    CCMoveTo* mtm = CCMoveTo::create(0.6, ccp(_screenSize.width*0.5+30, _screenSize.height*0.55));
    
    mid->runAction(CCSpawn::create(stm,mtm,NULL));
    
    CCDelayTime* dtm = CCDelayTime::create(0.5);
    
    CCMoveBy* mm = CCMoveBy::create(0.6, ccp(0, -4));
    CCMoveBy* mm2 = CCMoveBy::create(0.9, ccp(0, 12));
    CCMoveBy* mm3 = CCMoveBy::create(0.6, ccp(0, -8));
    
    CCSequence* sm = CCSequence::create(dtm,mm,mm2,mm3,NULL);
    
    mid->runAction(CCRepeatForever::create(sm));
    
    _login->addChild(mid);
    
    
    
    addChild(_login,100);
}
