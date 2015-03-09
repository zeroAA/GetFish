//
//  GameSecne.h
//  GetFish
//
//  Created by zhusu on 14/12/12.
//
//

#ifndef __GetFish__GameScene__
#define __GetFish__GameScene__

#include "cocos2d.h"
#include "FishManage.h"
#include "ShipManage.h"
#include "BackGround.h"
#include "EffectManage.h"

#include "Ship.h"
#include "Fish.h"

#include "GameUI.h"

USING_NS_CC;

class GameScene : public cocos2d::CCLayer
{
public:
    
    const static int ADD_NORMAL = 10;
    
    const static int ADD_FORMAT = 13;
    
    static cocos2d::CCScene* scene(int lev);
    
    static GameScene* create(int lev);
    
    virtual bool init(int lev);
    
    static GameScene* instance();
    
    GameScene();
    
    virtual ~GameScene();
    
    
    virtual void onEnter();
    
    virtual void onEnterTransitionDidFinish();
    
    virtual void onExit();
    
    virtual void registerWithTouchDispatcher(void);
    
    virtual void ccTouchesBegan(CCSet * touchs,CCEvent * event);
    
    virtual void ccTouchesMoved(CCSet * touchs,CCEvent * event);
    
    virtual void ccTouchesCancelled(CCSet * touchs,CCEvent * event);
    
    virtual void ccTouchesEnded(CCSet * touchs,CCEvent * event);
    
    virtual void draw();
    
    void addDolphin();
    
    void addLightFish();
    
    void addTortoise();
    
    void addWhale();
    
    void addEatFish();
    
    void addShark();
    
    void addSwordFish();
    
    void addStrong();
    
    void addEle();
    
    void addFormatFish(int id ,int speed,int dir);
    
    
    
private:
    
    static GameScene* _instance;
    
    void cycle(float delta);
    
    void addFish(int id);
    
    void addShip();
    
    void setShip(int x);
    
    bool canHook();
    
    void shipAndFish(Ship* ship,Fish* fish, int indext);
    
    void cycleFishs();
    
    bool isHookFish(Ship* ship,Fish* fish);
    
    bool isCollideFish(Ship* ship,Fish* fish);
    
    bool isCollideFish(Fish* fish1,Fish* fish2);
    
    bool waterCollideShip(Fish* fish,Ship* ship);
    
    void useDolphin(Fish* fish);
    
    void useLightFish(Fish* fish);
    
    void useTortoise(Fish* fish);
    
    void useFishAtk(Fish* fish);
    
    void useFish(Fish* fish);
    
    void setUIScroe(int sc);
    
    void setFishToRun();
    
    void addFish();

    
protected:
    CCSize _screenSize;
    
    FishManage* _fishLayer;
    
    ShipManage* _shipLayer;
    
    BackGround* _bgLayer;
    
    EffectManage* _effectLayer;
    
    int _addFishTime;
    
    int _addSPFishTime;
    
    GameUI* _ui;
    
    int _time;
    
    std::vector<int> _mubiao_scroe;
    
    int _nowLev;
    
   
    
    std::vector< std::vector<int> > _data;
    
    int _fishNum;
    
    int _nowDataInedxt;
    
    bool _isChange;
};

#endif /* defined(__GetFish__GameScene__) */
