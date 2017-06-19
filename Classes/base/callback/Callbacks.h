//
//  Callbacks.h
///  KingdomExpedition3
//  Created by xiacg


#ifndef Callbacks_h
#define Callbacks_h

#include "cocos2d.h"
#include  "cocos-ext.h"
#include <string>

USING_NS_CC;
USING_NS_CC_EXT;

using std::string;

typedef void (Ref::*GameCallBackRequest)(rapidjson::Document& o, string requestData);
typedef void (Ref::*HttpErrorCallBack)(string api);
typedef void (Ref::*GameCallBack)();
typedef void (Ref::*GameCallBackI)(int status);
typedef void (Ref::*GameCallBackO)(Ref* o);
typedef void (Ref::*GameAlertCallBack)(int flag,Ref* extraData);
typedef void (Ref::*GameCallBackNO)(Ref* target,Ref* o);

#define callbackRequest_selector(_SELECTOR)(GameCallBackRequest)(&_SELECTOR)
#define callbackHttpError_selector(_SELECTOR)(HttpErrorCallBack)(&_SELECTOR)
#define callback_selector(_SELECTOR) (GameCallBack)(&_SELECTOR)
#define callbacki_selector(_SELECTOR) (GameCallBackI)(&_SELECTOR)
#define callbacko_selector(_SELECTOR) (GameCallBackO)(&_SELECTOR)
#define callbackAlert_selector(_SELECTOR)(GameAlertCallBack)(&_SELECTOR)
#define callbackno_selector(_SELECTOR)(GameCallBackNO)(&_SELECTOR)

#endif /* Callbacks_h */
