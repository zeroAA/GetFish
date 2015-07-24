//
//  Tools.h
//  GetFish
//
//  Created by zs on 14-4-21.
//
//

#ifndef __GetFish__Tools__
#define __GetFish__Tools__

#include <iostream>
#include <string>
#include <math.h>
//#include <sstream>

#include "cocos2d.h"

#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

enum ScreenRationProfile
{
    KScreenRatioProfile3v4 = 0,
    KScreenRatioProfile2v3,
    KScreenRatioProfile10v16,
    KScreenRatioProfile10v17,
    KScreenRatioProfile9v16,
};

extern bool IS_ON_BUTTON;

class Tools
{
public:
    
    
    
    static CCRect rectMix(const CCRect& src1, const CCRect& src2);
    
    static float randomFloatInRange(float minInclusive, float maxInclusive);
    
    static int randomIntInRange(int minInclusive, int maxInclusive);
    
    static string intToString(int num);
    
    static string floatToString(float num);
    
    static int stringToInt(const string& str);
    
    static float stringToFloat(const string& str);
    
    static string pointToString(const CCPoint& pos);
    
    static CCPoint stringToPoint(const string& str);
    
    static string eliminateSuffix(string original, const char* mark);
    
    static vector<string> componentsSeparatedByString(const string& str, const string& delim);
    
    static string stringByTrimmingWhiteSpaceAndTab(string str, const string& delim);
    
    static bool hasPrefix(const string &s1, const string & s2);
    
//    static int rectOnRect(CCRect rect1 , CCRect rect2);//0左上 1上 2右上 3右 4右下 5下 6左下 7左 -1 包含关系
    
    const static int RECT_UP = 1;
    
    const static int RECT_RIGHT = 3;
    
    const static int RECT_DOWN = 5;
    
    const static int RECT_LEFT = 7;
    
    const static int RECT_IN = -1;
    
    static int rectOnRect(CCRect rect1 , CCRect rect2);// 1上  3右  5下 7左 -1 包含关系
    
    /* Resolution */
    static int calScreenRatioProfile(const CCSize& sz);
    
    static int int_abs(int a);
    
//private:
//    static int _profile;
};

#endif /* defined(__GetFish__Tools__) */
