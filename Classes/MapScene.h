//
//  MapScene.h
//  GetFish
//
//  Created by zhusu on 15/2/3.
//
//

#ifndef __GetFish__MapScene__
#define __GetFish__MapScene__

#include "cocos2d.h"

#include "MapUI.h"
#include "LoadingScreen.h"

USING_NS_CC;

class MapScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(MapScene);
    
    MapScene();
    
    virtual ~MapScene();
    
    virtual void onExit();
    
    virtual void onEnter();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
protected:
    MapUI* _mapUI;
    CCSize _screenSize;
    
};

#endif /* defined(__GetFish__MapScene__) */
