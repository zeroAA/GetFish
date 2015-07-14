#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "MapScene.h"
#include "Tools.h"
#include "AudioController.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    
   
    
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 30);
    
    CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    CCSize winSize = pDirector->getWinSize();
    int profile = Tools::calScreenRatioProfile(winSize);
    
    CCSize designResolutionSize;
    if(profile == KScreenRatioProfile3v4) {
        CCLog("KScreenRatioProfile3v4");
        designResolutionSize = CCSizeMake(1024, 768);
    }
    else if(profile == KScreenRatioProfile2v3) {
        CCLog("KScreenRatioProfile2v3");
        designResolutionSize = CCSizeMake(960, 640);
    }
    else if(profile == KScreenRatioProfile10v16) {
        CCLog("KScreenRatioProfile10v16");
        designResolutionSize = CCSizeMake(800, 480);
    }
    
    else if(profile == KScreenRatioProfile10v17) {
        CCLog("KScreenRatioProfile10v17");
        designResolutionSize = CCSizeMake(1136, 640);
    }
    
    
//    designResolutionSize = CCSizeMake(1136, 640);
    
    //    designResolutionSize = CCSizeMake(480, 320);
    
    CCSize lsSize = CCSizeMake(designResolutionSize.width, designResolutionSize.height);
    float scaleX = (float)frameSize.width / lsSize.width;
    float scaleY = (float)frameSize.height / lsSize.height;
    CCLOG("scaleX = %f, scaleY = %f", scaleX, scaleY);
    float scale = 0.0;
    if(scaleX > scaleY)
    {
        scale = scaleX / (frameSize.height / (float)lsSize.height);
    }
    else
    {
        scale = scaleY / (frameSize.width / (float) lsSize.width);
    }
    
    CCLOG("x = %f, y = %f, scale = %f", scaleX, scaleY, scale);
    
   
//    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(lsSize.width * scale, lsSize.height * scale, kResolutionNoBorder);
    
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(lsSize.width * scale, lsSize.height * scale, kResolutionFixedHeight);

    // create a scene. it's an autorelease object
    
//    CCScene *pScene = HelloWorld::scene();
    
//    CCScene *pScene = GameScene::scene(0,1);
    
    CCScene* pScene = MapScene::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}


// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();
    AUDIO->pauseBgMusic();
    // if you use SimpleAudioEngine, it must be pause
//     SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
    AUDIO->resumeBgMusic();
    // if you use SimpleAudioEngine, it must resume here
//     SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
