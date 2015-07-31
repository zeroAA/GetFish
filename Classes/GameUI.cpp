//
//  GameUI.cpp
//  GetFish
//
//  Created by zhusu on 15/1/27.
//
//

#include "GameUI.h"
#include "Common.h"
#include "Tools.h"
#include "Data.h"
#include "GameScene.h"

GameUI::GameUI():_dir(DIR_NONE)
{
    
}

GameUI::~GameUI()
{
}

bool GameUI::init()
{
    if(CCLayer::init()) {
        _screenSize = CCDirector::sharedDirector()->getWinSize();
        
        
        
        
        zuodi = CCSprite::createWithSpriteFrameName("ui_heibei.png");
        zuodi->setAnchorPoint(ccp(0, 1));
        zuodi->setPosition(ccp(_screenSize.width*0.035, _screenSize.height*0.97));
        
        addChild(zuodi);
        
        _node = CCNode::create();
        zuodi->addChild(_node);
        
        CCSprite* zi4 = CCSprite::createWithSpriteFrameName(("ui_tishi_zi4_"+Tools::intToString(GameScene::instance()->getSucType()+1)+".png").c_str());
        zi4->setAnchorPoint(ccp(0, 0.5));
        zi4->setPosition(ccp(zuodi->boundingBox().size.width*0.5-15, zuodi->boundingBox().size.height*0.5));
        _node->addChild(zi4);
        
        
        
        
        if (GameScene::instance()->getSucType()==0) {
            
            CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(("fish/fish_"+Tools::intToString(GameScene::instance()->getSucAdd())+".csb").c_str());
            CCArmature* fish = CCArmature::create(("fish_"+Tools::intToString(GameScene::instance()->getSucAdd())).c_str());
            fish->setPosition(ccp(zuodi->boundingBox().size.width*0.5+50, zuodi->boundingBox().size.height*0.5));
            fish->setScale(0.5);
            _node->addChild(fish);
            
            
            _num = CCLabelAtlas::create((","+Tools::intToString(GameScene::instance()->getSucNum())).c_str(), "ui/shuzi5.png", 12, 15, 43);
            _num->setAnchorPoint(ccp(0, 0.5));
            
            _num->setPosition(ccp(zuodi->boundingBox().size.width*0.5+80, zuodi->boundingBox().size.height*0.5));
            
            _node->addChild(_num);
        }else if (GameScene::instance()->getSucType()==1) {
            
            CCArmature* fish = CCArmature::create("item_2");
            fish->setPosition(ccp(zuodi->boundingBox().size.width*0.5+50, zuodi->boundingBox().size.height*0.5));
            _node->addChild(fish);
            
            
            _num = CCLabelAtlas::create((","+Tools::intToString(GameScene::instance()->getSucNum())).c_str(), "ui/shuzi5.png", 12, 15, 43);
            _num->setAnchorPoint(ccp(0, 0.5));
            
            _num->setPosition(ccp(zuodi->boundingBox().size.width*0.5+70, zuodi->boundingBox().size.height*0.5));
            
            _node->addChild(_num);
        }else if (GameScene::instance()->getSucType()==3) {
            
            _num = CCLabelAtlas::create((","+Tools::intToString(GameScene::instance()->getSucNum())).c_str(), "ui/shuzi5.png", 12, 15, 43);
            _num->setAnchorPoint(ccp(0, 0.5));
            
            _num->setPosition(ccp(zi4->boundingBox().getMaxX()+5, zuodi->boundingBox().size.height*0.5));
            
            _node->addChild(_num);
            
        }
        
        CCSprite* daojishi = CCSprite::createWithSpriteFrameName("ui_daojishi.png");
        
        daojishi->setAnchorPoint(ccp(0.5, 1));
        
        daojishi->setPosition(ccp(_screenSize.width*0.5, _screenSize.height+22));
        
        addChild(daojishi);
        
        if (GameScene::instance()->getShip()->getActor()->count()>1) {
            CCNode* jindutiao1 = CCNode::create();
            jindutiao1->setPosition(ccp(_screenSize.width*0.65, _screenSize.height*0.92));
            addChild(jindutiao1);
            
            
            CCSprite* jindudi1 = CCSprite::createWithSpriteFrameName("ui_diaoyu1.png");
            
            jindudi1->setAnchorPoint(ccp(0, 1));
            
            jindudi1->setPosition(ccp(0, 0));
            
            jindutiao1->addChild(jindudi1);
            
            
            CCSprite* tiao1 = CCSprite::createWithSpriteFrameName("ui_lanshang.png");
            
            
            _score_tiao1 = CCProgressTimer::create(tiao1);
            
            _score_tiao1->setType(kCCProgressTimerTypeBar);
            
            _score_tiao1->setBarChangeRate(ccp(1,0));
            
            _score_tiao1->setMidpoint(ccp(0, 0));
            
            _score_tiao1->setPercentage(0);
            
            _score_tiao1->setAnchorPoint(ccp(0, 1));
            
            _score_tiao1->setPosition(ccp(5, -7));
            
            jindutiao1->addChild(_score_tiao1);
            
            
            _score_Label1 = CCLabelAtlas::create("0", "ui/shuzi5.png", 12, 15, 43);
            _score_Label1->setAnchorPoint(ccp(1, 0.5));
            
            _score_Label1->setPosition(ccp(-5, -jindudi1->boundingBox().size.height*0.5));
            
            jindutiao1->addChild(_score_Label1);
        }
        
        
        CCNode* jindutiao = CCNode::create();
        
        if (GameScene::instance()->getShip()->getActor()->count()>1) {
            jindutiao->setPosition(ccp(_screenSize.width*0.65, _screenSize.height*0.99));
        }else{
            jindutiao->setPosition(ccp(_screenSize.width*0.65, _screenSize.height*0.95));
        }
        
        addChild(jindutiao);
        
        if (GameScene::instance()->getShip()->getActor()->count()<=1) {
            CCSprite* jindudixing = CCSprite::createWithSpriteFrameName("ui_game_xing.png");
            jindudixing->setPosition(ccp(-15, 2));
            jindudixing->setAnchorPoint(ccp(0, 0.5));
            jindutiao->addChild(jindudixing,10);
        }
        
        
        
        
//        CCSprite* jindu = CCSprite::createWithSpriteFrameName("ui_lvshang.png");
//        
//        jindu->setAnchorPoint(ccp(0, 1));
//        
//        jindu->setPosition(ccp(2, -5));
//        
//        jindutiao->addChild(jindu);
        CCSprite* jindudi ;
        CCSprite* tiao;
        
        if (GameScene::instance()->getShip()->getActor()->count()<=1) {
//            for(int i = 0 ; i <3 ;++i){
//                CCSprite* xing = CCSprite::createWithSpriteFrameName("ui_diaoyuxing.png");
//                xing->setPosition(ccp(jindudi->boundingBox().size.width*0.3*(i+1), -20));
//                
//                jindutiao->addChild(xing);
//            }
            tiao = CCSprite::createWithSpriteFrameName("ui_lvshangxing.png");
            jindudi = CCSprite::createWithSpriteFrameName("ui_diaoyu1xing.png");
            
        }else{
            tiao = CCSprite::createWithSpriteFrameName("ui_lvshang.png");
            
            jindudi = CCSprite::createWithSpriteFrameName("ui_diaoyu1.png");
            
            
        }
        
        jindudi->setAnchorPoint(ccp(0, 1));
        
        jindudi->setPosition(ccp(0, 0));
        
        jindutiao->addChild(jindudi);
        
        _score_tiao = CCProgressTimer::create(tiao);
        
        _score_tiao->setType(kCCProgressTimerTypeBar);
        
        _score_tiao->setBarChangeRate(ccp(1,0));
        
        _score_tiao->setMidpoint(ccp(0, 0));
        
        _score_tiao->setPercentage(0);
        
        _score_tiao->setAnchorPoint(ccp(0, 1));
        
        _score_tiao->setPosition(ccp(5, -7));
        
        jindutiao->addChild(_score_tiao);
        
        
        
        _buttons = ButtonWithSpriteManage::create("ui/button.png");
        
        addChild(_buttons);
        
        
        _buttons->addButton(BUTTON_GAME_PAUSE, "button_zanting.png", ccp(_screenSize.width*0.95, _screenSize.height*0.92));
        
        if (IS_ON_BUTTON) {
            
            
           
            
           
            
           
            
//            _buttons->addButton(BUTTON_GAME_RIGHT, "button_you.png", ccp(_screenSize.width*0.075+140, _screenSize.height*0.1));
//            
//            ButtonWithSprite* button = ButtonWithSprite::create(BUTTON_GAME_LEFT, "button_you.png",-1,1);
//            
//            button->setPosition(ccp(_screenSize.width*0.075, _screenSize.height*0.1));
//            
//            _buttons->addButton(button);
            
            _left = CCSprite::createWithSpriteFrameName("button_you.png");
            _left->setPosition(ccp(_screenSize.width*0.075, _screenSize.height*0.1));
            _left->setScaleX(-1);
            
            addChild(_left);
            
            _right = CCSprite::createWithSpriteFrameName("button_you.png");
            _right->setPosition(ccp(_screenSize.width*0.075+140, _screenSize.height*0.1));
            
            addChild(_right);
            
            
            _buttons->addButton(BUTTON_GAME_DO, "button_xiagou.png", ccp(_screenSize.width*0.925, _screenSize.height*0.1));
            
        }
        
        
        float y =_screenSize.height*0.09 ;
        
        if (IS_ON_BUTTON) {
            y =_screenSize.height*0.3 ;
        }
        
//         _buttons->addButton(BUTTON_GAME_ALLGET, "button_citie.png", ccp(_screenSize.width*0.925, _screenSize.height*0.3));
        
        ButtonWithSprite* all = ButtonWithSprite::create(BUTTON_GAME_ALLGET, "button_citie.png");
        all->setPosition(ccp(_screenSize.width*0.925, y));
        
        _citieLabel = CCLabelAtlas::create(Tools::intToString(getAll).c_str() , "ui/shuzi4.png", 21, 28, 43);
        _citieLabel->setScale(0.8);
        _citieLabel->setAnchorPoint(ccp(0.5, 0.5));
        _citieLabel->setPosition(ccp(90,20));
        
        all->addChild(_citieLabel);
        
        _buttons->addButton(all);
        
        _timeLabel = CCLabelAtlas::create("0", "ui/shuzi1.png", 21, 28, 43);
        _timeLabel->setAnchorPoint(ccp(0.5, 0.5));
        _timeLabel->setPosition(ccp(_screenSize.width*0.5, _screenSize.height*0.96));
        
        addChild(_timeLabel);
        
        _score_Label = CCLabelAtlas::create("0", "ui/shuzi5.png", 12, 15, 43);
        _score_Label->setAnchorPoint(ccp(1, 0.5));
        
        _score_Label->setPosition(ccp(-5, -jindudi->boundingBox().size.height*0.5));
        
//        _score_Label->setVisible(false);
        jindutiao->addChild(_score_Label,200);
        
        
        
        return true;
    }
    return false;
}

