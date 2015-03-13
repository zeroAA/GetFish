//
//  GameSecne.cpp
//  GetFish
//
//  Created by zhusu on 14/12/12.
//
//

#include "GameScene.h"
#include "Tools.h"
#include "Fish.h"
#include "Ship.h"
#include "Effect.h"
#include "Common.h"
#include "AudioController.h"
#include "BinaryReadUtil.h"

GameScene* GameScene::_instance = NULL;

const static int BG_Z = -80;

const static int SHIP_Z = -50;

const static int FISH_Z = -30;

const static int ROCK_Z = -25;

const static int LEAF_Z = -24;

const static int EFFECT_Z = -20;

const static int UI_Z = -10;

GameScene* GameScene::instance()
{
    if(NULL == _instance) {
        _instance = new GameScene();
    }
    
    return _instance;
}

CCScene* GameScene::scene(int lev)
{
    
    CCScene* scene = CCScene::create();
    
    GameScene* layer = GameScene::create(lev);
    
    scene->addChild(layer);
    
    return scene;
}

GameScene::GameScene():_addFishTime(0),_addSPFishTime(0),_time(1800),_isChange(false),_nowDataInedxt(0)
{
    
}

GameScene::~GameScene()
{
}

GameScene* GameScene::create(int lev)
{
    GameScene* game = new GameScene();
    
    if(game && game->init(lev)) {
        game->autorelease();
        return game;
    }
    
    CC_SAFE_DELETE(game);
    return NULL;
}

bool GameScene::init(int lev)
{
    
    if (CCLayer::init())
    {
       
        
        _screenSize = CCDirector::sharedDirector()->getWinSize();
        
        _instance = this;
        
        _nowLev = lev;
        
        
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_1.csb");
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_2.csb");
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_3.csb");
        
        
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_1110.csb");
        
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_1120.csb");
        
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_1130.csb");
        
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_1140.csb");
        
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_1150.csb");
        
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_1160.csb");
        
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_1170.csb");
        
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_1180.csb");
        
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_1190.csb");
        
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/whaleWater.csb");
        
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fishbone.csb");
        
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fishbone.ExportJson");
        
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("ship/ship_1.csb");
        
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("ship/player_3.csb");
      
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/rock_1.ExportJson");
        
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/leaf_1.csb");
        
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("test/test10.csb");
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("test/test11.csb");
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("test/test12.csb");
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("test/test13.csb");
//        
//        CCArmature* test1 = CCArmature::create("test10");
//        
//                test1->getAnimation()->playWithIndex(0);
//                test1->setPosition(_screenSize.width*0.2, _screenSize.height*0.5);
//        addChild(test1);
//        
//        CCArmature* test2 = CCArmature::create("test11");
//        
//        test2->getAnimation()->playWithIndex(0);
//        test2->setPosition(_screenSize.width*0.4, _screenSize.height*0.5);
//        addChild(test2);
//        
//        CCArmature* test3 = CCArmature::create("test12");
//        
//        test3->getAnimation()->playWithIndex(0);
//        test3->setPosition(_screenSize.width*0.6, _screenSize.height*0.5);
//        addChild(test3);
//        
//        
//        CCArmature* test4 = CCArmature::create("test13");
//        
//        test4->getAnimation()->playWithIndex(0);
//        test4->setPosition(_screenSize.width*0.8, _screenSize.height*0.5);
//        addChild(test4);
//
////        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("test/test3.csb");
////        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("test/test1.csb");
////        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("test/testRen.csb");
////        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("test/testRen1.csb");
////        
////        CCArmature* test = CCArmature::create("testRen");
//////        test->setScale(1.3);
////        test->getAnimation()->playWithIndex(0);
////        test->setPosition(_screenSize.width*0.5, _screenSize.height*0.5);
////        
////        addChild(test);
//////
////        CCArmature* test1 = CCArmature::create("test3");
////       
////        test1->getAnimation()->playWithIndex(0);
////        test1->setPosition(_screenSize.width*0.3, _screenSize.height*0.5);
////        
////        addChild(test1);
      
        
//        CCSprite* st = CCSprite::create("fish/skeleton-animation2.png");
//        
//        st->setPosition(ccp(100, 100));
//        
//        addChild(st,10);
        
        _shipLayer = ShipManage::create();
        
        addChild(_shipLayer,SHIP_Z);
        
        _shipLayer->addShip(0, "player_3");
        
        schedule(schedule_selector(GameScene::cycle));
        
        _fishLayer = FishManage::create();
        
        addChild(_fishLayer,FISH_Z);
        
        
        _rockLayer = RockManage::create();
        
        addChild(_rockLayer,ROCK_Z);
        
        _leafLayer = LeafManage::create();
        
        addChild(_leafLayer,LEAF_Z);

        _bgLayer = BackGround::create();
        
        addChild(_bgLayer,BG_Z);

        
        
        _effectLayer = EffectManage::create();
        
        addChild(_effectLayer,EFFECT_Z);
        
        
        
        _ui = GameUI::create();
        
        addChild(_ui,UI_Z);
        
        _mubiao_scroe.push_back(100);
        _mubiao_scroe.push_back(500);
        _mubiao_scroe.push_back(1000);
        
        _ui->addMubiaoScore(_mubiao_scroe);
        
        this->setTouchEnabled(true);
        
        
        BinaryReadUtil* _IO_read = BinaryReadUtil::create("data/level_0.data");
        
        int len = _IO_read -> readInt();
        
        for (int i = 0; i<len; ++i) {
            int len2 = _IO_read->readInt();
            
            
            //                CCLOG("j : %i",_IO_read->readInt());
            int type = _IO_read->readInt();
            if (type == ADD_NORMAL||type == ADD_FORMAT) {
                std::vector<int> data_1;
                data_1.push_back(type);
                for (int j = 0; j<len2-1; ++j) {
                    data_1.push_back(_IO_read->readInt());
                }
                
                _data.push_back(data_1);
            }else if(type == SET_TIME){
                _time = _IO_read->readInt();
            }else if(type == ADD_ROCK){
                CCPoint pos = CCPointMake(_IO_read->readInt(), _IO_read->readInt());
                int hp =_IO_read->readInt();
                _rockLayer->addRock("rock_1", hp, pos);
            }else if(type == ADD_LEAF){
//                _leafLayer->addLeaf("leaf_1", <#int dir#>, <#float speed#>, <#float y#>)
                
                std::vector<int> data;
                data.push_back(type);
                
                for (int j = 0; j<len2-1; ++j) {
                    data.push_back(_IO_read->readInt());
                }
                
                _add_leaf.push_back(data);
            }
            
            //            CCLOG("、、、、、");
        }
//        std::vector<int> nowdata= _data[_nowDataInedxt];
//        for (int i =0; i<nowdata.size(); ++i) {
//            CCLOG("%i",nowdata[i]);
//        }
        
//       CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
        
        
        
//        _rockLayer->addRock("rock_1", 5, CCPointMake(200, 200));
        
        
//        CCArmature* rock = CCArmature::create("rock_1");
//        rock->setPosition(CCPointMake(200, 200));
//        addChild(rock,100);
        
        return true;
    }
    
    return false;
}

