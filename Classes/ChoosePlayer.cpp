//
//  ChoosePlayer.cpp
//  GetFish
//
//  Created by zhusu on 15/3/5.
//
//

#include "ChoosePlayer.h"
#include "Common.h"
#include "Tools.h"
#include "MapScene.h"
#include "Data.h"
#include "GameSaveData.h"

ChoosePlayer::ChoosePlayer():_nowSelect(0),_isDead(false)
{
    
}

ChoosePlayer::~ChoosePlayer()
{
    if(_players){
        _players->release();
        _players  = NULL;
        
    }
    if (_small_players) {
        _small_players->release();
        _small_players=NULL;
    }
}

bool ChoosePlayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    
    
    _player_gold.push_back(0);
    _player_gold.push_back(PLAYER2_GOLD);
    _player_gold.push_back(PLAYER3_GOLD);
    _player_gold.push_back(PLAYER4_GOLD);
    _player_gold.push_back(PLAYER5_GOLD);
    _player_gold.push_back(PLAYER6_GOLD);
    
    CCSprite* guang = CCSprite::createWithSpriteFrameName("ui_guang.png");
    guang->setAnchorPoint(ccp(1, 0.5));
    guang->setPosition(ccp(_screenSize.width, _screenSize.height*0.5));
    addChild(guang);
    
    _players = CCArray::create();
    _players->retain();
    _small_players = CCArray::create();
    _small_players->retain();
    for(int i = 0;i<6;++i){
        
        CCSprite* player = CCSprite::create(("ship/bp_"+Tools::intToString(i+1) +".png").c_str());
        
        if(i == 4){
           player->setPosition(ccp(_screenSize.width*0.23, _screenSize.height*0.53));
            CCParticleSystemQuad* numP = CCParticleSystemQuad::create("ui/haidaochuanzhang.plist");
            numP->setScale(2);
            numP->setPosition(ccp(215, 60));
            player->addChild(numP);
            
        }if(i == 3){
            player->setPosition(ccp(_screenSize.width*0.25, _screenSize.height*0.53));
            
            CCParticleSystemQuad* numP = CCParticleSystemQuad::create("ui/saber.plist");
            numP->setScale(5);
            numP->setPosition(ccp(50, 20));
            player->addChild(numP);
            
        }else if(i == 2){
            
            player->setPosition(ccp(_screenSize.width*0.21, _screenSize.height*0.53));
            
            CCParticleSystemQuad* p1 = CCParticleSystemQuad::create("ui/lvjuren.plist");
            p1->setPosition(ccp(320, 255));
            player->addChild(p1);
            
            CCParticleSystemQuad* p2 = CCParticleSystemQuad::create("ui/lvjuren.plist");
            p2->setPosition(ccp(385, 250));
            player->addChild(p2);
            
        }else if(i == 5){
            player->setPosition(ccp(_screenSize.width*0.21, _screenSize.height*0.53));
            
            CCParticleSystemQuad* p1 = CCParticleSystemQuad::create("ui/shenlongxiaoqiu.plist");
            p1->setScale(0.5);
            p1->setPosition(ccp(378, 200));
            player->addChild(p1);
            
            
            CCParticleSystemQuad* p2 = CCParticleSystemQuad::create("ui/shenlongxiaoqiu.plist");
            p2->setScale(0.3);
            p2->setPosition(ccp(360, 295));
            player->addChild(p2);
            
            CCParticleSystemQuad* p3 = CCParticleSystemQuad::create("ui/shenlongxiaoqiu.plist");
            p3->setScale(0.5);
            p3->setPosition(ccp(188, 25));
            player->addChild(p3);
            
            CCParticleSystemQuad* p4 = CCParticleSystemQuad::create("ui/shenlongxiaoqiu.plist");
            p4->setScale(0.5);
            p4->setPosition(ccp(30, 270));
            player->addChild(p4);
            
            CCParticleSystemQuad* p5 = CCParticleSystemQuad::create("ui/shenlongxiaoqiu.plist");
            p5->setScale(0.3);
            p5->setPosition(ccp(35, 75));
            player->addChild(p5);
            
            CCParticleSystemQuad* p6 = CCParticleSystemQuad::create("ui/shenlongxiaoqiu.plist");
            p6->setScale(0.2);
            p6->setPosition(ccp(375, 115));
            player->addChild(p6);
            
            
            CCParticleSystemQuad* p7 = CCParticleSystemQuad::create("ui/shenlongyanjing1.plist");
            p7->setScale(1.5);
            p7->setPosition(ccp(75, 180));
            player->addChild(p7);
            
            
            CCParticleSystemQuad* p8 = CCParticleSystemQuad::create("ui/shenlongyanjing1.plist");
            p8->setScale(1.3);
            p8->setPosition(ccp(46, 185));
            player->addChild(p8);
            
            

            
        }else{
            player->setPosition(ccp(_screenSize.width*0.21, _screenSize.height*0.53));
        }
        CCMoveBy *move = CCMoveBy::create(1, CCPoint(0, 2));
        CCMoveBy *move2 = CCMoveBy::create(1, CCPoint(0, -2));
        
        
        
        CCSequence* sequence = CCSequence::create(move,move2,NULL);
        
        CCRepeatForever* repeat = CCRepeatForever::create(sequence);
        
        player->runAction(repeat);
        
        player->setVisible(false);
        addChild(player);
        
        _players->addObject(player);
        
        if(i == 1){
            CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(("ship/player_"+Tools::intToString(i+1)+".ExportJson").c_str());
        }else{
            CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(("ship/player_"+Tools::intToString(i+1)+".csb").c_str());
        }
        
        CCArmature* small_player = CCArmature::create(("player_"+Tools::intToString(i+1)).c_str());
        small_player->getAnimation()->playWithIndex(0);
       
        

        small_player->setPosition(ccp(guang->getPositionX()-guang->boundingBox().size.width*0.38, guang->getPositionY()-40));
        
        CCMoveBy* m = CCMoveBy::create(0.6, ccp(0, -4));
        CCMoveBy* m2 = CCMoveBy::create(0.9, ccp(0, 12));
        CCMoveBy* m3 = CCMoveBy::create(0.6, ccp(0, -8));
        
        CCSequence* s = CCSequence::create(m,m2,m3,NULL);
        
        small_player->runAction(CCRepeatForever::create(s));
        
        addChild(small_player);
        small_player->setVisible(false);
        _small_players->addObject(small_player);
        
    }
    
    ((CCSprite*)_players->objectAtIndex(_nowSelect))->setVisible(true);
    
     ((CCArmature*)_small_players->objectAtIndex(_nowSelect))->setVisible(true);
    
    for (int i = 0; i<_players->count(); ++i) {
        CCSprite* dian = CCSprite::createWithSpriteFrameName("ui_dian1.png");
        
        dian->setPosition(ccp(_screenSize.width*0.05+i*50, _screenSize.height*0.18));
        
        addChild(dian);
        
    }
    
    _chooseIc = CCSprite::createWithSpriteFrameName("ui_dian2.png");
    setChooseIC();
    addChild(_chooseIc);
    
    _left = CCSprite::createWithSpriteFrameName("ui_jiantou.png");
    CCMoveBy* lmov = CCMoveBy::create(0.2, ccp(-3, 0));
    CCMoveBy* lmov1 = CCMoveBy::create(0.2, ccp(6, 0));
    
    CCSequence* sq = CCSequence::create(lmov,lmov,lmov1,NULL);
    
    CCRepeatForever* re = CCRepeatForever::create(sq);
    
    _left->runAction(re);
    
    _left->setPosition(ccp(_screenSize.width*0.03, _screenSize.height*0.5));
    addChild(_left);
    
    _right = CCSprite::createWithSpriteFrameName("ui_jiantou.png");
    _right->setScaleX(-1);
    
    CCMoveBy* rmov = CCMoveBy::create(0.2, ccp(3, 0));
    CCMoveBy* rmov1 = CCMoveBy::create(0.2, ccp(-6, 0));
    
    CCSequence* rsq = CCSequence::create(rmov,rmov,rmov1,NULL);
    
    CCRepeatForever* rre = CCRepeatForever::create(rsq);
    
    _right->runAction(rre);

    
    _right->setPosition(ccp(_screenSize.width*0.4, _screenSize.height*0.5));

    addChild(_right);
    
    zi1 = CCSprite::createWithSpriteFrameName("ui_player_zi1.png");
    zi1->setAnchorPoint(ccp(0, 0));
    zi1->setPosition(ccp(guang->getPositionX()-guang->boundingBox().size.width*0.55, _screenSize.height*0.79));
    
    addChild(zi1);
    
    
    zi2 = CCSprite::createWithSpriteFrameName("ui_player_jieshao1.png");
    zi2->setAnchorPoint(ccp(0, 0));
    zi2->setPosition(ccp(zi1->getPositionX()+zi1->boundingBox().size.width+7, zi1->getPositionY()));
    
    addChild(zi2);
    
    _buy = CCNode::create();
    
