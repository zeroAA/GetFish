//
//  IOSiAP_Bridge.h
//  GetFish
//
//  Created by zhusu on 15/8/18.
//
//

#ifndef __GetFish__IOSiAP_Bridge__
#define __GetFish__IOSiAP_Bridge__
#include <stdio.h>

#include "IOSiAP.h"

class IOSiAP_Bridge : public IOSiAPDelegate
{
public:
    
    const static int IAP_SMALL_GOLD = 1;
    const static int IAP_BIG_GOLD = 2;
    const static int IAP_NEW_GIF = 3;
    const static int IAP_VIP_GIF = 4;
    const static int IAP_GAME_BIG_GOLD = 5;
    const static int IAP_OPEN_VIP = 6;
    
    IOSiAP_Bridge();
    ~IOSiAP_Bridge();
    IOSiAP *iap;
    
    void requestProducts(int);
    virtual void onRequestProductsFinish(void);
    virtual void onRequestProductsError(int code);
    virtual void onPaymentEvent(std::string &identifier, IOSiAPPaymentEvent event, int quantity);
    
    static IOSiAP_Bridge* instance();
    
protected:
    
    int productID;
    
    static IOSiAP_Bridge* _instance;
};



#endif /* defined(__GetFish__IOSiAP_Bridge__) */
