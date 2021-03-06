//
//  GameSaveData.h
//  GetFish
//
//  Created by zhusu on 15/5/14.
//
//

#ifndef __GetFish__GameSaveData__
#define __GetFish__GameSaveData__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class GameSaveData
{
public:
//    static void saveLeveData(int indext,int levData);
//    
//    static int getLeveData(int indext);
    
    static void loadLeveData();
    
    static void saveGoldData();
    
    static void loadGoldData();
    
    static void saveAllData();
    
    static void loadAllData();
    
    static void saveSetData();
    static void loadSetData();
    
    static void saveLevelData(int lev,int star);
    static int loadLevelData(int lev);
    
    static void savePlayer(int indext);
    
    static bool loadPlayer(int indext);
    
    static void saveReward(int indext);
    static bool loadReward(int indext);
    
    static void saveTeach();
    
    static bool loadTeach();
    
    static void saveRest();
    
    static bool loadRest();
    
    static void saveNewGif();
    
    static bool loadNewGif();
    
    static void saveVipGif();
    
    static bool loadVipGif();
    
    static void saveGif7(int indext);
    
    static bool loadGif7(int indext);
    
    static long loadTime();
    
private:
    
//    static vector<int> leveData;
};

#endif /* defined(__GetFish__GameSaveData__) */
