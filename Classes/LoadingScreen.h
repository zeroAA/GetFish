#ifndef __Zengine__LoadingScreen__
#define __Zengine__LoadingScreen__

#include "cocos2d.h"
USING_NS_CC;

class LoadingScreen : public CCScene
{
public:
    static LoadingScreen* create(const int screenid, const std::vector<int> param);
    
    LoadingScreen();
    
    bool init(const int screenId, const std::vector<int> param);
    
    virtual ~LoadingScreen();
    
    virtual void onEnter();
    
    virtual void onEnterTransitionDidFinish();
    
    virtual void onExit();
    
private:
    void loadNextScreen(CCTime delta);
    
protected:
    int _nextScreenId;
    
    std::vector<int> _nextScreenParam;
};

#endif /* defined(__Zengine__LoadingScreen__) */