void GameScene::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void GameScene::ccTouchesBegan(CCSet * touchs,CCEvent * event)
{
    if (!_ui->GameUItouchesBegan(touchs, event)) {
        
        for(CCSetIterator iter=touchs->begin();iter!=touchs->end();iter++){
            
            CCTouch * mytouch=(CCTouch *)(* iter);
            
            CCPoint pos=mytouch->getLocation();
            
            Ship* ship = dynamic_cast<Ship*>(_shipLayer->getActor()->objectAtIndex(0));
            if (ship) {
                ship->setShipTo(pos.x);
            }
            
            
            break;
        }

    }
}



void GameScene::ccTouchesCancelled(CCSet * touchs,CCEvent * event)
{
    
    if (_ui->getNowButtonID()!=-1) {
        _ui->GameUItouchesCancelled(touchs, event);
    }else{
    
        for(CCSetIterator iter=touchs->begin();iter!=touchs->end();iter++){
            
            CCTouch * mytouch=(CCTouch *)(* iter);
            
            CCPoint pos=mytouch->getLocation();
            
            Ship* ship = dynamic_cast<Ship*>(_shipLayer->getActor()->objectAtIndex(0));
            if (ship) {
                ship->setShipTo(pos.x);
            }
            
            
            break;
        }
    
    }
    
}

void GameScene::ccTouchesMoved(CCSet * touchs,CCEvent * event)
{
    if (_ui->getNowButtonID() != -1) {
        _ui->GameUItouchesMoved(touchs, event);
    }else{
    for(CCSetIterator iter=touchs->begin();iter!=touchs->end();iter++){
        
        CCTouch * mytouch=(CCTouch *)(* iter);
        
        CCPoint pos=mytouch->getLocation();
        
        Ship* ship = dynamic_cast<Ship*>(_shipLayer->getActor()->objectAtIndex(0));
        if (ship) {
            ship->setShipTo(pos.x);
        }
        
        
        break;
    }
    }
}

void GameScene::ccTouchesEnded(CCSet * touchs,CCEvent * event)
{
    if (_ui->getNowButtonID() != -1) {
        _ui->GameUItouchesEnded(touchs, event);
        
        if (_ui->getNowButtonID() == BUTTON_GAME_PAUSE) {
            #if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
                    CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
            #else
                    CCDirector::sharedDirector()->end();
            #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                    exit(0);
            #endif
            #endif
        }
    }else{
    Ship* ship = dynamic_cast<Ship*>(_shipLayer->getActor()->objectAtIndex(0));
    if (ship) {
        if (ship->isState(Ship::ACT_WALK)) {
            ship->setState(Ship::ACT_STAND);
        }
        
    }
    }
    
}


