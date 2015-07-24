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
#include "LoadingScreen.h"

GameScene* GameScene::_instance = NULL;



const static int BG_Z = -80;

const static int SHIP_Z = -50;

const static int SHELL_Z = -35;

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

CCScene* GameScene::scene(int player ,int lev)
{
    
    CCScene* scene = CCScene::create();
    
    GameScene* layer = GameScene::create(player,lev);
    
    scene->addChild(layer);
    
    return scene;
}

GameScene::GameScene():_addFishTime(0),_addSPFishTime(0),_time(FPS*60),_isChange(false),_nowDataInedxt(0),_fishNum(0),_begin(NULL),_pass_scroe(0),_pause(NULL),_maxScore(1000),_badEnd(NULL),_star(0),_sucEnd(NULL)
{
    
}

GameScene::~GameScene()
{
    CC_SAFE_DELETE(_flyNum);
    CC_SAFE_DELETE(_formatData);
}

GameScene* GameScene::create(int player ,int lev)
{
    GameScene* game = new GameScene();
    
    if(game && game->init(player,lev)) {
        game->autorelease();
        return game;
    }
    
    CC_SAFE_DELETE(game);
    return NULL;
}

bool GameScene::init(int player ,int lev)
{
    
    if (CCLayer::init())
    {
       
        
        _screenSize = CCDirector::sharedDirector()->getWinSize();
        
        _instance = this;
        
        _nowPlayer = player;
        _nowLev = lev;
        
        _formatData = CCArray::create();
        _formatData->retain();
        
        _flyNum = CCArray::create();
        _flyNum->retain();
        
        
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_1.csb");
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_2.csb");
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_3.csb");
//        
        
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_1110.csb");
//        
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_1120.csb");
//        
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_1130.csb");
//        
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_1140.csb");
//        
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_1150.csb");
//        
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_1160.csb");
//        
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_1170.csb");
//        
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_1180.csb");
//        
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fish_1190.csb");
        
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/whaleWater.csb");
        
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fishbone.csb");
        
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/fishbone.ExportJson");
        
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("ship/ship_1.csb");
        
       
      
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/rock_1.ExportJson");
        
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/leaf_1.csb");
        
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
        
        int sex = Ship::WOMAN;
        if (player == 2||player == 4||player == 5) {
            sex = Ship::MAN;
        }
        
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(("ship/player_"+Tools::intToString(player+1)+".ExportJson").c_str());
        
        _shipLayer->addShip(Ship::TYPE_PLAYER, ("player_"+Tools::intToString(player+1)).c_str(),sex,0);
        
        
        
        schedule(schedule_selector(GameScene::cycle));
        
        _fishLayer = FishManage::create();
        _fishLayer -> setAutoDead(false);
        addChild(_fishLayer,FISH_Z);
        
        _rockLayer = RockManage::create();
        
        addChild(_rockLayer,ROCK_Z);
        
        _leafLayer = LeafManage::create();
        
        addChild(_leafLayer,LEAF_Z);

        _bgLayer = BackGround::create();
        
        addChild(_bgLayer,BG_Z);

        
        
        _effectLayer = EffectManage::create();
        
        addChild(_effectLayer,EFFECT_Z);
        
        _shellLayer = ShellManage::create();
        
        addChild(_shellLayer,SHELL_Z);
        
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/shell_1.csb");
        
//        _shellLayer->addShell("shell_1", CCPointMake(200, 200), 1);
        
        
        
        BinaryReadUtil* _IO_read = BinaryReadUtil::create(("data/level_"+Tools::intToString(_nowLev)+".data").c_str());
        
        int len = _IO_read -> readInt();
       
        
        if (false) {
            for (int i = 0; i<len; ++i) {
                int len2 = _IO_read->readInt();
                for (int j = 0; j<len2; ++j) {
                    CCLOG("%i",_IO_read -> readInt());
                }
                CCLOG("////////////////");
            }
            
        }else{
        
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
                if(type == ADD_NORMAL){
                    
                    int num =(data_1.size()-4)/2;
                    
                    for (int k = 0; k<num; ++k) {
                        
                        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(("fish/fish_"+Tools::intToString(data_1[k*2+4])+".csb").c_str());
                        
                    }
                    
                }
                
                if (type == ADD_FORMAT) {
                    int num =(data_1.size()-1)/4;
                    for (int k = 0; k<num; ++k) {
                         CCNode* node = SceneReader::sharedSceneReader()->createNodeWithSceneFile(("data/form_"+Tools::intToString(data_1[k*4+1])+".json").c_str());
//                        CCNode* node = SceneReader::sharedSceneReader()->createNodeWithSceneFile(("data/form_"+Tools::intToString(1)+".csb").c_str());
                        data_1[k*4+1] =_formatData->count();
                        _formatData->addObject(node);
                        
                    }
                    
                    
                }
                
                _data.push_back(data_1);
            }else if(type == SET_TIME){
                _time = _IO_read->readInt();
            }else if(type == ADD_ROCK){
                int id =_IO_read->readInt();
                CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/rock_1.ExportJson");
                CCPoint pos = CCPointMake(_IO_read->readInt(), _IO_read->readInt());
                int hp =_IO_read->readInt();
                _rockLayer->addRock("rock_1", hp, pos);
            }else if(type == ADD_LEAF){
               
                CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fish/leaf_1.csb");
                std::vector<int> data;
                data.push_back(type);
                
                for (int j = 0; j<len2-1; ++j) {
                    data.push_back(_IO_read->readInt());
                }
                
                _add_leaf.push_back(data);
            }else if(type == ADD_SHELL){
                
                CCPoint pos =CCPointMake(_IO_read->readInt(), _IO_read->readInt()) ;
                int open_time = _IO_read->readInt();
                int close_time = _IO_read->readInt();
                
                int num =(len2-5)/2;
                for (int k = 0; k<num; ++k) {
                    _IO_read->readInt();
                    _IO_read->readInt();
                }
                
            }else if(type == ADD_AI){
                _IO_read->readInt();
                _IO_read->readInt();
                
                CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("ship/npc_1.csb");
                _shipLayer->addShip(Ship::TYPE_AI, "npc_1", Ship::WOMAN,_IO_read->readInt());
                
                _IO_read->readInt();
                _IO_read->readInt();
                
                for (int j = 0; j< len2-6; ++j) {
                    _IO_read->readInt();
                }
            }else if(type == ADD_OBJ){
                _pass_scroe =_IO_read->readInt();
                
                
                _mubiao_scroe.push_back(_IO_read->readInt());
                _mubiao_scroe.push_back(_IO_read->readInt());
                _mubiao_scroe.push_back(_IO_read->readInt());
                
                _suc_type = _IO_read->readInt();
        
                _suc_add = _IO_read->readInt();
                
                _suc_num = _IO_read->readInt();
                
            }
            
            //            CCLOG("、、、、、");
        }
        }
        _time = 60;
