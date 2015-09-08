//
//  MapUI.cpp
//  GetFish
//
//  Created by zhusu on 15/2/3.
//
//

#include "MapUI.h"
#include "Common.h"
#include "GameSaveData.h"
#include "Tools.h"
#include "MapScene.h"
#include "Message.h"
#include "Data.h"
#include "Reward.h"

const int MAPE_Z = -10;


MapUI* MapUI::create(int lev)
{
    MapUI* map = new MapUI();
    
    if(map && map->init(lev)) {
        map->autorelease();
        return map;
    }
    
    CC_SAFE_DELETE(map);
    return NULL;
}


MapUI::MapUI():_nowSelect(-1),_upLayer(NULL),_setCup(true),_isCanCup(false)
{
    
}

MapUI::~MapUI()
{
    CC_SAFE_RELEASE_NULL(_mapE);
}

bool MapUI::init(int lev)
{
    if(!CCLayer::init()) {
        
        return false;
    }
    
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    
    
    
    _gif_gold.push_back(1000);
    _gif_gold.push_back(3000);
    _gif_gold.push_back(6000);
    _gif_gold.push_back(10000);
    _gif_gold.push_back(15000);
    _gif_gold.push_back(20000);
    
    
    _gif_getAll.push_back(2);
    _gif_getAll.push_back(3);
    _gif_getAll.push_back(5);
    _gif_getAll.push_back(8);
    _gif_getAll.push_back(12);
    _gif_getAll.push_back(15);
    
    _mapE = CCArray::create();
    
    _mapE->retain();
    
    _levE = CCLayer::create();
    player_star = 0;
    int nowPage = 0;
    nowLev = 0;
    
    
    
    for(int k = 0 ; k<6;++k){
        for (int i = 0; i<3; ++i) {
            for (int j = 0; j<4; ++j) {
                int star = GameSaveData::loadLevelData(j+i*4+k*12);
                
                if (j+i+k == 0&&star<=0) {
                    star=1;
                    GameSaveData::saveLevelData(0, star);
                }
                
                if (star >0) {
                    nowLev =j+i*4+k*12;
                    nowPage = k;
                    if (star==2) {
                        player_star+=1;
                    }else if (star==3) {
                        player_star+=2;
                    }else if (star>=4) {
                        player_star+=3;
                    }
                    
                }
                
            }
        }
    }
    
        if (nowLev==11&&player_star>=LEV12_STAR) {
             GameSaveData::saveLevelData(nowLev+1, 1);
        }else if(nowLev==23&&player_star>=LEV24_STAR){
            GameSaveData::saveLevelData(nowLev+1, 1);
        }else if(nowLev == 35&&player_star>=LEV36_STAR){
            GameSaveData::saveLevelData(nowLev+1, 1);
        }else if(nowLev == 47&&player_star>=LEV48_STAR){
            GameSaveData::saveLevelData(nowLev+1, 1);
        }else if(nowLev == 59&&player_star>=LEV60_STAR){
            GameSaveData::saveLevelData(nowLev+1, 1);
        }
        
    
    for(int k = 0 ; k<6;++k){
        for (int i = 0; i<3; ++i) {
            for (int j = 0; j<4; ++j) {
                
                int star = GameSaveData::loadLevelData(j+i*4+k*12);
                
                MapElement* me = MapElement::create(star, j+i*4+k*12);
                me->setPosition(ccp(_screenSize.width*k+_screenSize.width*0.2+_screenSize.width*0.2*j, _screenSize.height-_screenSize.height*0.26-_screenSize.height*0.23*i));
                _levE->addChild(me);
                _mapE->addObject(me);
            }
        }
    }
    
    
    _levE->setContentSize(ccp(_screenSize.width, _screenSize.height));
    _scroll = ScrollView::create(_screenSize,_levE);
    _scroll->setDirection(kCCScrollViewDirectionHorizontal);
    _scroll->setTouchPriority(KEY_MAP-1);
    
    _scroll->setPosition(ccp(0,0));
    _scroll->setMate(_screenSize.width,6,ScrollView::MATE_NORMAL);
    this->addChild(_scroll,1);
    
    
    _buttons = ButtonWithSpriteManage::create("ui/button.png");
    
    addChild(_buttons);
    
    
    _cup = ButtonWithSprite::create(BUTTON_MAP_CUP, "button_mapbei.png");
    
    _cup->setPosition(ccp(_screenSize.width*0.93, _screenSize.height*0.11));
    
    _buttons->addButton(_cup);
    
    numP = CCParticleSystemQuad::create("ui/jiangli.plist");
    numP->setPosition(ccp(56,107));
    
    _cup->addChild(numP);
    
    this->setTouchEnabled(true);
    
    schedule(schedule_selector(MapUI::cycle));
    
    for (int i = 0; i<6; ++i) {
        CCSprite* dian = CCSprite::createWithSpriteFrameName("ui_dian1.png");
        
        dian->setPosition(ccp(_screenSize.width*0.5-125+i*50, _screenSize.height*0.10));
        
        addChild(dian);
        
    }
    _chooseIc = CCSprite::createWithSpriteFrameName("ui_dian2.png");
    setChooseIC();
    addChild(_chooseIc);
    
    
    if (data_nowLev>0) {
        nowPage= data_nowLev/12;
    }
    
    if (nowPage!=0) {
        _scroll->toOneMate(nowPage);
    }
    
    CCSprite* sstar = CCSprite::createWithSpriteFrameName("ui_c_xing.png");
    sstar->setPosition(ccp(_screenSize.width*0.4, _screenSize.height-45));
    addChild(sstar);
    
    CCLabelAtlas* starNum = CCLabelAtlas::create((","+Tools::intToString(player_star)).c_str(), "ui/shuzi4.png", 21, 28, 43);
    starNum->setAnchorPoint(ccp(0, 0.5));
    starNum->setPosition(ccp(sstar->boundingBox().getMaxX()+20, sstar->getPositionY()-5));
    addChild(starNum,10);
    
    
    
    return true;
}

