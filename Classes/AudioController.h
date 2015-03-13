//
//  AudioController.h
//  Zengine
//
//  Created by zs on 15-2-19.
//
//

#ifndef __Zengine__AudioController__
#define __Zengine__AudioController__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include <string>
USING_NS_CC;
using namespace std;

#define AUDIO AudioController::Instance()

class AudioController : public CCObject {
    
public:
    static AudioController* Instance();
    
    virtual ~AudioController();
    
    bool init();
    
    void pauseBgMusic();
    
    void pauseSfx();
    
    void end();
    
    void resumeBgMusic();
    
    void resumeSfx();
    
    void playSfx(string clip);
    
    void playBgMusic(string clip, bool loop);
    
    void playOldBgMusic();
    
    void preloadSfx(string clip);
    
    void preloadBackGroundMusic(string clip);
    
    void unloadSfx(string clip);
    
    void onSchedulePlayEffectDelay();
    
    void stopAllEffects();
    
    string getNowBg() const;
    
    void setOldBg(const string &old);
    
    string getOldBg() const;
    
private:
    AudioController();
    
    static AudioController* _instance;
    
protected:
    CocosDenshion::SimpleAudioEngine* _engine;
    
    string _bgMusic;
    
    string _oldbgMusic;
};


#endif /* defined(__Zengine__AudioController__) */
