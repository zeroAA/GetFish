//
//  Tools.cpp
//  GetFish
//
//  Created by zs on 14-4-21.
//
//

#include "Tools.h"

CCRect Tools::rectMix(const CCRect& src1, const CCRect& src2)
{
    CCRect result;
    
    float x1 = MIN(src1.getMinX(), src2.getMinX());
    float y1 = MIN(src1.getMinY(), src2.getMinY());
    float x2 = MAX(src1.getMaxX(), src2.getMaxX());
    float y2 = MAX(src1.getMaxY(), src2.getMaxY());
    
    result.origin=ccp(x1,y1);
    result.size=CCSizeMake(x2-x1, y2-y1);
    return result;
}

float Tools::randomFloatInRange(float minInclusive, float maxInclusive)
{
    return minInclusive + (CCRANDOM_0_1() * (maxInclusive - minInclusive));
}

int Tools::randomIntInRange(int minInclusive, int maxInclusive)
{
    float randomSeed = CCRANDOM_0_1();
    return minInclusive + ((int) floorf(randomSeed * (maxInclusive - minInclusive)));
}

string Tools::intToString(int num)
{
    stringstream ss;
    ss << num;
    string s = ss.str();
    return s;
}

string Tools::floatToString(float num)
{
    stringstream ss;
    ss << num;
    string s = ss.str();
    return s;
}

int Tools::stringToInt(const string& str)
{
    int num = 0;
    
    stringstream ss(str);
    
    ss >> num;
    
    return num;
}

float Tools::stringToFloat(const string &str)
{
    float num = 0;
    
    stringstream ss(str);
    
    ss >> num;
    
    return num;
    
}

string Tools::pointToString(const CCPoint &pos)
{
    float x = pos.x;
    float y = pos.y;
    string str = Tools::floatToString(x) + ":" + Tools::floatToString(y);
    return str;
}

CCPoint Tools::stringToPoint(const string &str)
{
    vector<string> v = Tools::componentsSeparatedByString(str, ":");
    float x = Tools::stringToFloat(v[0]);
    float y = Tools::stringToFloat(v[1]);
    return ccp(x, y);
}

string Tools::eliminateSuffix(string original, const char* mark)
{
    int lastindex = original.find_last_of(mark);
    return original.substr(0, lastindex);
}

vector<string> Tools::componentsSeparatedByString(const string &str, const string& delim)
{
    vector<string> tokens;
    string::size_type lastPos = 0;
    string::size_type pos = str.find(delim, lastPos);
    while(string::npos != pos)
    {
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = pos + delim.size();
        pos = str.find(delim, lastPos);
    }
    
    tokens.push_back(str.substr(lastPos, str.size() - lastPos));
    return tokens;
}

string Tools::stringByTrimmingWhiteSpaceAndTab(string str, const string& delim)
{
    string::size_type pos = 0;
    pos = str.find_first_of(delim, pos);
    if(pos == string::npos)
        return str;
    return stringByTrimmingWhiteSpaceAndTab(str.erase(pos, 1), delim);
}

bool Tools::hasPrefix(const string &s1, const string &s2)
{
    const char* p = s1.c_str();
    const char* q = s2.c_str();
    while(*p && *q)
        if(*p++ != *q++)
            return false;
    return true;
    
}

int Tools::rectOnRect(CCRect rect1, CCRect rect2)
{
//    if (rect1.getMinX()<=rect2.getMinX()&&rect1.getMinY()>=rect2.getMaxY()) {
//        return 0;
//    }
    if (rect1.getMinY()>=rect2.getMaxY()) {
        return RECT_UP;
    }
    
    if (rect1.getMaxY()<=rect2.getMinY()) {
        return RECT_DOWN;
    }
    
    if (rect1.getMaxX()<=rect2.getMinX()) {
        return RECT_LEFT;
    }
    
    if (rect1.getMinX()>=rect2.getMaxX()) {
        return RECT_RIGHT;
    }
}

int Tools::calScreenRatioProfile(const cocos2d::CCSize &sz)
{
    int _profile = KScreenRatioProfile2v3;
    float r = sz.height / sz.width;
    CCLOG("r = %f", r);//0.667
    float r1 = 768.0 / 1024.0;//0.75
    float r2 = 320.0 / 480.0;//0.667
    float r3 = 480.0 / 800.0;//0.6
    float r4 = 480.0 / 854.0;//0.5602
    if (r >= (r1 + r2) * 0.5) {//0.705
        _profile = KScreenRatioProfile3v4;
    }
    else if (r >= (r2 + r3) * 0.5) {//0.6335
        _profile = KScreenRatioProfile2v3;
    }
    else if (r >= (r3 + r4) * 0.5) {//0.5801
        _profile = KScreenRatioProfile10v16;
    }
    else {
        _profile = KScreenRatioProfile10v17;
    }
    return _profile;
    
}

int Tools::int_abs(int a)
{
    return abs(a);
}