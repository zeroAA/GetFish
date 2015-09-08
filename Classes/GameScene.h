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
#include "RockManage.h"
#include "LeafManage.h"
#include "ShellManage.h"
#include "ItemManage.h"
#include "FlyNum.h"
#include "BadEnd.h"
#include "SucEnd.h"

#include "Ship.h"
#include "Fish.h"

#include "Pause.h"

#include "GameUI.h"
#include "GameBegin.h"

#include "MessageManage.h"

#include "NoGold.h"

USING_NS_CC;

class GameScene : public cocos2d::CCLayer
{
public:
    
    const static int ADD_NORMAL = 10;
    
    const static int ADD_FORMAT = 13;
    
    const static int SET_TIME = 0;
    
    const static int ADD_SHELL =1;
    
    const static int ADD_ROCK = 2;
    
    const static int ADD_LEAF = 300;
    
    const static int ADD_AI = 4;
    
    const static int ADD_OBJ = 400;
    
    const static int ADD_TISHI = 500;
    
    const static int PF_TYPE_FISH = 0;
    
    const static int PF_TYPE_SHELL = 1;
    
    const static int PF_TYPE_ROCK = 2;
    
    const static int PF_TYPE_PK = 3;
    
    static cocos2d::CCScene* scene(int player ,int lev);
    
    static GameScene* create(int player ,int lev);
    
    virtual bool init(int player ,int lev);
    
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
    
    ShipManage* getShip();
    
    int getSucType() const;
    
    int getSucAdd() const;
    
    int getSucNum() const;
    
    bool isSuc();
    
    int getStar() const;
    
    int getNowLevel() const;
    
    int getTime() const;
    
    void addHitFish(int hit);
    
    void rmWhale(Fish* fish);
    
    void rmStrong(Fish* fish);
    
    void addItem(const char* name,cocos2d::CCPoint pos,int type,int v,int time);
    void addFlyNum(int type,int num,int shipID,CCPoint pos,CCPoint des);
    
    void setZhenZhu();
    
    void subSucNum();
    
    void allFishToDead(int shipID);
    
    bool canNextLev();
    
    void addMessage(int type,const char* name);
    
    int getMuBiao(int indext);
    
    void setCiTie(int num);
    
    void addBuy();
    
    void removeBuy(bool addFail);
    
    int getScroe(int indext);
    
private:
    
    static GameScene* _instance;
    
    void cycle(float delta);
    
    void addFish(int id);
    
    void addShip();
    
    void setShip(int x);
    
    bool canHook();
    
    void shipAndFish(Ship* ship,Fish* fish, int indext);
    
    void cycleFishs(float delta);
    
    void cycleRocks();
    
    void cycleLeafs();
    void cycleItems();
    
    bool isHookFish(Ship* ship,Fish* fish);
    
    bool isCollideFish(Ship* ship,Fish* fish);
    
    bool isCollideFish(Fish* fish1,Fish* fish2);
    
    bool isCollideFishAtk(Fish* fish1,Fish* fish2);
    
    bool waterCollideShip(Fish* fish,Ship* ship);
    
    void useDolphin(Fish* fish,int i);
    
    void useLightFish(Fish* fish,int i);
    
    void useTortoise(Fish* fish,int i);
    
    void useFishAtk(Fish* fish);
    
    void useFish(Fish* fish,int i);
    
    void setUIScroe(int sc);
    
    void setUIScroe(int indext ,int sc);
    
    void setFishToRun();
    
    void addFish();
    
    
 
    
    
    void setPerfect();
    
    
    void addTeach();
    
    void nextTeach();
    
    bool isMustTeach();
    
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
    
    int _pass_scroe;
    
    int _suc_type;
    
    int _suc_add;
    
    int _suc_num;
    
    bool _isSuc;
    
    int _nowLev;
    int _nowPlayer;
    
    std::vector< std::vector<int> > _data;
    std::vector< std::vector<int> > _add_leaf;
    
    int _fishNum;
    
    int _nowDataInedxt;
    
    bool _isChange;
    
    bool _isAddFormat;
    
    RockManage* _rockLayer;
    
    LeafManage* _leafLayer;
    
    ShellManage* _shellLayer;
    
    ItemManage* _itemLayer;
    
//    CCArray* _formatData;
    
    std::vector<int> _formatData;
    
    GameBegin* _begin;
    
    CCArray* _flyNum;
    
    int _addFlyTime;
    
    Pause* _pause;
    
    CCSprite* zi1;
    CCSprite* zi2;
    
    int _maxScore;
    
    BadEnd* _badEnd;
    SucEnd* _sucEnd;
    
    int _star;
    
    CCSprite* _lianji;
    
    MessageManage* _message;
    
    CCLayerColor* _up;
    CCLayerColor* _left;
    CCLayerColor* _right;
    CCLayerColor* _down;
    
    int _useGetAll;
    
    int _teach_time;
    
    NoGold* _tishi;
};

#endif /* defined(__GetFish__GameScene__) */
