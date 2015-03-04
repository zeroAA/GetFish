//
//  ScrollView.cpp
//
//  Created by zs on 14-6-26.
//
//

#include "ScrollView.h"

#include <math.h>

ScrollView::ScrollView():_isMate(false),_skipOnecMate(false)
{
    
}

ScrollView::~ScrollView()
{
    
}

ScrollView* ScrollView::create(CCSize size, CCNode* container/* = NULL*/)
{
    ScrollView* pRet = new ScrollView();
    if (pRet && pRet->init(size, container))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}


bool ScrollView::init(CCSize size, CCNode *container/* = NULL*/)
{
    if (CCScrollView::initWithViewSize(size,container))
    {
        
        return true;
    }
    return false;
}

void ScrollView::touchBegan()
{
    
    if( !_isMate || ( m_eDirection != kCCScrollViewDirectionHorizontal && m_eDirection != kCCScrollViewDirectionVertical )){
        return;
    }
    
    _mateBegan = m_eDirection == kCCScrollViewDirectionHorizontal ? getContentOffset().x : getContentOffset().y;
    
    _mateBeganTime = clock();
    
    _isLeft = false;
}
bool ScrollView::touchEnd()
{
    if( !_isMate || ( m_eDirection != kCCScrollViewDirectionHorizontal && m_eDirection != kCCScrollViewDirectionVertical )){
        
        
        return false ;
    }
    getMate();
    return true;
}

void ScrollView::touchCancel()
{
    if( !_isMate || ( m_eDirection != kCCScrollViewDirectionHorizontal && m_eDirection != kCCScrollViewDirectionVertical )){
        return ;
    }
    
    clearTouch();
    
}
void ScrollView::clearTouch()
{
   
}

bool ScrollView::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    
   

    
    if (!this->isVisible())
    {
        return false;
    }
    touchBegan();
    
//    float pos = m_eDirection == kCCScrollViewDirectionHorizontal ? getContentOffset().x : getContentOffset().y;
//    
//    CCLOG("posX : %f",pos);
    
    return CCScrollView::ccTouchBegan(touch, event);
    
    
}

void ScrollView::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    
    if (!this->isVisible())
    {
        return;
    }
    
    _oldMateMove = m_eDirection == kCCScrollViewDirectionHorizontal ? getContentOffset().x : getContentOffset().y;
   
    CCScrollView::ccTouchMoved(touch, event);
    
    _mateMove = m_eDirection == kCCScrollViewDirectionHorizontal ? getContentOffset().x : getContentOffset().y;
    
    if (fabs(_mateMove - _oldMateMove)>1) {
        
        _isLeft = _mateMove<_oldMateMove;
    }
}

void ScrollView::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    
    if (!this->isVisible())
    {
        return;
    }
     CCScrollView::ccTouchEnded(touch, event);
    touchEnd();
    
    

}

void ScrollView::ccTouchCancelled(CCTouch* touch, CCEvent* event)
{
    if (!this->isVisible())
    {
        return;
    }
    touchCancel();
   
    CCScrollView::ccTouchCancelled(touch, event);
}

void ScrollView::setMate(int mateMode)
{
    
    _isMate = true;
    _mateNum = m_pContainer->getChildrenCount();
    _mateH = kCCScrollViewDirectionHorizontal ? getViewSize().width/_mateNum : getViewSize().height/_mateNum ;
    
    _mateMode = mateMode;
}

void ScrollView::setMate(float mateH, int mateNum, int mateMode)
{
    
    _isMate = true;
    _mateH = mateH;
    _mateNum = mateNum;
    _mateMode = mateMode;
}

void ScrollView::getMate()
{
    
//    return;
    
    if (_skipOnecMate) {
        _skipOnecMate = false;
        return;
    }
    
    float endTime = clock();
    
    
    if (_mateH<=0) {
        return;
    }
    
    
    
    
    float pos = m_eDirection == kCCScrollViewDirectionHorizontal ? getContentOffset().x : getContentOffset().y;
    
    
    
    int kuai = 0;
    if (pos>0) {
        
        kuai =0;
        
    }else if(pos<-(_mateNum-1)*_mateH){
        
        kuai =_mateNum-1;
    } else{
        
        for (int i = 0; i<_mateNum; ++i) {
            if (i * _mateH <= fabs(pos) && fabs(pos) < (i + 1) * _mateH) {
                
                
                
                
                switch (_mateMode) {
                    case  MATE_NORMAL:
                        
                        
                        
                        if (_isLeft) {
                            
                            kuai =  i + 1;
                            
                        } else {
                            
                            kuai =  i;
                        }
                        break;
                    case MATE_HALF :
                        
                        if (_mateH< (i * _mateH + _mateH / 2)) {
                            
                            kuai = i;
                        } else {
                            
                            kuai = i + 1;
                        }
                        break;
                    case MATE_NEXT :
                        
                        kuai = i + 1;
                        break;
                    case MATE_BEHAND :
                        
                        kuai = i;
                        break;
                }
                
            }
        }
    }
    
    
//    float pageDurateion = 0.3;
//    CCPoint targetPointOffset = m_eDirection == kCCScrollViewDirectionHorizontal ? ccp(-kuai * _mateH, getContentOffset().y ) : ccp(getContentOffset().x, -kuai * _mateH );
//    setContentOffsetInDuration(targetPointOffset, pageDurateion);

    toOneMate(kuai);
    
}

void ScrollView::toOneMate(int num)
{
    
    unscheduleAllSelectors();
    float pageDurateion = 0.3;
    CCPoint targetPointOffset = m_eDirection == kCCScrollViewDirectionHorizontal ? ccp(-num * _mateH, getContentOffset().y ) : ccp(getContentOffset().x, -num * _mateH );
    setContentOffsetInDuration(targetPointOffset, pageDurateion);
}

void ScrollView::skipOnecMate()
{
    _skipOnecMate = true;
}