//    _buy->setVisible(false);
    
    _buy->setPosition(ccp(guang->getPositionX()-guang->boundingBox().size.width*0.5, guang->getPositionY()-130));
    
    CCSprite* buy_back = CCSprite::createWithSpriteFrameName("ui_jiesuo.png");
    
    _buy->addChild(buy_back);
    
    CCSprite* buy_mo_b = CCSprite::createWithSpriteFrameName("ui_jinback.png");
    buy_mo_b->setAnchorPoint(ccp(0, 0.5));
    buy_mo_b->setScale(1.2);
    buy_mo_b->setPosition(ccp(-buy_back->boundingBox().size.width*0.4, 0));
    _buy->addChild(buy_mo_b);
    
//    CCSprite* yang = CCSprite::createWithSpriteFrameName("ui_qian.png");
//    yang->setAnchorPoint(ccp(0, 0.5));
//    yang->setPosition(ccp(buy_mo_b->getPositionX()-18, 8));
//    _buy->addChild(yang);
    
    CCSprite* yang = CCSprite::createWithSpriteFrameName("ui_jinbi.png");
    yang->setAnchorPoint(ccp(0, 0.5));
    yang->setPosition(ccp(buy_mo_b->getPositionX()-4, 1));
    yang->setScale(0.7);
    _buy->addChild(yang);
    
    _goldLabel = CCLabelAtlas::create("5", "ui/shuzi3.png", 14, 20, 43);
    _goldLabel->setAnchorPoint(ccp(0.5, 0.5));
    _goldLabel->setScale(1.3);
    _goldLabel->setPosition(ccp(-buy_back->boundingBox().size.width*0.17, 0));
    //    _goldLabel->setPosition(CCPointMake(_screenSize.width*0.5, _screenSize.height*0.5));
    _buy->addChild(_goldLabel);
    
    addChild(_buy);
    
    
    
    
    _buttons = ButtonWithSpriteManage::create("ui/button.png");
    
    addChild(_buttons);
    
    
    _buy_button = ButtonWithSprite::create(BUTTON_MAP_BUY, "button_jiesuo.png");
    _buy_button->setPosition(ccp(_buy->getPositionX()+ 80, _buy->getPositionY()));
    _buttons->addButton(_buy_button);
    
    ButtonWithSprite* begain = ButtonWithSprite::create(BUTTON_MAP_BEGAIN, "button_kaishi.png");
    begain->setPosition(ccp(guang->getPositionX()-guang->boundingBox().size.width*0.58, guang->getPositionY()-250));
    //    begain->setPosition(ccp(guang->getPositionX()-guang->boundingBox().size.width*0.58, guang->getPositionY()));
    _buttons->addButton(begain);
    
    if (select_player == 0) {
        for (int i = 0; i<5; ++i) {
            if(GameSaveData::loadPlayer(i+1)){
                select_player = i+1;
            }
        }
    }
    
    setChoose(select_player);
    
    MapScene::instance()->setBackButtonV(false);
    
    return true;
}

