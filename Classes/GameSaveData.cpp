//
//  GameSaveData.cpp
//  GetFish
//
//  Created by zhusu on 15/5/14.
//
//

#include "GameSaveData.h"
#include "Tools.h"
#include "Data.h"

void GameSaveData::loadLeveData(){
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("has")) {
        CCLOG("没存档");
        
        CCUserDefault::sharedUserDefault()->setBoolForKey("IS_ON_MUISC", IS_ON_MUISC);
        CCUserDefault::sharedUserDefault()->setBoolForKey("IS_ON_SFX", IS_ON_SFX);
        CCUserDefault::sharedUserDefault()->setBoolForKey("IS_ON_BUTTON", IS_ON_BUTTON);
        
        CCUserDefault::sharedUserDefault()->setIntegerForKey(("Lev_"+Tools::intToString(0)+"_star").c_str(), 1);
        
        for(int i = 0 ; i < 5;++i){
            CCUserDefault::sharedUserDefault()->setBoolForKey(("player_"+Tools::intToString(i+1)).c_str(), false);
        }
        
        for (int i = 0; i<6; ++i) {
            
            CCUserDefault::sharedUserDefault()->setBoolForKey(("reward_"+Tools::intToString(i)).c_str(), false);

        }
        
        CCUserDefault::sharedUserDefault()->setBoolForKey("teach", false);
        
        CCUserDefault::sharedUserDefault()->setBoolForKey("rest", false);
        
        CCUserDefault::sharedUserDefault()->setBoolForKey("has", true);
        
        CCUserDefault::sharedUserDefault()->setIntegerForKey("All", 3);
        
        CCUserDefault::sharedUserDefault()->setBoolForKey("VIP", false);
        
        CCUserDefault::sharedUserDefault()->setBoolForKey("NewGif", false);
        
        struct cc_timeval tv;
        CCTime::gettimeofdayCocos2d(&tv, NULL);
        long time =(long)tv.tv_sec;
        
        struct tm *tm;
        time_t timep = tv.tv_sec;
        tm = localtime(&timep);
        
        time = time-tm->tm_hour*3600-tm->tm_min*60-tm->tm_sec;
        
        CCUserDefault::sharedUserDefault()->setDoubleForKey("time", time);
        
        
        for (int i = 0; i<7; ++i) {
            CCUserDefault::sharedUserDefault()->setBoolForKey(("gif7_"+Tools::intToString(i)).c_str(), false);
        }
        
        CCUserDefault::sharedUserDefault()->flush();
        CCLOG("建立存档完毕 %ld",time);
    }else{
//        for (int i = 0; i<35; ++i) {
//            saveLevelData(i,5);
//        }
        
        CCLOG("有存档");
    }
    
}

void GameSaveData::saveSetData()
{
//    CCLOG("save set : %i , %i , %i ,",IS_ON_MUISC,IS_ON_SFX,IS_ON_BUTTON);
    CCUserDefault::sharedUserDefault()->setBoolForKey("IS_ON_MUISC", IS_ON_MUISC);
    CCUserDefault::sharedUserDefault()->setBoolForKey("IS_ON_SFX", IS_ON_SFX);
    CCUserDefault::sharedUserDefault()->setBoolForKey("IS_ON_BUTTON", IS_ON_BUTTON);
    CCUserDefault::sharedUserDefault()->flush();
}

void GameSaveData::saveAllData()
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("All", getAll);
    CCUserDefault::sharedUserDefault()->flush();
}

void GameSaveData::loadAllData()
{
    getAll = CCUserDefault::sharedUserDefault()->getIntegerForKey("All");
}

int GameSaveData::loadLevelData(int lev)
{
    
    return CCUserDefault::sharedUserDefault()->getIntegerForKey(("Lev_"+Tools::intToString(lev)+"_star").c_str());
    
}

void GameSaveData::saveLevelData(int lev,int star)
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey(("Lev_"+Tools::intToString(lev)+"_star").c_str(), star);
    
    CCUserDefault::sharedUserDefault()->flush();
}


void GameSaveData::saveGoldData()
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("GOLD", player_gold);
    CCUserDefault::sharedUserDefault()->flush();
}

void GameSaveData::loadGoldData()
{
    player_gold = CCUserDefault::sharedUserDefault()->getIntegerForKey("GOLD");
}

void GameSaveData::loadSetData()
{
    
    IS_ON_MUISC = CCUserDefault::sharedUserDefault()->getBoolForKey("IS_ON_MUISC");
    IS_ON_SFX = CCUserDefault::sharedUserDefault()->getBoolForKey("IS_ON_SFX");
    IS_ON_BUTTON = CCUserDefault::sharedUserDefault()->getBoolForKey("IS_ON_BUTTON");
    
//    CCLOG("load set : %i , %i , %i ,",IS_ON_MUISC,IS_ON_SFX,IS_ON_BUTTON);
}

void GameSaveData::savePlayer(int indext)
{
    CCUserDefault::sharedUserDefault()->setBoolForKey(("player_"+Tools::intToString(indext)).c_str(), true);
    CCUserDefault::sharedUserDefault()->flush();
}

bool GameSaveData::loadPlayer(int indext)
{
    return CCUserDefault::sharedUserDefault()->getBoolForKey(("player_"+Tools::intToString(indext)).c_str());
}

void GameSaveData::saveReward(int indext)
{
    CCUserDefault::sharedUserDefault()->setBoolForKey(("reward_"+Tools::intToString(indext)).c_str(), true);
    CCUserDefault::sharedUserDefault()->flush();
}

bool GameSaveData::loadReward(int indext)
{
    return CCUserDefault::sharedUserDefault()->getBoolForKey(("reward_"+Tools::intToString(indext)).c_str());
}

void GameSaveData::saveTeach()
{
    CCUserDefault::sharedUserDefault()->setBoolForKey("teach", true);
    CCUserDefault::sharedUserDefault()->flush();
}

bool GameSaveData::loadTeach()
{
    return CCUserDefault::sharedUserDefault()->getBoolForKey("teach");
}

void GameSaveData::saveRest()
{
    CCUserDefault::sharedUserDefault()->setBoolForKey("rest", true);
    CCUserDefault::sharedUserDefault()->flush();
}

bool GameSaveData::loadRest()
{
    return CCUserDefault::sharedUserDefault()->getBoolForKey("rest");
}

void GameSaveData::saveVipGif()
{
    CCUserDefault::sharedUserDefault()->setBoolForKey("VIP", true);
    CCUserDefault::sharedUserDefault()->flush();
}

bool GameSaveData::loadVipGif()
{
    return CCUserDefault::sharedUserDefault()->getBoolForKey("VIP");
}

void GameSaveData::saveNewGif()
{
    CCUserDefault::sharedUserDefault()->setBoolForKey("NewGif", true);
    CCUserDefault::sharedUserDefault()->flush();
}

bool GameSaveData::loadNewGif()
{
    return CCUserDefault::sharedUserDefault()->getBoolForKey("NewGif");
}

void GameSaveData::saveGif7(int indext)
{
    CCUserDefault::sharedUserDefault()->setBoolForKey(("gif7_"+Tools::intToString(indext)).c_str(), true);
    CCUserDefault::sharedUserDefault()->flush();
}

bool GameSaveData::loadGif7(int indext)
{
    return CCUserDefault::sharedUserDefault()->getBoolForKey(("gif7_"+Tools::intToString(indext)).c_str());
}

long GameSaveData::loadTime()
{
    return CCUserDefault::sharedUserDefault()->getDoubleForKey("time");
}