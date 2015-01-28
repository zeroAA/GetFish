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
    
    int getNowButtonID() const;
    
    void setTime(int time);
    
    void setScore(float sc);
    
    void addMubiaoScore( std::vector<int> mubiao);
    
private:
    
    CCSize _screenSize;
    
    ButtonWithSpriteManage* _buttons;
    
    CCLabelAtlas* _timeLabel;
    
    CCProgressTimer* _score_tiao;
};


#endif /* defined(__GetFish__GameUI__) */
