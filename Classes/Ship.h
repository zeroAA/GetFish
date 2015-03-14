//
//  Ship.h
//  GetFish
//
//  Created by zs on 14-12-9.
//
//

#ifndef __GetFish__Ship__
#define __GetFish__Ship__

#include "cocos2d.h"
#include "Fish.h"
#include "Actor.h"
#include <vector>


using std::vector;


USING_NS_CC;



class Ship : public Actor
{
public:
    
    const static int ACT_STAND = 0;
    
    const static int ACT_WALK = 1;
    
    const static int ACT_SHOCKED = 2;
    
    const static int ACT_HANDUP = 3;
    
    const static int ACT_FLY = 4;
    
    const static int ACT_FALL = 5;
    
    const static int ACT_FALL_END = 6;
    
    const static int ACT_EATED = 7;
    
    const static int ACT_CUT_LINE = 8;
    
    const static int ACT_PULL = 9;
    
    const static int ACT_TURN_FISH = 10;
    
    const static int ACT_ELE = 11;

        
    const static int TYPE_PLAYER = 0;
    
    const static int TYPE_AI = 1;
    
    const static int HOOK_DIR_UP = 0;
    
    const static int HOOK_DIR_DOWN = 1;
    

    
    static Ship* create(int type ,const char* name);
    
    virtual bool init(int type ,const char* name);
    
    Ship();
    
    virtual ~Ship();
    
    virtual void cycle(float delta);
    
    int getID() const;
    
    bool isCanMove();
    
    void setState(int state);
    
    bool isPlayer();
    
    bool isShipNormal();
    
    void addVolume(int v);
    
    bool isShipFull();
    
    void setDesX(float x);
    
    void setHook(int type);
    
    void hookFish();
    
    void switchHookDir();
    
    void clearHook();
    
    void setHookUp();
    
    bool isHookOver();
    
    void cycleHook();
    
    void setNormal();
    
    void changeToNohurt();
    
    void draw();
    
    void hookFish(Fish* fish);
    
    int getHookDx();
    
    int getHookDy();
    
    CCSprite* getHookAnim();
    
    bool isState(int state);
    
    void reapFishSetHooked();
    
    void trunFish(Fish* fish);
    
    float getX();
    
    float getY();
    
    void setw_Fish(Fish* fish);
    
    Fish* getw_Fish();
    
    void runUpDown();
    
    void runFall();
    
    void setShipTo(float px);
    
    void setStop(float time);
    
    void shipOnAtk();
    
    CCPoint getEatPos() ;
    
    void setCutHookPos();
    
    
    
    void setCutHookY(float y);
    
    
    CCRect getHookLine() const;
    
    void setPullPos(CCPoint pos);
    
    
    void setX(float x);
    
    void setY(float y);
    
    void setXY(float x, float y);
    
    CC_SYNTHESIZE(int, _score, Score);
    
    void addScore(int sc);
    
    int getHookDir() const;
    
private:
    
    void initData();
    
    void initHook();
    
protected:
    
    CCArray* _fishSetHooked;
    
    CCArray* _TurnFish;
    
    CCSize _screenSize;
    
    CCArray* _anims;
    
    int _fishManIndext;
    
    const static int ANIM_FISHMAN_NORMAL=0;
    
   
    int _id;
    
    float _x;
    float _y;
    
    float _desX;
    
    const static int DIR_LEFT = 0;
    
    const static int DIR_RIGHT = 1;
    
    int _dir;
    
    float _speed;
    
    int _volume ;
    
    int _volumeMax;
    
    int _hoolSpeed;
	   
   
    
    int _type ;
    
    const static int LEFT_BORDER = 90;
    
    const static int RIGHT_BORDER = 90;
    
    const static int NO_HURT_TIME_MAX = 40;
    
    int _noHurtTime;
    
    CCSprite* _hook_anim;
    
    float _hookSpeed;
    
    int _hookInitDx;
    
    int _hookInitDy;
    
    int _hookWidth;
    
    int _hookHeight;
    
    float _hookDx;
    
    float _hookDy;
    
    
    
    int _hookDir;
    
    bool _bHasFishHooked;
    
    
	int _hookCurAngle;
	int _hookAngleType;
    
	const static int ANGLE_NULL = 0;
	const static int ANGLE_PLUS = 1;
	const static int ANGLE_MINUS = 2;
    
	int _hookWaveCount;
	int _hookWaveType;
    
	const static int HOOK_WAVE_NULL = 0;
	const static int HOOK_WAVE_UP = 1;
	const static int HOOK_WAVE_DOWN = 2;
    
	const static int ANGLE_0 = 0;
	const static int ANGLE_1 = 1;
	const static int ANGLE_2 = 2;
	const static int ANGLE_3 = 3;
	const static int ANGLE_4 = 4;
	const static int ANGLE_5 = 5;
	const static int ANGLE_10 = 6;
    
    vector<int> ANGLE_TAN;
    
    
    
    int _hit;
    
    int _HOOK_MOVE_DISTANCE;
    
    int _timeC;
    
    Fish* _w_Fish;
    
    int _testTime;
    
    float _stopTime;
    
    CCPoint _cut_Pos;
    
    CCPoint _cut_hook;
    
    CCPoint _pull_pos;
    
    
    
    float _cut_hook_y;
    
    
};

#endif /* defined(__GetFish__Ship__) */