void GameUI::onEnter()
{
    CCLayer::onEnter();
}

void GameUI::onExit()
{
    CCTextureCache::sharedTextureCache()->removeTextureForKey("ui/game.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("ui/game.plist");
    CCLayer::onExit();
}

bool GameUI::GameUItouchesBegan(CCSet * touchs,CCEvent * event)
{
    
    if (_buttons->touchesBegan(touchs, event)) {
        return true;
    }
    return false;
}

void GameUI::GameUItouchesMoved(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesMoved(touchs, event);

}

void GameUI::GameUItouchesCancelled(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesCancelled(touchs, event);
    
}

void GameUI::GameUItouchesEnded(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesEnded(touchs, event);
    
    
}

void GameUI::GameUItouchesDir(cocos2d::CCSet *touchs, cocos2d::CCEvent *event)
{
    
    
    _left->setScaleX(-1);
    _left->setScaleY(1);
    _right->setScale(1);
    
    for(CCSetIterator iter=touchs->begin();iter!=touchs->end();iter++){
        
        CCTouch * mytouch=(CCTouch *)(* iter);
        
        CCPoint pos=mytouch->getLocation();
        
        
        if (_left->boundingBox().containsPoint(pos)) {
            _left->setScaleX(-0.8);
            _left->setScaleY(0.8);
            setDir(DIR_LEFT);
            return;
        }
        
        if (_right->boundingBox().containsPoint(pos)) {
            _right->setScale(0.8);
            setDir(DIR_RIGHT);
            return;
        }
        
        
    }
    
    setDir(DIR_NONE);
}

int GameUI::getNowButtonID() const
{
    return _buttons->getNowID();
}

void GameUI::setTime(int time)
{
    _timeLabel->setString(Tools::intToString(time).c_str());
}

void GameUI::setScoreTiao(float sc)
{
    _score_tiao->setPercentage(sc);
}

void GameUI::setScoreTiao1(float sc)
{
    _score_tiao1->setPercentage(sc);
}

void GameUI::setScore(int sc)
{
    _score_Label->setString(Tools::intToString(sc).c_str());
}

void GameUI::setScore1(int sc)
{
    _score_Label1->setString(Tools::intToString(sc).c_str());
}

void GameUI::addMubiaoScore(std::vector<int> mubiao)
{
    if (true) {
        return;
    }
    for (int i = 0 ; i<mubiao.size(); ++i) {
        CCLabelAtlas* mubiaoLabel = CCLabelAtlas::create(Tools::intToString(mubiao[i]).c_str(), "ui/shuzi2.png", 18, 26, 48);
        mubiaoLabel->setAnchorPoint(ccp(0.5, 0.5));
        mubiaoLabel->setPosition(ccp(_screenSize.width*0.7+_screenSize.width*0.08*i, _screenSize.height*0.9));
        
        addChild(mubiaoLabel);

    }
}

CCSprite* GameUI::getLeft()
{
    return _left;
}

CCSprite* GameUI::getRight()
{
    return _right;
}

void GameUI::setSucNum(std::string str)
{
    _num->setString(str.c_str());
}

void GameUI::setSuc()
{
    zuodi->removeChild(_node, true);
    CCSprite* wancheng = CCSprite::createWithSpriteFrameName("dacheng.png");
    wancheng->setPosition(ccp(zuodi->boundingBox().size.width*0.5+20,zuodi->boundingBox().size.height*0.5));
    wancheng->setScale(3);
    
    CCScaleTo* sc = CCScaleTo::create(0.3, 1);
    
    wancheng->runAction(sc);
    zuodi->addChild(wancheng);
}

void GameUI::setCitieNum(int num)
{
    _citieLabel->setString(Tools::intToString(num).c_str());
}