void GameScene::onEnter()
{
    
    CCLayer::onEnter();
}

void GameScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void GameScene::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    
    
    CCLayer::onExit();
}

void GameScene::cycle(float delta)
{
    
    _time--;
    if (_time>=0) {
        _ui->setTime((int)(_time/30));
    }
    
    if (_isChange) {
        if (_fishLayer->getActor()->count() == 0) {
            
            _isChange = false;
            _nowDataInedxt++;
        }
    }else{
        addFish();
    }
    
    
    for (int i =0; i<_add_leaf.size(); ++i) {
        std::vector<int> nowdata= _add_leaf[i];
        nowdata[1]--;
        if (nowdata[1] == 0) {
            _leafLayer->addLeaf("leaf_1", nowdata[4], nowdata[2], nowdata[3]);
        }
    }
    
//    _addFishTime--;
//    if (_addFishTime<0) {
//        _addFishTime = Tools::randomIntInRange(30, 60);
//        
//        addFish(2);
//    }
//    _addSPFishTime--;
//    if (_addSPFishTime<0
////        && _fishLayer->getActor()->count() == 0
//        ) {
//        _addSPFishTime = Tools::randomFloatInRange(120, 200);
//       
//        addDolphin();
//        addLightFish();
//        addTortoise();
//
//        addWhale();
//        addEatFish();
//
//        addShark();
//
//        addSwordFish();
//
//        addStrong();
//
//        addEle();
//        
//        _leafLayer->addLeaf("leaf_1", Leaf::DIR_RIGHT, 5, 200);
//        
//    }
   
    cycleFishs();
   
    cycleRocks();
    
    cycleLeafs();
}



void GameScene::addFish(int id)
{
    _fishLayer->addFish(id, Tools::randomFloatInRange(3, 7), Tools::randomIntInRange(Fish::DIR_LEFT, Fish::DIR_RIGHT+1), ("fish_"+Tools::intToString(id)).c_str());

}

void GameScene::draw()
{
//    ccDrawColor4B(0xff, 0xff, 0x00, 0);
//    glLineWidth(1.0f);
//
//    CCArray* fishSet = _fishLayer->getActor();
//
//    for (int i = 0; i<fishSet->count(); ++i) {
//        Fish* fish =(Fish*) fishSet->objectAtIndex(i);
//
//        CCRect rect1 = fish->getBodyRect(2);
//        
//    
////        CCLOG("x : %f y : %f w : %f h : %f",rect1.origin.x,rect1.origin.y,rect1.size.width,rect1.size.height);
//        ccDrawRect(ccp(rect1.origin.x,rect1.origin.y), ccp(rect1.origin.x+rect1.size.width, rect1.origin.y+rect1.size.height));
//        
////        ccDrawRect(ccp(rect1.origin.x,rect1.origin.y), ccp(rect1.origin.x+rect1.size.width, rect1.origin.y+rect1.size.height));
//        
////        ccDrawCircle(ccp(fish->getBone("pull")->getWorldInfo()->x+fish->getPositionX(), fish->getBone("pull")->getWorldInfo()->y+fish->getPositionY()), 15, 360, 10, true);
//        
//    }
//
//    Ship* ship = (Ship*) _shipLayer->getActor()->objectAtIndex(0);
//    
//    CCRect rect2 = ship->getHookLine();
//    
////    ccDrawRect(ccp(rect2.origin.x+ship->getPositionX(),rect2.origin.y+ship->getPositionY()), ccp(rect2.origin.x+ship->getPositionX()+rect2.size.width, rect2.origin.y+ship->getPositionY()+rect2.size.height));
//    
//    ccDrawRect(ccp(rect2.origin.x,rect2.origin.y), ccp(rect2.origin.x+rect2.size.width, rect2.origin.y+rect2.size.height));
//    
////    ccDrawCircle(ccp(ship->getPositionX()+ ship->getHookDx(), ship->getPositionY()+ ship->getHookDy()), 15, 360, 10, true);
}

bool GameScene::canHook(){
    return true;
}



