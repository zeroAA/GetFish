//
//  GameSaveData.cpp
//  GetFish
//
//  Created by zhusu on 15/5/14.
//
//

#include "GameSaveData.h"

void GameSaveData::loadLeveData(){
    if (CCUserDefault::sharedUserDefault()->getStringForKey("has")=="") {
        CCLOG("没存档");
        CCUserDefault::sharedUserDefault()->setStringForKey("has", "has");
        CCUserDefault::sharedUserDefault()->flush();
        CCLOG("建立存档完毕");
    }else{
        CCLOG("有存档 %s",CCUserDefault::sharedUserDefault()->getStringForKey("has").c_str());
    }
    
}