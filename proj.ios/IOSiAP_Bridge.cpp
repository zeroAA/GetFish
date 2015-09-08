//
//  IOSiAP_Bridge.cpp
//  GetFish
//
//  Created by zhusu on 15/8/18.
//
//

#include "IOSiAP_Bridge.h"
#include "cocos2d.h"
#include "MapScene.h"
#include "Data.h"
#include "GameSaveData.h"
#include "GameScene.h"
#include "Common.h"

USING_NS_CC;

IOSiAP_Bridge* IOSiAP_Bridge::_instance = NULL;

IOSiAP_Bridge* IOSiAP_Bridge::instance()
{
    if(NULL == _instance) {
        _instance = new IOSiAP_Bridge();
    }
    
    return _instance;
}

IOSiAP_Bridge::IOSiAP_Bridge()
{
    iap = new IOSiAP();
    iap->delegate = this;
}

IOSiAP_Bridge::~IOSiAP_Bridge()
{
    delete iap;
}

void IOSiAP_Bridge:: requestProducts(int id)
{
    productID = id;
    std::vector<std::string> product;
    product.push_back("getfish100");
    product.push_back("getfish101");
    product.push_back("getfish102");
    product.push_back("getfish103");
    //把需要付费的道具的所有product id都放到容器里面传进去
    iap->requestProducts(product);
}

void IOSiAP_Bridge::onRequestProductsFinish(void)
{
    std::string identifier = "";
    switch (productID) {
        case IAP_SMALL_GOLD:
            identifier = "getfish100";
            break;
        case IAP_GAME_BIG_GOLD:
        case IAP_BIG_GOLD:
            identifier = "getfish101";
            break;
        case IAP_NEW_GIF:
            identifier = "getfish102";
            break;
        case IAP_OPEN_VIP:
        case IAP_VIP_GIF:
            identifier = "getfish103";
            break;
        default:
            break;
    }
    
    //必须在onRequestProductsFinish后才能去请求iAP产品数据。
    IOSProduct *product = iap->iOSProductByIdentifier(identifier);
    // 然后可以发起付款请求。,第一个参数是由iOSProductByIdentifier获取的IOSProduct实例，第二个参数是购买数量
    iap->paymentWithProduct(product, 1);
    
    CCLOG("go!");
}

void IOSiAP_Bridge::onRequestProductsError(int code)
{
    //这里requestProducts出错了，不能进行后面的所有操作。
    CCLOG("付款失败 code : %i",code);
    
    switch (productID) {
        case IAP_SMALL_GOLD:
        case IAP_BIG_GOLD:
        case IAP_NEW_GIF:
        case IAP_VIP_GIF:
        case IAP_OPEN_VIP:
            
            MapScene::instance()->removeBuy(true);
            
            break;
        case IAP_GAME_BIG_GOLD:
            GameScene::instance()->removeBuy(true);
            break;
        default:
            
            break;
    }
}

void IOSiAP_Bridge::onPaymentEvent(std::string &identifier, IOSiAPPaymentEvent event, int quantity)
{
    CCLOG("付款event %i",event);
    if (event == IOSIAP_PAYMENT_PURCHAED) {
        //付款成功了，可以吧金币发给玩家了。
        //根据传入的参数就能知道购买的是哪种类型的金币
        switch (productID) {
            case IAP_SMALL_GOLD:
                CCLOG("付款成功100");
                player_gold+=23000;
                
                MapScene::instance()->setGold();
                
                GameSaveData::saveGoldData();
                break;
            case IAP_BIG_GOLD:
                CCLOG("付款成功101");
                player_gold+=75000;
                
                MapScene::instance()->setGold();
                
                GameSaveData::saveGoldData();
                break;
            case IAP_NEW_GIF:
                CCLOG("付款成功102");
                
                GameSaveData::savePlayer(4);
                
                getAll+=5;
                
                GameSaveData::saveAllData();
                GameSaveData::saveNewGif();
                
                
                MapScene::instance()->setShopButton(3);
                
                break;
            case IAP_OPEN_VIP:
            case IAP_VIP_GIF:
                CCLOG("付款成功103");
                
                for (int i = 0; i<72; ++i) {
                    if (GameSaveData::loadLevelData(i)<=0) {
                        GameSaveData::saveLevelData(i, 1);
                    }
                }
                
                for (int i = 0; i<6; ++i) {
                    GameSaveData::savePlayer(i);
                }
                
                getAll+=99;
                
                GameSaveData::saveAllData();
                GameSaveData::saveVipGif();
                
                select_player = 5;
                
                if (productID == IAP_VIP_GIF) {
                    MapScene::instance()->setShopButton(2);
                }else{
                    
                    MapScene::instance()->changeToMap();
                }
                
                break;
            case IAP_GAME_BIG_GOLD:
                CCLOG("付款成功101");
                
                player_gold+=75000;
                                
                GameSaveData::saveGoldData();
                getAll+=1;
                
                GameSaveData::saveAllData();
                GameScene::instance()->setCiTie(getAll);

                break;
            default:
                CCLOG("未知的付款类型");
                break;
        }
        
        
    }else if(event == IOSIAP_PAYMENT_FAILED){
        
        switch (productID) {
            case IAP_SMALL_GOLD:
            case IAP_BIG_GOLD:
            case IAP_NEW_GIF:
            case IAP_VIP_GIF:
            case IAP_OPEN_VIP:    
                MapScene::instance()->removeBuy(true);
                
                break;
            case IAP_GAME_BIG_GOLD:
                GameScene::instance()->removeBuy(true);
                break;
            default:
                
                break;
        }
        
    }else{
        switch (productID) {
            case IAP_SMALL_GOLD:
            case IAP_BIG_GOLD:
            case IAP_NEW_GIF:
            case IAP_VIP_GIF:
            case IAP_OPEN_VIP:
                MapScene::instance()->removeBuy(false);
                break;
            case IAP_GAME_BIG_GOLD:
                GameScene::instance()->removeBuy(false);
                break;
            default:
                
                break;
        }
    }
    //其他状态依情况处理掉。
}