void GameScene::cycleFishs()
{
    
    CCArray* fishs = _fishLayer->getActor();
    
    for (int i = 0 ; i<fishs->count(); ++i) {
        Fish* fish = (Fish*) fishs->objectAtIndex(i);
        
        if (fish->isFishDead()) {
            
            
            if (fish->getDeadType() == Fish::HOOK_DEAD||fish->getDeadType() == Fish::POW_DEAD) {
                if (fish->getShipID()>=0&&fish->getShipID()<_shipLayer->getActor()->count()) {
                    
//                    CCLOG("?!?! id : %i type : %i shipid : %i",fish->getID(),fish->getDeadType(),fish->getShipID());
                    
                    Ship* ship = (Ship*)_shipLayer->getActor()->objectAtIndex(fish->getShipID());
                    ship->addScore(fish->getScore());
//                    CCLOG("sc : % i ",ship->getScore());
                    
                    setUIScroe(ship->getScore());
                    
                }
            }
            
            
    
            continue;
        }
        
        CCArray* ships = _shipLayer->getActor();
        
        for (int k = 0; k < ships->count(); ++k) {
            
            shipAndFish((Ship*) ships->objectAtIndex(k), fish, k);
            
        }
        
        if (fish->issetXY()) {
            
            Ship* ship;
            
            if (fish->getShipID() != -1) {
                ship = (Ship*) ships->objectAtIndex(fish->getShipID());
                
            }
            
            if (ship) {
                
                fish->setXY(ship->getPositionX()+ ship->getHookDx()-6,ship->getPositionY()+ship->getHookDy()+10);
                
            }
        }
        
    }
}

