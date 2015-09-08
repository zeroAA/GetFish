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
#include "ChoosePlayer.h"
#include "Set.h"

#include "ButtonWithSpriteManage.h"

#include "MessageManage.h"

#include "Shop.h"

USING_NS_CC;

class MapScene : public cocos2d::CCLayer
{
public:
    
    const static int CHOOSE = 0;
    const static int MAP = 1;
    
    const static int SET = 5;
    
    const static int SHOP = 6;
    
    const static int GAME = 50;
    
    virtual bool init(int type);
    
    static MapScene* instance();
    
    static cocos2d::CCScene* scene(int type);
    
    static MapScene* create(int type);
    
    MapScene();
    
    virtual ~MapScene();
    
    virtual void onExit();
    
    virtual void onEnter();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    void addMessage(int type,const char* name);
    
    void setGold();
    
    void setBackButtonV(bool v);
    
    void addBuy();
    
    void removeBuy(bool addFail);
    
    void setShopButton(int indext);
    
    void changeToMap();

private:
    
    static MapScene* _instance;
    
    
    
    void changeToChoose();
    
    void changeToSet();
    
    void changeToShop(int type);
    
    void cycle(float delta);
    
    void addLogin();
    
    
    
protected:
//    MapUI* _mapUI;
    CCSize _screenSize;
//    ChoosePlayer* _choose;
    
    CCLayer* _onLayer;
//    Set* _set;
    
    ButtonWithSpriteManage* _buttons;
    int _nowLayer ;
    
    int _backLayer;
    
    CCLabelAtlas* _goldLabel;
    
//    int _nowPlayer;
    
    CCLayer* _login;
    
    CCLayer* _logo;
    
    int _logo_time;
    
    MessageManage* _message;
    
    ButtonWithSprite* _back;
    
    
};



#endif /* defined(__GetFish__MapScene__) */
