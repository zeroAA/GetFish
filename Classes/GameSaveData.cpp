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
    if (CCUserDefault::sharedUserDefault()->getStringForKey("has")=="") {
        CCLOG("没存档");
        
        CCUserDefault::sharedUserDefault()->setBoolForKey("IS_ON_MUISC", IS_ON_MUISC);
        CCUserDefault::sharedUserDefault()->setBoolForKey("IS_ON_SFX", IS_ON_SFX);
        CCUserDefault::sharedUserDefault()->setBoolForKey("IS_ON_BUTTON", IS_ON_BUTTON);
        
        CCUserDefault::sharedUserDefault()->setIntegerForKey(("Lev_"+Tools::intToString(0)+"_star").c_str(), 1);
        
        for(int i = 0 ; i < 5;++i){
            CCUserDefault::sharedUserDefault()->setBoolForKey(("player_"+Tools::intToString(i+1)).c_str(), false);
        }
        
        CCUserDefault::sharedUserDefault()->setStringForKey("has", "has");
        CCUserDefault::sharedUserDefault()->flush();
        
        CCLOG("建立存档完毕");
    }else{
//        for (int i = 0; i<35; ++i) {
//            saveLevelData(i,5);
//        }
        
        CCLOG("有存档 %s",CCUserDefault::sharedUserDefault()->getStringForKey("has").c_str());
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
//    vector<int> data;
//    data.push_back();
    
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
}

bool GameSaveData::loadPlayer(int indext)
{
    return CCUserDefault::sharedUserDefault()->getBoolForKey(("player_"+Tools::intToString(indext)).c_str());
}