void GameScene::shipAndFish(Ship *ship, Fish *fish, int i)
{
    if (fish->isNormalFish()) {
        
        if (ship->isCanMove()  && isHookFish(ship,fish)) {
            
            if (fish->isHooked()) {
                
                ship->hookFish(fish);
                fish->setShipID(i);
            }
            
        }
        
    }
    
    
    if (fish->isDolphin()) {
        if (ship->isCanMove()  && isHookFish(ship,fish) && fish->isState(Fish::ACT_STATE_WALK)) {
            useDolphin(fish);
            fish->setShipID(i);
            ship->hookFish();
            
        }
        
        if (fish->isState(Fish::ACT_STATE_DOLPHIN_ATK)) {
            useFishAtk(fish);
            
        }
    }
    
    if (fish->isLightFish()) {
        if (fish->isState(Fish::ACT_STATE_LIGHT)) {
            useFishAtk(fish);
            
        }
        
        if (ship->isCanMove()  && isHookFish(ship,fish) && fish->isState(Fish::ACT_STATE_WALK)) {
            fish->setShipID(i);
            useLightFish(fish);
            ship->hookFish();
        }
    }
    
    if (fish->isTortoise()) {
        
        
        if (ship->isCanMove()  && isHookFish(ship,fish) && fish->isState(Fish::ACT_STATE_WALK)) {
            
            fish->setShipID(i);
            
            useTortoise(fish);
            
            ship->hookFish();
            
        }
        
        if (fish->isState(Fish::ACT_STATE_TORTOISE)) {
            useFishAtk(fish);
        }
    }
    
    if (fish->isWhale()) {
        
       
        if (fish->isState(Fish::ACT_STATE_WALK) && ship->isShipNormal()) {
            
                         
            if (fish->getDir()==Fish::DIR_LEFT) {
                if (fish->getX() - ship->getX() < 200 && fish->getX() - ship->getX() > 100) {
                    
                    fish->setStartPos(ship->getX()-200, fish->getY());
                    
                    fish->setDes(ship->getX(), ship->getY()-60, 1);
                    
                    fish->setState(Fish::ACT_STATE_GOTOSHIP);
                    
                    
                }
            } else {
                if (ship->getX() - fish->getX() < 200 && ship->getX() - fish->getX() > 100) {
                    
                    fish->setStartPos(ship->getX()+200, fish->getY());
                    
                    fish->setDes(ship->getX(), ship->getY()-60, 1);
                    
                    fish->setState(Fish::ACT_STATE_GOTOSHIP);
                    
                    
                }
            }
            
        }
        
        if (fish->isState(Fish::ACT_STATE_ZHUANG_STAY)) {
            
            if (ship->isShipNormal() && waterCollideShip(fish,ship)) {
                
                
                
                fish->setState(Fish::ACT_STATE_ZHUANG_ATK);
                fish->setAnim(Fish::ANIM_ATK);
                ship->setState(Ship::ACT_FLY);
                
                ship->hookFish();
                
                ship->setw_Fish(fish);
                
            }
        }
    }
    
    if (fish->isEat()) {
        
        if (fish->isState(Fish::ACT_STATE_WALK)  && ship->isShipNormal()) {
            
            if (fish->getDir()==Fish::DIR_LEFT) {
                if ((fish->getX() - ship->getX() < 200 && fish->getX() - ship->getX() > 100) && fish->getX() - ship->getX() > 0) {
                    
                    fish->setAY(2.7f);
                    
                    fish->setSpeedY(43 + 10 * (fish->getY() - (Fish::FISH_Y_MIN + 10)) / (Fish::FISH_Y_MAX - (Fish::FISH_Y_MIN + 10)));
                    
                    fish->setState(Fish::ACT_STATE_HAN_UP) ;
                    
                    fish->setAnim(Fish::ANIM_ATK_READY);
                    
                    fish->setRotation(90);
                    
                    fish->setOLDY(fish->getY());
                }
            } else {
                if ((ship->getX() - fish->getX() < 200 && ship->getX() - fish->getX() > 100) && ship->getX() - fish->getX() > 0) {
                    
                    fish->setAY(2.7f);
                    
                    fish->setSpeedY(43 + 10 * (fish->getY() - (Fish::FISH_Y_MIN + 10)) / (Fish::FISH_Y_MAX - (Fish::FISH_Y_MIN + 10)));
                    
                    fish->setState(Fish::ACT_STATE_HAN_UP) ;
                    
                    fish->setAnim(Fish::ANIM_ATK_READY);
                    
                    fish->setRotation(-90);
                    
                    fish->setOLDY(fish->getY());
                }
            }
            
        }
        
        if (fish->isState(Fish::ACT_STATE_HAN_UP)) {
            
            if (!fish->isState(Fish::STATE_DEAD) && fish->getSpeedY() < 0 && ship->isShipNormal() && fish->getBodyRect().intersectsRect(ship->getBodyRect(1))) {
                
                fish->setRotation(0);
                
                fish->setAnim(Fish::ANIM_ATK);
                
                
                fish->setState(Fish::ACT_STATE_HAN_ATK);
                
                
                ship->setState(Ship::ACT_EATED);
                
                fish->setDeadTime(40);
                ship->setStop(40);
                
                ship->shipOnAtk();
                
                
            }
            
        }
        
        if (fish->isState(Fish::ACT_STATE_HAN_ATK)) {
            
            fish->setXY(ship->getEatPos().x, ship->getEatPos().y);
        }
    }
    
    
    if (fish->isShark()) {
        if (fish->isState(Fish::ACT_STATE_WALK)) {
            
            CCArray* fishs = _fishLayer->getActor();
            
            
            for (int j = 0; j < fishs->count(); j++) {
                
                Fish* fish2 = (Fish*) fishs->objectAtIndex(j);
                
                if (fish2->getType() != fish->getType() && !fish2->isState(Fish::STATE_DEAD) && fish2->getBodyRect().intersectsRect(fish->getBodyRect(1))) {
                    
                    if (fish2->getType() != Fish::SHARK) {
                        
                        if (fish2->isWhale()) {
                            
                            CCArray* ships = _shipLayer->getActor();
                            
                            for (int k = 0; k < ships->count(); ++k) {
                                
                                Ship* ship3 = (Ship*) ships->objectAtIndex(k);
                                
                                if (ship3->getw_Fish() == fish2 &&
                                    
                                     (
                                      fish2->isState(Fish::ACT_STATE_ZHUANG_ATK) ||
                                      fish2->isState(Fish::ACT_STATE_ZHUANG_END)
                                      
                                      ) &&
                                    
                                    ship3->isState(Ship::ACT_FLY)
                                    
                                    ) {
                                    ship3->setState(Ship::ACT_FALL) ;
                                    //										ship3.setNormal();
                                }
                                
                            }
                            
                        }
                        
                        if (fish2->isStrong()) {
                            
                            CCArray* ships = _shipLayer->getActor();
                            
                            for (int k = 0; k < ships->count(); ++k) {
                                
                                Ship* ship3 = (Ship*) ships->objectAtIndex(k);
                                
                                if (ship3->getw_Fish() == fish2 && fish2->isState(Fish::ACT_STATE_DEN) ) {
                                    ship3->setNormal();
                                    ship3->clearHook();
                                }
                                
                            }
                            
                        }
                        
                        fish2->setDeadType(Fish::OWN_DEAD);
                        fish2->setState(Fish::STATE_DEAD);
                        _effectLayer->addEffect(Effect::TYPE_OVER_DEAD,"fishbone",fish2->getPosition(),fish2->getDir() == Fish::DIR_LEFT);
                        
                        if (fish2->getCurrentMovementID() != "Animation8"||fish2->getCurrentMovementID() != "Animation7") {
                            fish->setAnim(Fish::ANIM_ATK);
                            
                        }
                        
                    }
                }
                
            }
        }
    }
    
    
    if (fish->isSword()) {

        if (ship->isShipNormal() && fish->isState(Fish::ACT_STATE_WALK)  && ship-> getHookLine().intersectsRect(fish->getBodyRect(2))) {
            
            ship->setCutHookPos();
            
            ship->setCutHookY(fish->getBodyRect(2).getMidY());
            
            ship->setState(Ship::ACT_CUT_LINE) ;
            
            ship->shipOnAtk();
            
            ship->setStop(40);
        }
    }
    
    
    if (fish->isStrong()) {
        
        if (ship->isShipNormal() && fish->isState(Fish::ACT_STATE_WALK) && ship-> getHookLine().intersectsRect(fish->getBodyRect(1))) {
            
            ship->setState(Ship::ACT_PULL);
            
            fish->setState(Fish::ACT_STATE_DEN);
            fish->setAnim(Fish::ANIM_ATK);
            ship->setw_Fish(fish);
            
            ship->setCutHookPos();
            
            ship->setHookUp();
            
            ship->shipOnAtk();
        }
        
        if (ship->getw_Fish() == fish && fish->isState(Fish::ACT_STATE_DEN) ) {
            
            ship->setPullPos(CCPointMake(fish->getBone("pull")->getWorldInfo()->x+fish->getPositionX()-ship->getPositionX(), fish->getBone("pull")->getWorldInfo()->y+fish->getPositionY()-ship->getPositionY()));
            
            
            
            if (fish->getDir() == Fish::DIR_RIGHT) {
                if (ship->isPlayer()) {
                    if (fish->getPositionX() - ship->getPositionX() > 100) {
                        ship->setX( fish->getPositionX() - 100);
                    }
                    
                }else{
                    
                    if (fish->getPositionX() - ship->getPositionX() > -45) {
                        ship->setX(fish->getPositionX()+45);
                    }
                    
                }
                
                
                if (ship->getBodyRect().getMaxX() > _screenSize.width) {
                    ship->setX(_screenSize.width-ship->getBodyRect().size.width*0.5);
                    ship->setState(Ship::ACT_STAND);
                    ship->changeToNohurt();
                    
                    ship->clearHook();
                    fish->setGo();
                }
                
            } else {
                
                if (ship->isPlayer()) {
                    
                    if (ship->getPositionX() - fish->getPositionX() > 100) {
                        ship->setX(fish->getPositionX() + 100);
                    }
                    
                }else{
                    if (ship->getPositionX() - fish->getPositionX() > 245) {
                        ship->setX(fish->getPositionX()+245);
                    }
                }
                
                
                if (ship->getBodyRect().getMinX() < 0) {
                    ship->setX(ship->getBodyRect().size.width*0.5);
                    ship->setState (Ship::ACT_STAND);
                    ship->changeToNohurt();
                    ship->clearHook();
                    fish->setGo();
                }
            }
            
        }
        
    }
    
    if (fish->isEle() && ship->isShipNormal() && fish->isState(Fish::ACT_STATE_WALK)   && isHookFish(ship,fish)) {
        
        fish->setAnim(Fish::ANIM_ATK);
        
        fish->setStayTime(40);
        
        fish->setState(Fish::ACT_STATE_SHOCK);
        
        ship->setStop(40);
        
        ship->setState(Ship::ACT_ELE);
        
        ship->setHookUp();
        
        ship->shipOnAtk();
        
        ship->playWithIndex(1);
        
    }
}