void MapUI::cycle(float delta)
{
    
    _levE->setPosition(ccp(_scroll->getContentOffset().x, 0));
    
    
    if (_scroll-> isMoveEnd()) {
        
        setChooseIC();
        if (_setCup) {
            
            _isCanCup = true;
            
            _setCup = false;
            
            bool can = true;
            
            if (GameSaveData::loadReward(_scroll->getNowPage())) {
                can = false;
            }
            
            
            numP->setPosition(ccp(56,107));
            if (can) {
                
                for (int i = 0; i<12; ++i) {
                    int star = GameSaveData::loadLevelData(i+_scroll->getNowPage()*12);
                    if (star <5) {
                        numP->setPosition(99999, 99999);
                        _isCanCup = false;
                        break;
                    }
                }
            }
            
            _cup->setVisible(can);
        }
    }else{
        _setCup = true;
    }
}

void MapUI::onEnter()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, KEY_MAP, true);
    
    CCLayer::onEnter();
}

void MapUI::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CCLayer::onExit();
}

bool MapUI::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint pos = pTouch->getLocation();
    
    
    if (_upLayer) {
        return _upLayer->touchBegan(pTouch, pEvent);
    }else{
        
        if (CCRectMake(_screenSize.width*0.1, _screenSize.height*0.2, _screenSize.width*0.8, _screenSize.height*0.6).containsPoint(pos)) {
            
            _nowSelect= 1000;
            return true;
        }
        
        if (_buttons->toucheBegan(pTouch, pEvent)) {
            return true;
        }
    }
    return false;
}

void MapUI::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (_upLayer) {
        _upLayer->touchMoved(pTouch, pEvent);
    }else{
        _buttons->toucheMoved(pTouch, pEvent);
    }
}

