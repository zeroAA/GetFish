//
//  ScrollView.h
//
//  Created by zs on 14-6-26.
//
//

#ifndef __Zengine__ScrollView__
#define __Zengine__ScrollView__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class ScrollView : public CCScrollView
{
public:
    
    
    const static int MATE_NORMAL = 0;//按滑动方向匹配
    
    const static int MATE_NEXT = 1; //匹配下一个
    
    const static int MATE_BEHAND = 2; //匹配上一个
    
    const static int MATE_HALF = 3; //匹配中心左右的
    
    ScrollView();
    
    virtual ~ScrollView();
    
    bool init(CCSize size, CCNode* container = NULL);
    
    static ScrollView* create(CCSize size, CCNode* container = NULL);
    

    bool isMoveEnd();
    void setMate(float mateH,int mateNum,int mateMode);
    
    void setMate(int mateMode);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    void toOneMate(int num);
    
    void skipOnecMate();
    
    int getMatH() const;
    
    int getNowPage();
    
    void setEnable(bool is);
    
private:
    
    void touchBegan();
    bool touchEnd();
    void touchCancel();
    void clearTouch();
    
    void getMate();
    
protected:
    
    bool _isMate;
    
    float _mateH;
    
    float _mateBegan;
    
    float _mateMove;
    
    float _oldMateMove;
    
    int _mateNum;
   
    int _mateMode;
   
    float _mateBeganTime;
    
    bool _isLeft;
    
    bool _skipOnecMate;
    
    
    bool _isEnable;
};

#endif /* defined(__Zengine__ScrollView__) */