bool GameScene::isHookFish(Ship *ship, Fish *fish)
{
    
    if (fish->isState(Fish::ACT_STATE_HOOKED) || fish->isFishDead() || ship->isState(Ship::ACT_SHOCKED)) {
        return false;
    }
    
    return isCollideFish(ship,fish);
}

bool GameScene::waterCollideShip(Fish *fish, Ship *ship)
{
//    CCRect waterRect = CCRectMake(fish->getPositionX()+fish->getBodyRect(1).origin.x, fish->getPositionY()+fish->getBodyRect(1).origin.y, fish->getBodyRect(1).size.width, fish->getBodyRect(1).size.height);
    
    return fish->getBodyRect(1).intersectsRect(ship->getBodyRect(2));
}

bool GameScene::isCollideFish(Ship *ship, Fish *fish)
{
    CCRect shipRect = CCRectMake(ship->getPositionX()+ship->getHookAnim()->boundingBox().origin.x, ship->getPositionY()+ship->getHookAnim()->boundingBox().origin.y, ship->getHookAnim()->boundingBox().size.width, ship->getHookAnim()->boundingBox().size.height);
    
    return shipRect.intersectsRect(fish->getBodyRect());
}

bool GameScene::isCollideFish(Fish *fish1, Fish *fish2)
{

    return fish1->getBodyRect().intersectsRect(fish2->getBodyRect());
}


void GameScene::addDolphin(){
    this->addFish(Fish::DOLPHIN);
}

void GameScene::useDolphin(Fish* fish)
{
    fish->setAnim(Fish::ANIM_ATK_READY);
    
    fish->setState(Fish::ACT_STATE_DOLPHIN_READY);
    
}

void GameScene::addLightFish(){
    this->addFish(Fish::LIGHTFISH);
}

void GameScene::useLightFish(Fish* fish)
{
    fish->setAnim(4);
    
    fish->setState(Fish::ACT_STATE_LIGHT_READY);
    
}

