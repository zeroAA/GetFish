//
//  GameUI.h
//  GetFish
//
//  Created by zhusu on 15/1/27.
//
//

#ifndef __GetFish__GameUI__
#define __GetFish__GameUI__

#include "cocos2d.h"
#include "ButtonWithSpriteManage.h"

USING_NS_CC;

class GameUI : public CCLayer
{
public:
    
    static const int DIR_NONE = 0;
    static const int DIR_LEFT = 1;
    static const int DIR_RIGHT = 2;
    
    
    
    CREATE_FUNC(GameUI);
    
    GameUI();
    
    virtual bool init();
    
    virtual ~GameUI();
    
    virtual void onEnter();
    
    virtual void onExit();
    
    bool GameUItouchesBegan(CCSet * touchs,CCEvent * event);
    
    void GameUItouchesMoved(CCSet * touchs,CCEvent * event);
    
    void GameUItouchesCancelled(CCSet * touchs,CCEvent * event);
    
    void GameUItouchesEnded(CCSet * touchs,CCEvent * event);
    
    void GameUItouchesDir(CCSet * touchs,CCEvent * event);
    void GameUItouchesMovedDir(CCSet * touchs,CCEvent * event);
//    void GameUItouchesEndDir(CCSet * touchs,CCEvent * event);
    
    int getNowButtonID() const;
    
    void setTime(int time);
    
    void setScoreTiao(float sc);
    
     void setScoreTiao1(float sc);
    
    void setScore(int sc);
    
    void setScore1(int sc);
    
    void addMubiaoScore( std::vector<int> mubiao);
    
    void addSucLab(int type , int );
    
    void setSucNum(std::string str);
    
    void setSuc();
    
    CCSprite* getLeft();
    CCSprite* getRight();
    CCSprite* getHook();
    
    CC_SYNTHESIZE(int, _dir, Dir);
    
    CC_SYNTHESIZE(bool, _ishook, isHook);
    
    void setCitieNum(int num);
    
private:
    
    CCSize _screenSize;
    
    ButtonWithSpriteManage* _buttons;
    
    CCLabelAtlas* _timeLabel;
    
    CCLabelAtlas* _citieLabel;
    
    CCLabelAtlas* _score_Label;
    CCLabelAtlas* _score_Label1;
    
    CCProgressTimer* _score_tiao;
    
    CCProgressTimer* _score_tiao1;
    
    CCSprite* _left;
    
    CCSprite* _right;
    
    CCSprite* _hook;
    
    CCLabelAtlas* _num;
    
    CCNode* _node;
    
    CCSprite* zuodi;
};


#endif /* defined(__GetFish__GameUI__) */
