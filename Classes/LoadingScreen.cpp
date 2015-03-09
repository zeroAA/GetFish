

#include "LoadingScreen.h"
#include "Common.h"
#include "GameScene.h"

LoadingScreen* LoadingScreen::create(const int screenid, const int param)
{
    LoadingScreen* loading = new LoadingScreen();
    
    if(loading && loading->init(screenid, param)) {
        loading->autorelease();
        return loading;
    }
    
    CC_SAFE_DELETE(loading);
    return NULL;
}

LoadingScreen::LoadingScreen():_nextScreenId(KScreenUnkown), _nextScreenParam(0)
{

}

bool LoadingScreen::init(const int screenId, const int param)
{
    if(CCScene::init()) {
        
//        CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
//        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
        
        _nextScreenId = screenId;
        _nextScreenParam = param;
        CCLayerColor* color = CCLayerColor::create(ccc4(255, 255, 255, 255));
        this->addChild(color, 0);
        
        return true;
    }
    
    return false;
}

LoadingScreen::~LoadingScreen()
{

}

void LoadingScreen::onEnter()
{
    CCScene::onEnter();
}

void LoadingScreen::onEnterTransitionDidFinish()
{
    this->scheduleOnce(schedule_selector(LoadingScreen::loadNextScreen), 0.5);
    CCScene::onEnterTransitionDidFinish();
}

void LoadingScreen::onExit()
{
    CCScene::onExit();
}

void LoadingScreen::loadNextScreen(cocos2d::CCTime delta)
{
    CCScene* scene = NULL;
    
    if(_nextScreenId == KScreenGame) {
        scene = GameScene::scene(_nextScreenParam);
    }
    
    if(scene != NULL) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.2, scene));
    }
}