void MapUI::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    if (_upLayer) {
        _upLayer->touchEnded(pTouch, pEvent);
        
        if (_upLayer->getButtonID() == BUTTON_GET_BACK) {
            _scroll->setEnable(true);
            removeChild(_upLayer);
            _upLayer=NULL;
        }else if (_upLayer->getButtonID() == BUTTON_GET_GET){
            
            bool can = true;
            
            for (int i = 0; i<3; ++i) {
                for (int j = 0; j<4; ++j) {
                    int star = GameSaveData::loadLevelData(j+i*4+_scroll->getNowPage()*12);
                    if (star <4) {
                        can = false;
                        break;
                    }
                }
            }
            
            if (can) {
                MapScene::instance()->addMessage(1, "ui_ti_4.png");
                _cup->setVisible(false);
                _scroll->setEnable(true);
                removeChild(_upLayer);
                _upLayer=NULL;
                
                player_gold += _gif_gold[_scroll->getNowPage()];
                MapScene::instance()->setGold();
                getAll += _gif_getAll[_scroll->getNowPage()];
                
                GameSaveData::saveReward(_scroll->getNowPage());
                
                
            }else{
                MapScene::instance()->addMessage(1, "ui_ti_5.png");
            }
            
        }
    }else{
        _buttons->toucheEnded(pTouch, pEvent);
        
        
        if (_nowSelect == 1000&&_scroll-> isMoveEnd()) {
            for (int i = _scroll->getNowPage()*12; i<_scroll->getNowPage()*12+12; ++i) {
                
                MapElement* me = (MapElement*) _mapE->objectAtIndex(i);
                
                if (CCRectMake(me->getBody().origin.x+(int)_scroll->getContentOffset().x, me->getBody().origin.y, me->getBody().size.width, me->getBody().size.height).containsPoint(pTouch->getLocation())) {
                    //                CCLOG("se : %i ",me->getLev());
                    
                    if (me->getStar()==0) {
                        //                    CCLOG("no open");
                        
                        if (player_star<LEV12_STAR&&me->getLev() >= 12&&me->getLev() <= 23) {
                            
                            if (nowLev<11) {
                                MapScene::instance()->addMessage(Message::TYPE_OVER_DEAD, "ui_ti_21.png");
                            }else{
                            
                            
                            _tishi = NoGold::create(NoGold::TYPE_KAI_2);
                            _tishi->setPosition(_screenSize.width*0.5, _screenSize.height*0.5);
                            addChild(_tishi,999);
                            }
                            
                        }else if (player_star<LEV24_STAR&& me->getLev() >= 24&& me->getLev() <= 35){
                            if (nowLev<11) {
                            MapScene::instance()->addMessage(Message::TYPE_OVER_DEAD, "ui_ti_22.png");
                            }else{
                            _tishi = NoGold::create(NoGold::TYPE_KAI_3);
                            _tishi->setPosition(_screenSize.width*0.5, _screenSize.height*0.5);
                            addChild(_tishi,999);
                            }
                        }else if (player_star<LEV36_STAR&& me->getLev() >= 36&&me->getLev() <= 47){
                            if (nowLev<11) {
                            MapScene::instance()->addMessage(Message::TYPE_OVER_DEAD, "ui_ti_23.png");
                            }else{
                            _tishi = NoGold::create(NoGold::TYPE_KAI_4);
                            _tishi->setPosition(_screenSize.width*0.5, _screenSize.height*0.5);
                            addChild(_tishi,999);
                            }
                        }else if (player_star<LEV48_STAR&&me->getLev() >= 48&&me->getLev() <= 59){
                            if (nowLev<11) {
                            MapScene::instance()->addMessage(Message::TYPE_OVER_DEAD, "ui_ti_24.png");
                            }else{
                            _tishi = NoGold::create(NoGold::TYPE_KAI_5);
                            _tishi->setPosition(_screenSize.width*0.5, _screenSize.height*0.5);
                            addChild(_tishi,999);
                            }
                        }else if (player_star<LEV60_STAR&&me->getLev() >= 60&&me->getLev() <= 71){
                            if (nowLev<11) {
                            MapScene::instance()->addMessage(Message::TYPE_OVER_DEAD, "ui_ti_25.png");
                            }else{
                            _tishi = NoGold::create(NoGold::TYPE_KAI_6);
                            _tishi->setPosition(_screenSize.width*0.5, _screenSize.height*0.5);
                            addChild(_tishi,999);
                            }
                        }else{
                            
                            if (nowLev<11) {
                                                            MapScene::instance()->addMessage(Message::TYPE_OVER_DEAD, "ui_ti_3.png");
                                
                            }else{
                         
                            _tishi = NoGold::create(NoGold::TYPE_KAI_NO);
                            _tishi->setPosition(_screenSize.width*0.5, _screenSize.height*0.5);
                            addChild(_tishi,999);
                            }
                            
                        }
                    }else{
                        _nowSelect =me->getLev();
                    }
                    
                    return;
                    
                }
            }
            
        }else if(_buttons->getNowID() == BUTTON_MAP_CUP){
            if (!_upLayer) {
                _scroll->setEnable(false);
                _upLayer = Reward::create(_isCanCup,_gif_gold[_scroll->getNowPage()],_gif_getAll[_scroll->getNowPage()]);
                _upLayer->setPosition(ccp(_screenSize.width*0.5, _screenSize.height*0.5));
                addChild(_upLayer,200);
            }
            
            
//                    for (int i =0; i<25; ++i) {
//                        GameSaveData::saveLevelData(i, 5);
//                    }
        }
        
        
        if(_nowSelect == 1000){
            _nowSelect =-1;
            
        }
    }
}

void MapUI::setChooseIC()
{
    _chooseIc->setPosition(ccp(_screenSize.width*0.5-125+_scroll->getNowPage()*50, _screenSize.height*0.10));
}

int MapUI::getNowSelect() const
{
    return _nowSelect;
}

bool MapUI::isToGame() const
{
    
    return 0<=_nowSelect&&_nowSelect<_mapE->count();
    
    //    return true;
}
