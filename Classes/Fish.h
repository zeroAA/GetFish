//
//  Fish.h
//  GetFish
//
//  Created by zs on 14-12-8.
//
//

#ifndef __GetFish__Fish__
#define __GetFish__Fish__

#include "cocos2d.h"

#include "Actor.h"

USING_NS_CC;


class Fish : public Actor
{
public:
    
    const static int ACT_STATE_NORMAL = 0;
    
    const static int ACT_STATE_HOOKED = 1;
    
    const static int ACT_STATE_FAINT = 2;
    
    const static int ACT_STATE_SHOCK = 3;
    
    const static int ACT_STATE_ESCAPE = 4;
    
    const static int ACT_STATE_FALL = 5;
    
    const static int ACT_STATE_FALLRUN = 6;
    
    const static int ACT_STATE_REST = 7;
    
    const static int ACT_STATE_GETEAT = 8;
    
    const static int ACT_STATE_RUN = 9;
    
    const static int ACT_STATE_RACR = 10;
    
    const static int ACT_STATE_SKILL = 11;
    
    const static int ACT_STATE_DEAD = 12;
    
    const static int ACT_STATE_WALK = 13;
    
    const static int ACT_STATE_GO = 14;
    
    const static int ACT_STATE_STAY = 15;
    
    const static int ACT_STATE_DOLPHIN_READY = 16;
    
    const static int ACT_STATE_DOLPHIN_ATK = 17;
    
    const static int ACT_STATE_LIGHT = 18;
    
    const static int ACT_STATE_TORTOISE = 19;
    
    const static int ACT_STATE_GOTOSHIP = 20;
    
    const static int ACT_STATE_ZHUANG_STAY = 21;
    
    const static int ACT_STATE_ZHUANG_END = 22;
    
    const static int ACT_STATE_ZHUANG_ATK = 23;
    
    const static int ACT_STATE_HAN_UP = 24;
    
    const static int ACT_STATE_HAN_ATK = 50;
    
    const static int ACT_STATE_DEN = 25;
    
    const static int ACT_STATE_GO_TIME = 26;
    
    const static int ACT_STATE_GO_TIME_DOWN = 27;
    
    const static int ACT_STATE_TORTOISE_READY = 28;
    
    const static int ACT_STATE_GOTO_EAT = 29;
    
    const static int ACT_STATE_GOTO_DES = 30;
    
    const static int ACT_STATE_TURN = 31;
    
    const static int ACT_STATE_LIGHT_READY = 32;
    
    const static int ANIM_RIGHT = 0;
    const static int ANIM_LEFT = 1;
    const static int ANIM_HOOK = 2;
    const static int ANIM_TURN = 3;
    
    const static int ANIM_ATK_READY = 4;
    
    const static int ANIM_ATK = 6;
    
    
    const static int NORMAL_B = 0; // 普通鱼起始
    
    const static int NORMAL_E = 1000;//普通鱼结束
    
    const static int DOLPHIN = 1110;//海豚
    
	const static int LIGHTFISH = 1120;//灯笼鱼
    
	const static int TORTOISE = 1130;//乌龟
   
	const static int WHALE = 1140;//鲸鱼
    
	const static int EATFISH = 1150;//食人鱼
    
	const static int SHARK = 1160;//鲨鱼
    
	const static int SWORDFISH = 1170;//剑鱼
    
	const static int STRONGFISH = 1180;//大力
    
	const static int ELEFISH = 1190;//电鱼
    
	const static int FLYFISH_B = 1300;//飞起金币鱼起始
    
	const static int FLYFISH_E = 1400;//飞起金币鱼结束
    
    const static int FISH_Y_MIN = 370;
    
    const static int FISH_Y_MAX = 50;
    
    const static int DIR_LEFT = 0;
    
    const static int DIR_RIGHT = 1;
    
    const static int HOOK_DEAD = 0;
    
    const static int EXIT_MAP_DEAD = 1;
    
    const static int OWN_DEAD = 2;
    
    const static int POW_DEAD = 3;//磁铁
    
    const static int EXIT_DEAD_NORMAL = 0;
    
    const static int EXIT_DEAD_LEFT = 1;
    
    const static int EXIT_DEAD_RIGHT = 2;
    
    const static int EXIT_DEAD_NO = 3;
    
    static Fish* create(int type,float speed , int dir,const char* name);
    
    virtual bool init(int type,float speed , int dir,const char* name);
    
    Fish();
    
    virtual ~Fish();
    
    virtual void cycle(float delta);
    
    
    
    bool isUseFish();
    
    int getID();
    
    void setSpeed(float spdx,float spdy);
    
    bool isExitMap();
    
    bool isExitMapLeft();
    
    bool isExitMapRight();
    
//    void draw();
    
    bool isFishDead();
    
    bool isState(int state);
    
    void setShipID(int id);
    
    bool isCanHooked();
    
    bool isHooked();
    
    bool issetXY();
    
    int getShipID();
    
    void setDead(bool isdead);
    
    void setState(int state);
    
    void setSpeedX(float sx);
    
    void setSpeedY(float sy);
    
    int getVolume();
    
    void setXY(float x , float y);
    
    void setTurn();
    
    bool isNormalFish();
    
    bool isDolphin();
    
    bool isLightFish();
    
    bool isTortoise();
    
    void setAnim(int anim);
    
    bool isHook();
    
    bool isShark();
    
    bool isWhale();
    
    bool isEat();
    
    bool isSword();
    
    bool isStrong();
    
    bool isEle();
   
    
    void setGo();
    
    void setTortoiseC(int c);
    
    void setTortoiseR();
    
    void setSharkAnim();
    
    int getDir();
    
    float getX();
    
    float getY();
    
    void setDes(float desX,float desY,float time);
    
    void setStartPos(float x,float y);
    
    void setOLDY(float y);
    
    void setAY(float a);
    
    float getSpeedY() const;
    
    void setDeadTime( float time);
    
    int getType() const;
    
    void setDeadType(int type);
    
    void setChangeTime(float time);
    
    void setStayTime(float time);
    
    CC_SYNTHESIZE(int, _score, Score);
    
    int getDeadType() const;
    
    void setExitDeadType(int type);
    
private:
    
    void initData();

protected:
    CCSize _screenSize;
    
  
    int _id;
    float _speedx;
    float _speedy;
    
    float _aY;

    
    int _dir;
    
//    int _state = ACT_STATE_WALK;
    
    int _volume;
    
    float _x;
    
    float _y;
    
    float _oldy;
    
    bool _isDead;
    
    
    
    int _deadType ;
    
    
    
    int _exitDead ;
    
    int _shipID;
    
    int _tortoiseC;
    
    int _stayTime;
    
    float _startX;
    
    float _startY;
    
    float _deadTime;
    
    float _changeTime;
    
};

#endif /* defined(__GetFish__Fish__) */
