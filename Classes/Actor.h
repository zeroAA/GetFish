//
//  Actor.h
//  GetFish
//
//  Created by zs on 14-4-18.
//
//

#ifndef __GetFish__Actor__
#define __GetFish__Actor__

#include "cocos2d.h"

#include "cocos-ext.h"
USING_NS_CC;
using namespace cocos2d::extension;

class Actor : public CCArmature
{
public:
        
    const static int STATE_NORMAL = 100;
    
    const static int STATE_DEAD = 101;
    
    static Actor* create(const char *name);
    
    virtual bool init(const char *name);
    
    Actor();
    
    virtual ~Actor();
    
    void setState(int state);
    
    int getState() const;
    
    virtual void onEnter();
    
    virtual void onExit();
    
    /**
     * Get current movementID
     * @return The name of current movement
     */
    std::string getCurrentMovementID();
    
//    virtual void draw();
    
    virtual void cycle(float delta);
    
    void actorCycle(float delta);
    
    virtual CCRect getBodyRect() ;
    
    virtual CCRect getBodyRect(int indext) ;
    
    virtual void setBodyPonit();
    
    void playWithIndex(int index);
    
    void play(const char *animationName);
    
    void setAutoDead(bool isDead);
    
private:
    
    
    
protected:
    
    bool _isAutoDead;
    
    int _state;
    
    CCSize _screenSize;
    
    int _proState;
    
    std::vector<CCPoint> _body1;
    std::vector<CCPoint> _body2;
    
    
};


#endif /* defined(__GetFish__Actor__) */
