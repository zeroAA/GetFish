//
//  BadEnd.cpp
//  GetFish
//
//  Created by zhusu on 15/7/22.
//
//

#include "BadEnd.h"
#include "Common.h"
#include "Tools.h"
#include "GameSaveData.h"
#include "GameScene.h"
#include "Data.h"

BadEnd::BadEnd():_dead(-1)
{
    
}

BadEnd::~BadEnd()
{
}

bool BadEnd::init()
{
    if(CCLayer::init()) {
        
        CCLayerColor* layerColor = CCLayerColor::create();
        layerColor->setColor(ccc3(0, 0, 0));
        layerColor->setOpacity(200);
        
        addChild(layerColor);
        
        CCSize _screenSize = CCDirector::sharedDirector()->getWinSize();
        
        CCSprite* di = CCSprite::create("ui/badend.png");
        di->setPosition(ccp(_screenSize.width*0.5, _screenSize.height*0.65));
        addChild(di);
        
        
        _numLabel = CCLabelAtlas::create("10", "ui/shuzi4.png", 21, 28, 43);
        _numLabel->setAnchorPoint(ccp(0.5, 0.5));
        _numLabel->setScale(1.5);
        _numLabel->setPosition(ccp(di->boundingBox().size.width*0.5, 100));
        di->addChild(_numLabel);
        
        CCSprite* zi = CCSprite::create("ui/badendzi.png");
        zi->setPosition(ccp(_screenSize.width*0.5, _screenSize.height*0.2));
        addChild(zi);
        this->setTouchEnabled(true);
        
        _buttons = ButtonWithSpriteManage::create("ui/button.png");
        
        addChild(_buttons);
        ButtonWithSprite* button_reset;
        
        if (GameSaveData::loadRest()) {
            #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
            button_reset = ButtonWithSprite::create(BUTTON_END_RESET, "button_chongzhi_ip.png");
#else
            button_reset = ButtonWithSprite::create(BUTTON_END_RESET, "button_chongzhi.png");
#endif
            
        }else{
            button_reset = ButtonWithSprite::create(BUTTON_END_RESET, "button_mianchongzhi.png");
            CCSprite* zi = CCSprite::create("ui/yindao_d_99.png");
            zi->setPosition(ccp(_screenSize.width*0.5, _screenSize.height*0.2-40));
            addChild(zi);
        }
       
        
        
        button_reset->setPosition(ccp(_screenSize.width*0.8, _screenSize.height*0.32));
        
        _buttons->addButton(button_reset);
        
        ButtonWithSprite* button_play = ButtonWithSprite::create(BUTTON_END_PLAY, "buttion_chongwan.png");
        
        button_play->setPosition(ccp(_screenSize.width*0.5, _screenSize.height*0.32));
        
        _buttons->addButton(button_play);
        
        ButtonWithSprite* button_back = ButtonWithSprite::create(BUTTON_END_BACK, "button_fanhui2.png");
        
        button_back->setPosition(ccp(_screenSize.width*0.2, _screenSize.height*0.32));
        
        _buttons->addButton(button_back);
        
        _time = 10*FPS+2;
        
        return true;
    }
    
    return false;
}

void BadEnd::touchesBegan(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesBegan(touchs, event);
}


void BadEnd::touchesMoved(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesMoved(touchs, event);
}

void BadEnd::touchesEnded(CCSet * touchs,CCEvent * event)
{
    _buttons->touchesEnded(touchs, event);
   
    if(_buttons->getNowID() == BUTTON_END_RESET){
        
        if (GameSaveData::loadRest()) {
            if (player_gold>=REST_GOLD) {
                setDead(DEAD_TYPE_REST);
            }else{
                GameScene::instance()->addMessage(1, "ui_ti_2.png");
            }
        }else{
            
            setDead(DEAD_TYPE_REST);
        }

        
        
    
    }else if(_buttons->getNowID() == BUTTON_END_PLAY){
        setDead(DEAD_TYPE_PLAY);
    }else if(_buttons->getNowID() == BUTTON_END_BACK){
        setDead(DEAD_TYPE_BACK);
    }
}

void BadEnd::cycle(float dt)
{
    _time--;
    _numLabel->setString(Tools::intToString((int)(_time/FPS)).c_str());
    
    if (_time<=0) {
        setDead(DEAD_TYPE_BACK);
    }
}

void BadEnd::onExit()
{
    
   
    CCTextureCache::sharedTextureCache()->removeTextureForKey("ui/badend.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("ui/badendzi.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("ui/yindao_d_99.png");
    
    CCLayer::onExit();
}