void GameScene::addTortoise(){
    this->addFish(Fish::TORTOISE);
}

void GameScene::useTortoise(Fish *fish)
{
    fish->setAnim(4);
    
    fish->setState(Fish::ACT_STATE_TORTOISE_READY);
    
}

void GameScene::addWhale()
{
    addFish(Fish::WHALE);
}

void GameScene::addEatFish()
{
    addFish(Fish::EATFISH);
}

void GameScene::addShark()
{
    addFish(Fish::SHARK);
}

void GameScene::addSwordFish()
{
    addFish(Fish::SWORDFISH);
}

void GameScene::addStrong()
{
    addFish(Fish::STRONGFISH);
}

void GameScene::addEle()
{
    addFish(Fish::ELEFISH);
}


void GameScene::useFishAtk(Fish* fish) {
    
    CCArray* fishs = _fishLayer->getActor();
    
    for (int j = 0; j < fishs->count(); j++) {
        
        Fish* fish2 = (Fish*) fishs->objectAtIndex(j);
        
        if (!fish2->isFishDead() && isCollideFish(fish2,fish) && fish2!=fish) {
            
            if (fish2->isUseFish()) {
                
                useFish(fish2);
                
            }else if (!fish2->isHook() && !fish2->isShark()) {
                
                
                if (fish2->isWhale()) {
                    
                    CCArray* ships = _shipLayer->getActor();
                    
                    for (int k = 0; k < ships->count(); ++k) {
                        
                        Ship* ship3 = (Ship*) ships->objectAtIndex(k);
                        
                        if (ship3->getw_Fish() == fish2 &&
                            
                            (
                             fish2->isState(Fish::ACT_STATE_ZHUANG_ATK) ||
                             fish2->isState(Fish::ACT_STATE_ZHUANG_END)
                             
                             ) &&
                            
                            ship3->isState(Ship::ACT_FLY)
                            
                            ) {
                            ship3->setState(Ship::ACT_FALL) ;
                            
                        }
                        
                    }
                    
                }
                
                if (fish2->isStrong()) {
                    
                    CCArray* ships = _shipLayer->getActor();
                    
                    for (int k = 0; k < ships->count(); ++k) {
                        
                        Ship* ship3 = (Ship*) ships->objectAtIndex(k);
                        
                        if (ship3->getw_Fish() == fish2 && fish2->isState(Fish::ACT_STATE_DEN) ) {
                            ship3->setNormal();
                            ship3->clearHook();
                        }
                        
                    }
                    
                }

                
                fish2->setShipID(fish->getShipID());
                fish2->setDead(true);
                fish2->setDeadType(Fish::HOOK_DEAD);
                
            }
        }
        
    }
}

void GameScene::useFish(Fish* fish) {
    if (fish->isState(Fish::ACT_STATE_WALK)) {
        
        switch (fish->getID()) {
            case Fish::DOLPHIN:
                useDolphin(fish);
                break;
            case Fish::LIGHTFISH:
                useLightFish(fish);
                break;
            case Fish::TORTOISE:
                useTortoise(fish);
                break;
        }
    }
}

void GameScene::setUIScroe(int sc)
{
    
    if (sc<=_mubiao_scroe[0]) {
        _ui->setScoreTiao(((float)(sc*100)/(float)_mubiao_scroe[0])*0.33333);
    }else if(sc>_mubiao_scroe[0]&&sc<=_mubiao_scroe[1]){
        _ui->setScoreTiao((((float)((sc-_mubiao_scroe[0])*100)/(float)(_mubiao_scroe[1]-_mubiao_scroe[0]))*0.33333)+33.3333);
    }else if(sc>_mubiao_scroe[1]&&sc<=_mubiao_scroe[2]){
        _ui->setScoreTiao((((float)((sc-_mubiao_scroe[1])*100)/(float)(_mubiao_scroe[2]-_mubiao_scroe[1]))*0.33333)+66.6666);
    }else if(sc>_mubiao_scroe[2]){
        _ui->setScore(100);
    }
    _ui->setScore(sc);
    
}

void GameScene::setFishToRun()
{
    CCArray* fishs = _fishLayer->getActor();
    
    for (int i = 0 ; i<fishs->count(); ++i) {
        Fish* fish = (Fish*) fishs->objectAtIndex(i);
        
        fish->setGo();
    }
}

