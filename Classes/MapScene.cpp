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

const static int BACK_Z = -100;

const static int MAPUI_Z = -10;

const static int CHOOSE_Z = -5;

const static int SET_Z = -1;

MapScene* MapScene::_instance = NULL;

MapScene* MapScene::instance()
{
    if(NULL == _instance) {
        _instance = new MapScene();
    }
    
    return _instance;
}

MapScene::MapScene():_nowLayer(CHOOSE),_onLayer(NULL),_backLayer(CHOOSE),_login(NULL)
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
    
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    if(type == 0){
    _login = CCLayer::create();
    
    CCSprite* lb = CCSprite::create("main/login.jpg");
    lb->setPosition(ccp(_screenSize.width*0.5, _screenSize.height*0.5));
    _login->addChild(lb);
    
    
    CCSprite* t = CCSprite::create("main/login_t.png");
    t->setAnchorPoint(ccp(0.5, 0));
    t->setPosition(ccp(_screenSize.width*0.5, _screenSize.height));
    _login->addChild(t);
    
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
    _login->addChild(b);
    
    CCFadeOut* out = CCFadeOut::create(1);
    CCFadeIn* in = CCFadeIn::create(1);
    CCSequence* sq = CCSequence::create(out,in,NULL);
    CCRepeatForever* re = CCRepeatForever::create(sq);
    b->runAction(re);
    
    addChild(_login,100);
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
    _goldLabel->setPosition(ccp(_goldback->getPositionX()+_goldback->boundingBox().size.width*0.5-5, _goldback->getPositionY()));
//    _goldLabel->setPosition(CCPointMake(_screenSize.width*0.5, _screenSize.height*0.5));
    addChild(_goldLabel,10);
    
    
    _buttons = ButtonWithSpriteManage::create("ui/button.png");
    
    addChild(_buttons);
    
    ButtonWithSprite* _shop = ButtonWithSprite::create(BUTTON_MAP_SHOP, "button_jia.png");
    _shop->setAnchorPoint(ccp(0, 0.5));
    _shop->setPosition(ccp(_goldback->getPositionX()+_goldback->boundingBox().size.width-_shop->boundingBox().size.width, _goldback->getPositionY()));
    
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
    
    CCLayer::onExit();
}

bool MapScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (_login) {
        return true;
    }
    return _buttons->toucheBegan(pTouch, pEvent);
}

void MapScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (_login) {
        return;
    }
     _buttons->toucheMoved(pTouch, pEvent);
}

void MapScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    if (_login) {
        this->removeChild(_login);
        _login=NULL;
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
            
        }
    }else if (_buttons->getNowID() == BUTTON_MAP_SET){
        
        changeToSet();
    }else if (_buttons->getNowID() == BUTTON_MAP_VIP){
        getAll=99;
        GameSaveData::saveAllData();
    }else if (_buttons->getNowID() == BUTTON_MAP_SHOP){
        player_gold+=999;
        GameSaveData::saveGoldData();
        setGold();
    }
//    removeAllChildren();
//    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f, LoadingScreen::create(KScreenGame, 0)));
}

void MapScene::setGold()
{
    _goldLabel->setString(Tools::intToString(player_gold).c_str());
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