//        _mubiao_scroe.push_back(100);
//        _mubiao_scroe.push_back(500);
//        _mubiao_scroe.push_back(1000);
//        _pass_scroe =50;
//        _suc_type = 0;
//        _suc_add = 2;
//        _suc_num = 10;
        
        
        _ui = GameUI::create();
        
        _ui->setTime((int)(_time/30));
        
        addChild(_ui,UI_Z);
        
        _ui->addMubiaoScore(_mubiao_scroe);
        
        
        
        this->setTouchEnabled(true);
        
//        std::vector<int> nowdata= _data[_nowDataInedxt];
//        for (int i =0; i<nowdata.size(); ++i) {
//            CCLOG("%i",nowdata[i]);
//        }
        
//       CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
        
        
        
//        _rockLayer->addRock("rock_1", 5, CCPointMake(200, 200));
        
        
//        CCArmature* rock = CCArmature::create("rock_1");
//        rock->setPosition(CCPointMake(200, 200));
//        addChild(rock,100);
        
        AUDIO->playSfx("music/startRound");
         CCLOG("type : %i",_suc_type);
        _begin = GameBegin::create(_pass_scroe, _suc_type, _suc_add , _suc_num);
//        _begin->setPosition(_screenSize.width*0.5, _screenSize.height*0.5);
        
        _begin->setPosition(_screenSize.width*0.5, _screenSize.height*1.5);
        
        CCMoveTo* mov1 = CCMoveTo::create(0.7, ccp(_screenSize.width*0.5, _screenSize.height*0.4));
        
        CCMoveTo* mov2 = CCMoveTo::create(0.1, ccp(_screenSize.width*0.5, _screenSize.height*0.5));
        
        CCSequence* sq = CCSequence::create(mov1,mov2,NULL);
        
        _begin->runAction(sq);
        
        addChild(_begin);
        
       
        
        
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
    
    if (_begin) {
        _begin->touchesBegan(touchs, event);
    }else if(_badEnd){
        _badEnd->touchesBegan(touchs, event);
    }else if(_sucEnd){
        _sucEnd->touchesBegan(touchs, event);
    }else if (_pause) {
        _pause->touchesBegan(touchs, event);
    }else if (_ui->GameUItouchesBegan(touchs, event)) {
        if (_ui->getNowButtonID()!=-1) {
            if(_ui->getNowButtonID() == BUTTON_GAME_LEFT){
                Ship* ship = dynamic_cast<Ship*>(_shipLayer->getActor()->objectAtIndex(0));
                if (ship) {
                    ship->setShipToNoHook(0);
                }
                
            }else if(_ui->getNowButtonID() == BUTTON_GAME_RIGHT){
                Ship* ship = dynamic_cast<Ship*>(_shipLayer->getActor()->objectAtIndex(0));
                if (ship) {
                    ship->setShipToNoHook(_screenSize.width);
                }
            }else if(_ui->getNowButtonID() == BUTTON_GAME_DO){
                
                Ship* ship = dynamic_cast<Ship*>(_shipLayer->getActor()->objectAtIndex(0));
                if (ship) {
                    ship->hook();
                }
                
            }
        }
    }else{
        if (!IS_ON_BUTTON) {
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
}



void GameScene::ccTouchesCancelled(CCSet * touchs,CCEvent * event)
{
    
    if (_begin) {
        _begin->touchesCancelled(touchs, event);
    }else if(_badEnd){
        
    }else if(_sucEnd){
        
    }else if (_pause) {
        _pause->touchesCancelled(touchs, event);
    }else if (_ui->getNowButtonID()!=-1) {
        _ui->GameUItouchesCancelled(touchs, event);
    }else{
        if (!IS_ON_BUTTON) {
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
    
}

void GameScene::ccTouchesMoved(CCSet * touchs,CCEvent * event)
{
    
    if (_begin) {
        _begin->touchesMoved(touchs, event);
    }else if(_badEnd){
        _badEnd->touchesMoved(touchs, event);
    }else if(_sucEnd){
        _sucEnd->touchesMoved(touchs, event);
    }else if (_pause) {
        _pause->touchesMoved(touchs, event);
    }else if (_ui->getNowButtonID() != -1) {
        _ui->GameUItouchesMoved(touchs, event);
    }else{
        
        if (!IS_ON_BUTTON) {
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
    
}

void GameScene::ccTouchesEnded(CCSet * touchs,CCEvent * event)
{
    
    if (_begin) {
        _begin->touchesEnded(touchs, event);
    }else if(_badEnd){
        _badEnd->touchesEnded(touchs, event);
    }else if(_sucEnd){
        _sucEnd->touchesEnded(touchs, event);
    }else if (_pause) {
        _pause->touchesEnded(touchs, event);
    }else if (_ui->getNowButtonID() != -1) {
        _ui->GameUItouchesEnded(touchs, event);
        
        if (_ui->getNowButtonID() == BUTTON_GAME_PAUSE) {
            if (!_pause) {
                CCDirector::sharedDirector()->pause();
                _pause = Pause::create();
                _pause->setPosition(ccp(_screenSize.width*0.5, _screenSize.height*0.5));
                addChild(_pause,100);
            }
            
        }else if(_ui->getNowButtonID() == BUTTON_GAME_ALLGET){
            allFishToDead(0);
        }
        
        Ship* ship = dynamic_cast<Ship*>(_shipLayer->getActor()->objectAtIndex(0));
        if (ship) {
            if (ship->isState(Ship::ACT_WALK)) {
                ship->setState(Ship::ACT_STAND);
            }
            
        }
        
    }else{
        if (!IS_ON_BUTTON) {
            Ship* ship = dynamic_cast<Ship*>(_shipLayer->getActor()->objectAtIndex(0));
            if (ship) {
                if (ship->isState(Ship::ACT_WALK)) {
                    ship->setState(Ship::ACT_STAND);
                }
                
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
    
    if (_badEnd) {
        if (_badEnd->getDead()==BadEnd::DEAD_TYPE_BACK) {
            removeChild(_badEnd, true);
            _badEnd=NULL;
            unschedule(schedule_selector(GameScene::cycle));
            removeAllChildren();
            std::vector<int> a;
            CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f, LoadingScreen::create(KScreenMap,  a)));
            
        }else if (_badEnd->getDead()==BadEnd::DEAD_TYPE_REST) {
            removeChild(_badEnd, true);
            _badEnd=NULL;

            _time=61*FPS;
            
        }else if (_badEnd->getDead()==BadEnd::DEAD_TYPE_PLAY) {
            removeChild(_badEnd, true);
            _badEnd=NULL;
            std::vector<int> lev;
            lev.push_back(_nowPlayer);
            lev.push_back(_nowLev);
            unschedule(schedule_selector(GameScene::cycle));
            removeAllChildren();
            CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f, LoadingScreen::create(KScreenGame, lev)));

        }
        return;
    }
    
    if (_sucEnd) {
        if (_sucEnd->getDead()==SucEnd::DEAD_TYPE_BACK) {
            removeChild(_sucEnd, true);
            _sucEnd=NULL;
            unschedule(schedule_selector(GameScene::cycle));
            removeAllChildren();
            std::vector<int> a;
            CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f, LoadingScreen::create(KScreenMap,  a)));
            
        }else if (_sucEnd->getDead()==SucEnd::DEAD_TYPE_NEXT) {
            removeChild(_sucEnd, true);
            _sucEnd=NULL;
            if (_nowLev == 71) {
                unschedule(schedule_selector(GameScene::cycle));
                removeAllChildren();
                std::vector<int> a;
                CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f, LoadingScreen::create(KScreenMap,  a)));
            }else{
                
                std::vector<int> lev;
                lev.push_back(_nowPlayer);
                lev.push_back(_nowLev+1);
                unschedule(schedule_selector(GameScene::cycle));
                removeAllChildren();
                CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f, LoadingScreen::create(KScreenGame, lev)));
            }
            
        }
        return;
    }
    
    if (_pause) {
       
        if (_pause->getDead()!=Pause::DEAD_TYPE_NODEAD) {
            if (_pause->getDead() == Pause::DEAD_TYPE_TOGAME) {
                removeChild(_pause, true);
                _pause=NULL;
            }else if(_pause->getDead() == Pause::DEAD_TYPE_BACK){
                removeChild(_pause, true);
                _pause=NULL;
                unschedule(schedule_selector(GameScene::cycle));
                removeAllChildren();
                std::vector<int> a;
                CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f, LoadingScreen::create(KScreenMap,  a)));
            }
            
        }
        
        return;
    }
    
    
    
    if (_begin) {
        if (_begin->getDead()!=GameBegin::DEAD_TYPE_NODEAD) {
            
            if (_begin->getDead() == GameBegin::DEAD_TYPE_TOGAME) {
                removeChild(_begin, true);
                _begin=NULL;
            }else if(_begin->getDead() == GameBegin::DEAD_TYPE_BACK){
                removeChild(_begin, true);
                _begin=NULL;
                unschedule(schedule_selector(GameScene::cycle));
                removeAllChildren();
                std::vector<int> a;
                CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f, LoadingScreen::create(KScreenMap,  a)));
            }
            
        }
        
        return;
    }
    
    _addFlyTime = 0;
    
    _time--;
    if (_time>=0) {
        _ui->setTime((int)(_time/FPS));
        
        if(_time == FPS*10){
           AUDIO->playSfx("music/lowTime");
        }
        
        if(_time == 0){
            setFishToRun();
            AUDIO->playSfx("music/endRound");
        }
    }else{
        
        if(_fishLayer&& _fishLayer->getActor()->count() == 0){
//            unschedule(schedule_selector(GameScene::cycle));
//            removeAllChildren();
//            std::vector<int> a;
//            CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f, LoadingScreen::create(KScreenMap,  a)));
            
            if(_star == 0){
                _badEnd=BadEnd::create();
                addChild(_badEnd);
            }else{
                _sucEnd = SucEnd::create();
                addChild(_sucEnd);
            }
            return;
        }
        
    }
    
    if (_isChange) {
        if (_fishLayer->getActor()->count() == 0) {
            
            _isChange = false;
            _nowDataInedxt++;
            
            if (_nowDataInedxt>=_data.size()) {
                _nowDataInedxt=0;
            }
        }
    }else{
        if (_time>0) {
            addFish();
        }
    }
    
    
    for (int i =0; i<_add_leaf.size(); ++i) {
//        std::vector<int> nowdata= _add_leaf[i];
        
        _add_leaf[i][1]--;
//        CCLOG("nowdata[1] %i",nowdata[1]);
        if (_add_leaf[i][1] == 0) {
            _leafLayer->addLeaf("leaf_1", _add_leaf[i][4], _add_leaf[i][2], _add_leaf[i][3]);
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
    
    for (int i = 0; i<_flyNum->count(); ++i) {
        FlyNum* num = (FlyNum*) _flyNum->objectAtIndex(i);
        if (num->getState() == FlyNum::STATE_DEAD) {
            Ship* ship =(Ship*) _shipLayer->getActor()->objectAtIndex(num->getShipID());
            ship->addScore(num->getNum());
            
            
            
            if (_shipLayer->getActor()->count()>1) {
//                Ship* ship =(Ship*) _shipLayer->getActor()->objectAtIndex(num->getShipID());
                setUIScroe(num->getShipID(),ship->getScore());
            }else{
//                Ship* ship =(Ship*) _shipLayer->getActor()->objectAtIndex(0);
                setUIScroe(ship->getScore());
            }
            
            _flyNum->removeObject(num);
            this->removeChild(num);
            i--;
            continue;
        }
    }
    
    _shipLayer->manageCycle(delta);
    _effectLayer->manageCycle(delta);
    _rockLayer->manageCycle(delta);
    _leafLayer->manageCycle(delta);
    _shellLayer->manageCycle(delta);
    
    
    
    
    
    cycleFishs(delta);
   
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



void GameScene::cycleFishs(float delta)
{
    
    CCArray* fishs = _fishLayer->getActor();
    
    for (int i = 0 ; i<fishs->count(); ++i) {
        Fish* fish = (Fish*) fishs->objectAtIndex(i);
        
        fish->cycle(delta);
        fish->actorCycle(delta);
        
        if (fish->isFishDead()) {
            
            
            
            if (fish->getDeadType() == Fish::HOOK_DEAD||fish->getDeadType() == Fish::POW_DEAD) {
                
                if (fish->getShipID()>=0&&fish->getShipID()<_shipLayer->getActor()->count()) {
                    
//                    CCLOG("?!?! id : %i type : %i shipid : %i",fish->getID(),fish->getDeadType(),fish->getShipID());
//                    Ship* ship = (Ship*)_shipLayer->getActor()->objectAtIndex(fish->getShipID());
//                    ship->addScore(fish->getScore());
////                    CCLOG("sc : % i ",ship->getScore());
//                    
//                    setUIScroe(ship->getScore());
                    if (_shipLayer->getActor()->count()>1) {
                        if (fish->getShipID()==0) {
                            addFlyNum(FlyNum::TYPE_NORMAL, fish->getScore(), fish->getShipID(), fish->getPosition(), ccp(_screenSize.width*0.75,_screenSize.height*0.95));
                        }else{
                            addFlyNum(FlyNum::TYPE_NORMAL2, fish->getScore(), fish->getShipID(), fish->getPosition(), ccp(_screenSize.width*0.75,_screenSize.height*0.9));
                        }
                        
                    }else{
                        addFlyNum(FlyNum::TYPE_NORMAL, fish->getScore(), fish->getShipID(), fish->getPosition(), ccp(_screenSize.width*0.75,_screenSize.height*0.9));
                    }
                    
                   
                    
                }
            }
            
            _fishLayer->removeActor(fish);
            
            i--;
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
                
                fish->setXY(ship->getPositionX()+ ((ship->getHookDx()-6)*ship->getScaleX()),ship->getPositionY()+ship->getHookDy()+10);
                
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
                if (ship->getSex() == Ship::MAN) {
                    AUDIO->playSfx("music/whaleShout");
                }else{
                    AUDIO->playSfx("music/whaleShout2");
                }
                
                
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
                
                fish->setShipID(i);
                ship->setState(Ship::ACT_EATED);
                
                fish->setDeadTime(40);
                ship->setStop(40);
                
                ship->shipOnAtk();
                
                AUDIO->playSfx("music/beiyao");
            }
            
        }
        
        if (fish->isState(Fish::ACT_STATE_HAN_ATK)) {
            Ship* ship12 = (Ship*) _shipLayer->getActor()->objectAtIndex(fish->getShipID());
            fish->setXY(ship12->getEatPos().x, ship12->getEatPos().y);
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
                        AUDIO->playSfx("music/shayu");
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
            AUDIO->playSfx("music/swordfishCutsLine");
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
                    
                    AUDIO->playSfx("music/boatDragEnds");
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
                    AUDIO->playSfx("music/boatDragEnds");
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
        AUDIO->playSfx("music/anguilla");
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
//    CCRect shipRect = CCRectMake(ship->getPositionX()+ship->getHookAnim()->boundingBox().origin.x, ship->getPositionY()+ship->getHookAnim()->boundingBox().origin.y, ship->getHookAnim()->boundingBox().size.width, ship->getHookAnim()->boundingBox().size.height);
//    
    return ship->getHookBody().intersectsRect(fish->getBodyRect());
}

bool GameScene::isCollideFish(Fish *fish1, Fish *fish2)
{

    return fish1->getBodyRect().intersectsRect(fish2->getBodyRect());
}

bool GameScene::isCollideFishAtk(Fish *fish1, Fish *fish2)
{
    
    return fish1->getBodyRect().intersectsRect(fish2->getBodyRect(1));
}


void GameScene::addDolphin(){
    this->addFish(Fish::DOLPHIN);
}

void GameScene::useDolphin(Fish* fish)
{
    
    AUDIO->playSfx("music/dolphinhit");
    
    fish->setAnim(Fish::ANIM_ATK_READY);
    
    fish->setState(Fish::ACT_STATE_DOLPHIN_READY);
    
}

void GameScene::addLightFish(){
    this->addFish(Fish::LIGHTFISH);
}

void GameScene::useLightFish(Fish* fish)
{
    AUDIO->playSfx("music/glimhit");
    fish->setAnim(4);
    
    fish->setState(Fish::ACT_STATE_LIGHT_READY);
    
}

void GameScene::addTortoise(){
    this->addFish(Fish::TORTOISE);
}

void GameScene::useTortoise(Fish *fish)
{
    AUDIO->playSfx("music/tortoisehit");
    fish->setAnim(4);
    fish->setExitDeadType(Fish::EXIT_DEAD_NORMAL);
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
        
        if (!fish2->isFishDead() && isCollideFishAtk(fish2,fish) && fish2!=fish) {
            
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
                AUDIO->playSfx("music/glimattack");
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
    
    if (sc<_mubiao_scroe[0]) {
        _ui->setScoreTiao(((float)(sc*100)/(float)_mubiao_scroe[0])*0.33333);
        _star = 0;
    }else if(sc>=_mubiao_scroe[0]&&sc<_mubiao_scroe[1]){
        _ui->setScoreTiao((((float)((sc-_mubiao_scroe[0])*100)/(float)(_mubiao_scroe[1]-_mubiao_scroe[0]))*0.33333)+33.3333);
        _star = 1;
    }else if(sc>=_mubiao_scroe[1]&&sc<_mubiao_scroe[2]){
        _ui->setScoreTiao((((float)((sc-_mubiao_scroe[1])*100)/(float)(_mubiao_scroe[2]-_mubiao_scroe[1]))*0.33333)+66.6666);
        _star = 2;
    }else if(sc>=_mubiao_scroe[2]){
        _ui->setScoreTiao(100);
        _star = 3;
    }
    _ui->setScore(sc);
    
}

void GameScene::setUIScroe(int indext , int sc)
{
    float jindu =(float)sc*100/(float)_maxScore;
    if (indext == 0) {
        _ui->setScoreTiao(jindu);
        _ui->setScore(sc);
    }else{
        _ui->setScoreTiao1(jindu);
        _ui->setScore1(sc);
    }
    
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
//    CCLOG("???!!! %i",_nowDataInedxt);
    std::vector<int> nowdata= _data[_nowDataInedxt];
    
//    if (_nowDataInedxt == 1) {
//        CCLOG("now : %i",nowdata[0]);
//    }
    
    if (nowdata[0] == ADD_NORMAL) {
        
        if (_fishLayer->getActor()->count()>=20) {
            return;
        }
        
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
//                setFishToRun();
            }
        }
    }else if(nowdata[0] == ADD_FORMAT){
       
        _isChange = true;
        if (_fishLayer->getActor()->count() == 0) {
            for (int i = 0; i<(nowdata.size()-1)/4; ++i) {
                if (_data[_nowDataInedxt][i*4+4]>0) {
                    addFormatFish(nowdata[1+i*4], nowdata[2+i*4], nowdata[3+i*4]);
                    _data[_nowDataInedxt][i*4+4]--;
                    _isChange = false;
                }
                
            }
        }
        
        
    }
}

void GameScene::addFormatFish(int id, int speed, int dir)
{
    
    CCNode* node = (CCNode*)_formatData->objectAtIndex(id);
    
//    CCNode* node = SceneReader::sharedSceneReader()->createNodeWithSceneFile(("data/form_"+Tools::intToString(id)+".csb").c_str());
//    CCNode* node = SceneReader::sharedSceneReader()->createNodeWithSceneFile(("data/test.csb"));
//    CCNode* node = SceneReader::sharedSceneReader()->createNodeWithSceneFile("data/test.json");
    
    CCArray* all =  node->getChildren();
    
    
    
    
    for (int i = 0; i<all->count(); ++i) {
        
        CCNode* fish =dynamic_cast<CCNode*> (all->objectAtIndex(i));
        
        
        
        CCArmature* arm = (CCArmature *)((CCComRender*) fish->getComponent("CCArmature"))->getNode();
        string str = arm->getName().substr(0,arm->getName().find('.'));
        
        string str1 = arm->getName().substr(arm->getName().find('_')+1,arm->getName().find('.'));
        
        
        
        int exitType = Fish::EXIT_DEAD_RIGHT;
        
        CCPoint pos = fish->getPosition();
        
        if (dir == 0) {
            exitType = Fish::EXIT_DEAD_LEFT;
            pos = CCPointMake(fish->getPositionX()+_screenSize.width, fish->getPositionY());
        }
        
        
        
        _fishLayer->addFish(Tools::stringToInt(str1.c_str()), speed, dir, (str).c_str(),exitType,pos);

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

void GameScene::addFlyNum(int type, int num, int shipID,CCPoint pos,CCPoint des)
{
    
    FlyNum* flynum = FlyNum::create(type, num);
    flynum->setPosition(pos);
    flynum->setShipID(shipID);
    CCMoveTo* to = CCMoveTo::create(ccpDistance(pos, des)/500, des);
    flynum->runAction(to);
    flynum->setDes(des);
    if (_addFlyTime>0) {
        flynum->setStayTime(_addFlyTime);
        
    }
    _addFlyTime+=2;
    _flyNum->addObject(flynum);
    this->addChild(flynum,10);
}

void GameScene::allFishToDead(int shipID)
{
    CCArray* fishs = _fishLayer->getActor();
    
    for (int i = 0 ; i<fishs->count(); ++i) {
        Fish* fish = (Fish*) fishs->objectAtIndex(i);
        fish->setShipID(shipID);
        fish->setDead(true);
        fish->setDeadType(Fish::HOOK_DEAD);

    }
}

ShipManage* GameScene::getShip()
{
    return _shipLayer;
}

int GameScene::getSucNum() const
{
    return _suc_num;
}

int GameScene::getSucAdd() const
{
    return _suc_add;
}

int GameScene::getSucType() const
{
    
    return _suc_type;
}

int GameScene::getStar() const
{
//    return 3;
    return _star;
}