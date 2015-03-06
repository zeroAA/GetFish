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
        }if(i == 3){
            player->setPosition(ccp(_screenSize.width*0.25, _screenSize.height*0.53));
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

        
        CCSprite* small_player = CCSprite::create(("ship/bp_"+Tools::intToString(i+1) +".png").c_str(), CCRectMake(0, boundingBox().size.height*0.15, player->boundingBox().size.width, 247));
        small_player->setScaleX(-1);
        
        if (i == 0) {
            small_player->setPosition(ccp(guang->getPositionX()-guang->boundingBox().size.width*0.35, guang->getPositionY()+60));
        }if (i == 2) {
             small_player->setPosition(ccp(guang->getPositionX()-guang->boundingBox().size.width*0.41, guang->getPositionY()+60));
        }else{
        small_player->setPosition(ccp(guang->getPositionX()-guang->boundingBox().size.width*0.38, guang->getPositionY()+60));
        
        }
        addChild(small_player);
        small_player->setVisible(false);
        _small_players->addObject(small_player);
        
    }
    
    ((CCSprite*)_players->objectAtIndex(_nowSelect))->setVisible(true);
    
     ((CCSprite*)_small_players->objectAtIndex(_nowSelect))->setVisible(true);
    
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
    
    CCSprite* zi1 = CCSprite::createWithSpriteFrameName("ui_zi1.png");
    zi1->setAnchorPoint(ccp(0, 0));
    zi1->setPosition(ccp(guang->getPositionX()-guang->boundingBox().size.width*0.55, _screenSize.height*0.79));
    
    addChild(zi1);
    
    
    CCSprite* zi2 = CCSprite::createWithSpriteFrameName("ui_jiesao1.png");
    zi2->setAnchorPoint(ccp(0, 0));
    zi2->setPosition(ccp(zi1->getPositionX()+zi1->boundingBox().size.width+10, zi1->getPositionY()));
    
    addChild(zi2);
    
    _buy = CCNode::create();
    
    _buy->setPosition(ccp(guang->getPositionX()-guang->boundingBox().size.width*0.5, guang->getPositionY()-130));
    
    CCSprite* buy_back = CCSprite::createWithSpriteFrameName("ui_jiesuo.png");
    
    _buy->addChild(buy_back);
    
    CCSprite* buy_mo_b = CCSprite::createWithSpriteFrameName("ui_jinback.png");
    buy_mo_b->setAnchorPoint(ccp(0, 0.5));
    buy_mo_b->setPosition(ccp(-buy_back->boundingBox().size.width*0.4, 0));
    _buy->addChild(buy_mo_b);
    
    CCSprite* yang = CCSprite::createWithSpriteFrameName("ui_qian.png");
    yang->setAnchorPoint(ccp(0, 0.5));
    yang->setPosition(ccp(buy_mo_b->getPositionX()-18, 8));
    _buy->addChild(yang);
    
    
    
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

    
    return true;
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

bool ChoosePlayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(_buttons->toucheBegan(pTouch, pEvent)){
        return true;
    }
    CCPoint pos=pTouch->getLocation();
    
//    CCLOG("x : %i y : %i",(int)_left->boundingBox().origin.x,(int)_left->boundingBox().origin.y);
    
    if (_left->isVisible()&&_left->boundingBox().containsPoint(pos)) {
        
        _nowSelect--;
        if (_nowSelect<0) {
            _nowSelect=_players->count()-1;
        }
        changePlayer();
        return true;
    }
    
    if (_right->isVisible()&&_right->boundingBox().containsPoint(pos)) {
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
        _isDead = true;
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
        ((CCSprite*)_small_players->objectAtIndex(i))->setVisible(false);
    }
    ((CCSprite*)_small_players->objectAtIndex(_nowSelect))->setVisible(true);
    
   CCSprite* player = ((CCSprite*)_players->objectAtIndex(_nowSelect));
    player->setVisible(true);
    player->setOpacity(0);
    CCFadeIn* in = CCFadeIn::create(0.5);
    player->runAction(in);
    
    setChooseIC();
}

bool ChoosePlayer::getIsDead() const
{
    return _isDead;
}