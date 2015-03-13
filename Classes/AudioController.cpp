//
//  AudioController.cpp
//  Zengine
//
//  Created by zs on 15-2-19.
//
//

#include "AudioController.h"

#define KExtension ".mp3"

AudioController* AudioController::_instance = NULL;

AudioController::AudioController():_engine(CocosDenshion::SimpleAudioEngine::sharedEngine())
{
    
}

AudioController* AudioController::Instance()
{
    if(NULL == _instance)
    {
        _instance = new AudioController();
        if(!_instance->init())
        {
            CC_SAFE_DELETE(_instance);
        }
    }
    return _instance;

}

bool AudioController::init()
{
    
    _oldbgMusic="";
    _bgMusic="";
    bool bRet = false;
    do {
        CC_BREAK_IF(!_engine);
        bRet = true;
    } while (0);
    return bRet;
}




AudioController::~AudioController()
{
    _engine->end();
}

void AudioController::playBgMusic(string clip, bool loop)
{
    /*if(_engine->isBackgroundMusicPlaying()) {
        _engine->stopBackgroundMusic();
    }*/
//    return;
    _bgMusic = clip + KExtension;
    
    _engine->setBackgroundMusicVolume(0.5);
    _engine->playBackgroundMusic(_bgMusic.c_str(), true);

}

void AudioController::playSfx(string clip)
{
//    return;
    string music = clip + KExtension;
    _engine->preloadEffect(music.c_str());
    int soundId = _engine->playEffect(music.c_str());
}

void AudioController::preloadSfx(string clip)
{
    string sfxName = clip + KExtension;
    _engine->preloadEffect(sfxName.c_str());
}

void AudioController::preloadBackGroundMusic(string clip)
{
    string sfxName = "Music/" + clip + KExtension;
    _engine->preloadBackgroundMusic(sfxName.c_str());
    
}

void AudioController::unloadSfx(string clip)
{
    string sfxName = clip + KExtension;
    _engine->unloadEffect(sfxName.c_str());

}

void AudioController::stopAllEffects()
{
	_engine->stopAllEffects();
}

void AudioController::pauseBgMusic()
{
   
    _engine->pauseBackgroundMusic();
}

void AudioController::pauseSfx()
{
    _engine->pauseAllEffects();
}

void AudioController::resumeBgMusic()
{
    _engine->resumeBackgroundMusic();
}

void AudioController::resumeSfx()
{
    _engine->resumeAllEffects();
}

void AudioController::end()
{
    _engine->end();
}

string AudioController::getNowBg() const
{
    return _bgMusic;
}

string AudioController::getOldBg() const
{
    return _oldbgMusic;
}

void AudioController::setOldBg(const string &old)
{
    _oldbgMusic = old;
}
