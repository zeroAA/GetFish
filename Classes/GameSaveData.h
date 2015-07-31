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
    
private:
    
//    static vector<int> leveData;
};

#endif /* defined(__GetFish__GameSaveData__) */