void ChoosePlayer::setBuyV(bool buy)
{
    _buy->setVisible(buy);
    _buy_button->setVisible(buy);
    
}


void ChoosePlayer::onEnter()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, KEY_CHOOSE, true);
    
    CCLayer::onEnter();
}

void ChoosePlayer::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CCLayer::onExit();
}

void ChoosePlayer::setChoose(int choose)
{
    _nowSelect=choose;
    changePlayer();
}

bool ChoosePlayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    
    
    if(_buttons->toucheBegan(pTouch, pEvent)){
        return true;
    }
    CCPoint pos=pTouch->getLocation();
    
//    CCLOG("x : %i y : %i",(int)_left->boundingBox().origin.x,(int)_left->boundingBox().origin.y);
    
    if (_left->isVisible()&&
        
        CCRectMake(_left->boundingBox().origin.x, _left->boundingBox().origin.y-200, 130, 400).containsPoint(pos)) {
        
        _nowSelect--;
        if (_nowSelect<0) {
            _nowSelect=_players->count()-1;
            
        }
        
        changePlayer();
        return true;
    }
    
    if (_right->isVisible()&&CCRectMake(_right->boundingBox().getMaxX()-100, _right->boundingBox().origin.y-200, 150, 400).containsPoint(pos)) {
        _nowSelect++;
        if (_nowSelect>_players->count()-1) {
            _nowSelect=0;
        }
        changePlayer();
        return true;
    }
    
    return false;
}

void ChoosePlayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    _buttons->toucheMoved(pTouch, pEvent);
}

void ChoosePlayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    _buttons->toucheEnded(pTouch, pEvent);
    
    if (_buttons->getNowID()==BUTTON_MAP_BEGAIN) {
        
        if (_buy_button->isVisible()) {
            MapScene::instance()->addMessage(1, "ui_ti_1.png");
        }else{
            _isDead = true;
            
        }
        
    }else if (_buttons->getNowID()==BUTTON_MAP_BUY) {
        
        
        if (player_gold >= _player_gold[_nowSelect]) {
            getAll+=3;
            GameSaveData::saveAllData();
            player_gold -= _player_gold[_nowSelect];
            GameSaveData::savePlayer(_nowSelect);
            GameSaveData::saveGoldData();
            MapScene::instance()->setGold();
            setBuyV(false);
        }else{
            MapScene::instance()->addMessage(1, "ui_ti_2.png");
        }
        
        
    }
}

void ChoosePlayer::setChooseIC()
{
    _chooseIc->setPosition(ccp(_screenSize.width*0.05+_nowSelect*50, _screenSize.height*0.18));
}

void ChoosePlayer::changePlayer()
{
   
    for(int i = 0 ; i<_players->count();++i){
        ((CCSprite*)_players->objectAtIndex(i))->setVisible(false);
        ((CCArmature*)_small_players->objectAtIndex(i))->setVisible(false);
    }
    ((CCArmature*)_small_players->objectAtIndex(_nowSelect))->setVisible(true);
    
    CCSprite* player = ((CCSprite*)_players->objectAtIndex(_nowSelect));
    player->setVisible(true);
    player->setOpacity(0);
    CCFadeIn* in = CCFadeIn::create(0.5);
    player->runAction(in);
    
    setChooseIC();
    
    
    CCSpriteFrame* nzi1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(("ui_player_zi"+Tools::intToString(_nowSelect+1)+".png").c_str());
    
    zi1->setDisplayFrame(nzi1);
    
    CCSpriteFrame* nzi2 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(("ui_player_jieshao"+Tools::intToString(_nowSelect+1)+".png").c_str());
    zi2 ->setDisplayFrame(nzi2);;
    
    
    select_player = _nowSelect;
    
    _goldLabel->setString(Tools::intToString(_player_gold[_nowSelect]).c_str());
    
    
    
    if (_nowSelect==0) {
        
        setBuyV(false);
    }else if (_nowSelect==1&&GameSaveData::loadPlayer(1)) {
        setBuyV(false);
    }else if(_nowSelect==2&&GameSaveData::loadPlayer(2)){
        setBuyV(false);
    }else if(_nowSelect==3&&GameSaveData::loadPlayer(3)){
        setBuyV(false);
    }else if(_nowSelect==4&&GameSaveData::loadPlayer(4)){
        setBuyV(false);
    }else if(_nowSelect==5&&GameSaveData::loadPlayer(5)){
        setBuyV(false);
    }else{
        
        setBuyV(true);
        
    }
    
}

bool ChoosePlayer::getIsDead() const
{
    return _isDead;
}

int ChoosePlayer::getNowPlayer() const
{
    return _nowSelect;
}