void GameScene::addFish()
{
//    CCLOG("???!!! %i",_nowDataInedxt);
    std::vector<int> nowdata= _data[_nowDataInedxt];
    
//    if (_nowDataInedxt == 1) {
//        CCLOG("now : %i",nowdata[0]);
//    }
    
    if (nowdata[0] == ADD_NORMAL) {
        _addFishTime++;
        if (_addFishTime >= nowdata[2]) {
            _addFishTime =0;
            int num =(nowdata.size()-4)/2;
            for (int i = 0; i<nowdata[1]; ++i) {
                int chu = Tools::randomIntInRange(0, 100);
                int fishIndext = 0;
                int up=0;
                
                for (int j = 0; j<num; ++j) {
                    if (j==0) {
                        if (0<=chu && chu<nowdata[i*2+5]) {
                            fishIndext=j;
                            break;
                        }
                    }else{
                        up+=nowdata[(i-1)*2+5];
                        
                        if (up<=chu&&chu<=nowdata[i*2+5]+up) {
                            fishIndext = j;
                            break;
                        }
                    }
                }
                
                addFish(nowdata[fishIndext*2+4]);
                 _fishNum++;
            }
            
           
            
            if (_fishNum >= nowdata[3]) {
                _fishNum = 0;
                _isChange = true;
                setFishToRun();
            }
        }
    }else if(nowdata[0] == ADD_FORMAT){
       
        _isChange = true;
        if (_fishLayer->getActor()->count() == 0) {
            for (int i = 0; i<(nowdata.size()-1)/4; ++i) {
                if (nowdata[i*4+4]>0) {
                    addFormatFish(nowdata[1+i*4], nowdata[2+i*4], nowdata[3+i*4]);
                    nowdata[i*4+4]--;
                    _isChange = false;
                }
                
            }
        }
        
        
    }
}

void GameScene::addFormatFish(int id, int speed, int dir)
{
    CCNode* node = SceneReader::sharedSceneReader()->createNodeWithSceneFile(("data/form_"+Tools::intToString(id)+".csb").c_str());
    
//    CCNode* node = SceneReader::sharedSceneReader()->createNodeWithSceneFile("data/test.json");
    
    CCArray* all =  node->getChildren();
    
    
    CCLOG("id : %i speed % i dir %i",id,speed,dir);
    
    for (int i = 0; i<all->count(); ++i) {
        
        CCNode* fish =dynamic_cast<CCNode*> (all->objectAtIndex(i));
        
        CCLOG("fish %i",fish->getTag());
        
        CCArmature* arm = (CCArmature *)((CCComRender*) fish->getComponent("CCArmature"))->getNode();
        string str = arm->getName().substr(0,arm->getName().find('.'));
        int exitType = Fish::EXIT_DEAD_RIGHT;
        
        CCPoint pos = fish->getPosition();
        
        if (dir == 0) {
            exitType = Fish::EXIT_DEAD_LEFT;
            pos = CCPointMake(fish->getPositionX()+_screenSize.width, fish->getPositionY());
        }
        
        
        
        _fishLayer->addFish(id, speed, dir, (str).c_str(),exitType,pos);

    }
}

void GameScene::cycleRocks()
{
    CCArray* rocks = _rockLayer->getActor();
    
    CCArray* ships = _shipLayer->getActor();
    
    

    
    for (int i = 0; i<rocks->count(); ++i) {
        Rock* rock = (Rock*) rocks->objectAtIndex(i);
        
        for (int k = 0; k < ships->count(); ++k) {
            
            Ship* ship = (Ship*) ships->objectAtIndex(k);
            
            CCRect shipRect = CCRectMake(ship->getPositionX()+ship->getHookAnim()->boundingBox().origin.x, ship->getPositionY()+ship->getHookAnim()->boundingBox().origin.y, ship->getHookAnim()->boundingBox().size.width, ship->getHookAnim()->boundingBox().size.height);
            
            
            if ( shipRect.intersectsRect(rock->getBodyRect())) {
                
                if (ship->getHookDir() == Ship::HOOK_DIR_DOWN){
                    rock->subHp();
                    ship->setHookUp();
                }else{
//                    ship->shipOnAtk();
                }
            }
        }
    }
}

void GameScene::cycleLeafs()
{
    CCArray* leafs = _leafLayer->getActor();
    
    CCArray* ships = _shipLayer->getActor();
    
    for (int i = 0; i<leafs->count(); ++i) {
        Leaf* leaf = (Leaf*) leafs->objectAtIndex(i);
        
        for (int k = 0; k < ships->count(); ++k) {
            
            Ship* ship = (Ship*) ships->objectAtIndex(k);
            
            CCRect shipRect = CCRectMake(ship->getPositionX()+ship->getHookAnim()->boundingBox().origin.x, ship->getPositionY()+ship->getHookAnim()->boundingBox().origin.y, ship->getHookAnim()->boundingBox().size.width, ship->getHookAnim()->boundingBox().size.height);
            
            
            if ( shipRect.intersectsRect(leaf->getBodyRect())) {
                
                if (ship->getHookDir() == Ship::HOOK_DIR_DOWN){
                    leaf->subHp();
                    ship->setHookUp();
                }else{
                    //                    ship->shipOnAtk();
                }
            }
        }
    }
}