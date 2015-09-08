//
//  Pause.cpp
//  GetFish
//
//  Created by zhusu on 15/7/20.
//
//

#include "Pause.h"
#include "Common.h"
#include "GameScene.h"
#include "Tools.h"

Pause::Pause():_dead(DEAD_TYPE_NODEAD)
{
    
}

Pause::~Pause()
{
}

Pause* Pause::create(int score,int type,int fishID,int num)
{
    Pause* map = new Pause();
    
    if(map && map->init( score, type,fishID, num)) {
        map->autorelease();
        return map;
    }
    
    CC_SAFE_DELETE(map);
    return NULL;
}

bool Pause::init(int score,int type,int fishID,int num)
{
    if(CCLayer::init()) {
        
        CCSprite* back = CCSprite::createWithSpriteFrameName("ui_tishi_back.png");
        
        addChild(back);
        
        CCSprite* ming = CCSprite::createWithSpriteFrameName("ui_c_zanting.png");
        ming->setAnchorPoint(ccp(0, 1));
        ming->setPosition(ccp(-back->boundingBox().size.width*0.5+15, back->boundingBox().size.height*0.5-5));
        addChild(ming);
        
        int lev = GameScene::instance()->getNowLevel();
        CCLabelAtlas *_levLabel = CCLabelAtlas::create( (Tools::intToString((lev/12)+1)+ "-"+Tools::intToString(lev-(lev/12)*12+1)).c_str(), "ui/shuzi4.png", 21, 28, 43);
        
        _levLabel->setAnchorPoint(ccp(0, 1));
        
        _levLabel->setPosition(ccp(ming->boundingBox().getMaxX()+10, ming->getPositionY()-10));
        
        addChild(_levLabel);
        
        //        CCSprite* zi = CCSprite::createWithSpriteFrameName("yindao_d_13.png");
        //        zi->setPosition(ccp(0, 10));
        //        addChild(zi);
        
        
        CCSprite* zi1 = CCSprite::createWithSpriteFrameName("ui_tishi_zi.png");
        zi1->setAnchorPoint(ccp(0, 0));
        zi1->setPosition(ccp(-back->boundingBox().size.width*0.5+20, 60));
        
        addChild(zi1);
        CCSprite* zi2;
        if (type != 3&&GameScene::instance()->getShip()->getActor()->count()<=1&&GameScene::instance()->getScroe(0)>=GameScene::instance()->getMuBiao(0)){
            
            CCSprite* zi2 =   CCSprite::createWithSpriteFrameName("dacheng.png");
            zi2->setAnchorPoint(ccp(0, 0));
            zi2->setPosition(ccp(-back->boundingBox().size.width*0.5+25, 25));
            addChild(zi2);
            
        }else{
            
            
            
            if (GameScene::instance()->getShip()->getActor()->count()>1){
                zi2 = CCSprite::createWithSpriteFrameName("ui_tishi_zi4_4.png");
            }else{
                zi2 = CCSprite::createWithSpriteFrameName("ui_tishi_zi2.png");
            }
            
            zi2->setAnchorPoint(ccp(0, 0));
            zi2->setPosition(ccp(-back->boundingBox().size.width*0.5+25, 25));
            
            addChild(zi2);
            
            _score = CCLabelAtlas::create( (","+Tools::intToString(score)).c_str(), "ui/shuzi5.png", 12, 15, 43);
            _score->setAnchorPoint(ccp(0, 0));
            
            _score->setPosition(ccp(-back->boundingBox().size.width*0.5+zi2->boundingBox().size.width+30, 28));
            addChild(_score,100);
        }
        for (int i = 0; i<2; ++i) {
            CCSprite* star10 = CCSprite::createWithSpriteFrameName("ui_sr.png");
            
            
            star10->setPosition(ccp(80+i*60, 75));
            addChild(star10);
            
            
        }
        
        
        if (type != 3&&GameScene::instance()->getShip()->getActor()->count()<=1&&GameScene::instance()->getScroe(0)>=GameScene::instance()->getMuBiao(1)){
            
            CCSprite* wan =   CCSprite::createWithSpriteFrameName("dacheng.png");
            wan->setAnchorPoint(ccp(0, 0));
            wan->setPosition(ccp(25, 25));
            addChild(wan);
            
        }else{
            
            CCSprite* zi20;
            
            if (GameScene::instance()->getShip()->getActor()->count()>1){
                zi20 = CCSprite::createWithSpriteFrameName("ui_tishi_zi4_4.png");
            }else{
                zi20 = CCSprite::createWithSpriteFrameName("ui_tishi_zi2.png");
            }
            
            zi20->setAnchorPoint(ccp(0, 0));
            zi20->setPosition(ccp(25, 25));
            addChild(zi20);
            
            
            
            CCLabelAtlas* _score20 = CCLabelAtlas::create( (","+Tools::intToString(GameScene::instance()->getMuBiao(1))).c_str(), "ui/shuzi5.png", 12, 15, 43);
            _score20->setAnchorPoint(ccp(0, 0));
            
            _score20->setPosition(ccp(zi20->boundingBox().getMaxX()+5, zi20->getPositionY()+2));
            addChild(_score20);
        }
        for (int i = 0; i<3; ++i) {
            CCSprite* star1 = CCSprite::createWithSpriteFrameName("ui_sr.png");
            
            
            star1->setPosition(ccp(50+i*60,  -15));
            addChild(star1);
        }
        
        
        if (type != 3&&GameScene::instance()->getShip()->getActor()->count()<=1&&GameScene::instance()->getScroe(0)>=GameScene::instance()->getMuBiao(2)){
            
            CCSprite* wan =   CCSprite::createWithSpriteFrameName("dacheng.png");
            wan->setAnchorPoint(ccp(0, 0));
            wan->setPosition(ccp(25, -80));
            addChild(wan);
            
        }else{
            CCSprite* zi21;
            
            if (GameScene::instance()->getShip()->getActor()->count()>1){
                zi21 = CCSprite::createWithSpriteFrameName("ui_tishi_zi4_4.png");
            }else{
                zi21 = CCSprite::createWithSpriteFrameName("ui_tishi_zi2.png");
            }
            
            zi21->setAnchorPoint(ccp(0, 0));
            zi21->setPosition(ccp(25, -80));
            addChild(zi21);
            
            
            CCLabelAtlas* _score21 = CCLabelAtlas::create( (","+Tools::intToString(GameScene::instance()->getMuBiao(2))).c_str(), "ui/shuzi5.png", 12, 15, 43);
            _score21->setAnchorPoint(ccp(0, 0));
            
            _score21->setPosition(ccp(zi21->boundingBox().getMaxX()+5, zi21->getPositionY()+2));
            addChild(_score21);
        }
        CCSprite* zi3 = CCSprite::createWithSpriteFrameName("ui_tishi_zi3.png");
        zi3->setAnchorPoint(ccp(0, 0));
        zi3->setPosition(ccp(-back->boundingBox().size.width*0.5+20, -30));
        
        addChild(zi3);
        
        CCSprite* zi4 = CCSprite::createWithSpriteFrameName(("ui_tishi_zi4_"+Tools::intToString(type+1)+".png").c_str());
        zi4->setAnchorPoint(ccp(0, 0));
        zi4->setPosition(ccp(-back->boundingBox().size.width*0.5+25, -80));
        
        addChild(zi4);
        
        if(type == 0){
            if (num<=0) {
                zi4->setVisible(false);
                CCSprite* wan =   CCSprite::createWithSpriteFrameName("dacheng.png");
                wan->setAnchorPoint(ccp(0, 0));
                wan ->setPosition(ccp(-back->boundingBox().size.width*0.5+25, -80));
                addChild(wan);
            }else{
                zi4->setPosition(ccp(-back->boundingBox().size.width*0.5+25, -80));
                fish = CCArmature::create(("fish_"+Tools::intToString(fishID)).c_str());
                fish->setPosition(ccp(-back->boundingBox().size.width*0.5+100, -70));
                fish->setScale(0.5);
                addChild(fish);
                
                
                _num = CCLabelAtlas::create((","+Tools::intToString(num)).c_str(), "ui/shuzi5.png", 12, 15, 43);
                _num->setAnchorPoint(ccp(0, 0));
                
                _num->setPosition(ccp(-back->boundingBox().size.width*0.5+130, -78));
                
                addChild(_num);
            }
            
        }else if(type == 1){
            if (num<=0) {
                zi4->setVisible(false);
                CCSprite* wan =   CCSprite::createWithSpriteFrameName("dacheng.png");
                wan->setAnchorPoint(ccp(0, 0));
                wan ->setPosition(ccp(-back->boundingBox().size.width*0.5+25, -80));
                addChild(wan);
            }else{
                fish = CCArmature::create("item_2");
                fish->setPosition(ccp(-back->boundingBox().size.width*0.5+100, -70));
                addChild(fish);
                
                
                _num = CCLabelAtlas::create((","+Tools::intToString(num)).c_str(), "ui/shuzi5.png", 12, 15, 43);
                _num->setAnchorPoint(ccp(0, 0));
                
                _num->setPosition(ccp(-back->boundingBox().size.width*0.5+130, -78));
                
                addChild(_num);
            }
        }else if(type == 3){
            _num = CCLabelAtlas::create((","+Tools::intToString(num)).c_str(), "ui/shuzi5.png", 12, 15, 43);
            _num->setAnchorPoint(ccp(0, 0));
            
            _num->setPosition(ccp(-back->boundingBox().size.width*0.5+zi2->boundingBox().size.width+30, -78));
            addChild(_num);
        }
        
        
        
        
        CCSprite* xian = CCSprite::createWithSpriteFrameName("ui_set_xian.png");
        
        addChild(xian);
        
        
        _buttons = ButtonWithSpriteManage::create("ui/button.png");
        
        addChild(_buttons);
        
        
        ButtonWithSprite* _back = ButtonWithSprite::create(BUTTON_PAUSE_BACK, "button_fanhui2.png");
        _back->setPosition(ccp(-back->boundingBox().size.width*0.3, -132));
        
        _buttons->addButton(_back);
        
        
        ButtonWithSprite* _toGame = ButtonWithSprite::create(BUTTON_PAUSE_TOGAME, "button_jixu.png");
        _toGame->setPosition(ccp(back->boundingBox().size.width*0.3, -132));
        
        _buttons->addButton(_toGame);
        
        return true;
    }
    
    return false;
}


void Pause::touchesBegan(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesBegan(touchs, event);
}

void Pause::touchesCancelled(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesCancelled(touchs, event);
}

void Pause::touchesMoved(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesMoved(touchs, event);
}

void Pause::touchesEnded(CCSet * touchs,CCEvent * event)
{
    
    _buttons->touchesEnded(touchs, event);
    
    if (_buttons->getNowID() == BUTTON_PAUSE_BACK) {
        CCDirector::sharedDirector()->resume();
        setDead(DEAD_TYPE_BACK);
    }else if (_buttons->getNowID() == BUTTON_PAUSE_TOGAME) {
        CCDirector::sharedDirector()->resume();
        setDead(DEAD_TYPE_TOGAME);
    }
    
}