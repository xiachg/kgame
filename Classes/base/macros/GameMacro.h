//
//  GameMacro.h
//  KingdomExpedition3
//  Created by xiacg


#ifndef kgame_GameMacro_h
#define kgame_GameMacro_h

#include"cocos2d.h"
#include"cocos-ext.h"
#include"editor-support/cocostudio/CCSGUIReader.h"
#include"editor-support/cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"

USING_NS_CC_EXT;
USING_NS_CC;

using namespace cocos2d::ui;
using namespace cocostudio;

//该宏可以安全的对Ref*对象进行赋值 对于Widget对象不需要retain其他的均需要retain才行
#define GAME_SAFE_ASSIGN(a,b)\
if (b)\
{\
	CC_SAFE_RETAIN(b); \
	GAME_SAFE_RELEASE(a); \
	a = b; \
}\
else\
{\
	CC_SAFE_RELEASE_NULL(a); \
}

//该宏可以安全的对Ref*对象进行release释放引用 对于Widget对象不需要release其他的均需要release才行
#define GAME_SAFE_RELEASE(a)\
if (a)\
{\
	a->release(); \
	a = NULL; \
}

#define GET_GAME_MAIN_LAYER (BaseScene::getInstance()->getCurrentLayer())
#define GET_GAME_MAIN_SCENE (BaseScene::getInstance()->getCurrentScene())

#define CREATE_UILAYOUT_FUNC(__TYPE__) \
	static __TYPE__* create(Widget* obj) \
{ \
	__TYPE__ *pRet = new __TYPE__(); \
if (pRet && pRet->init() && pRet->initByUI(obj)) \
{ \
	pRet->autorelease(); \
	return pRet; \
} \
	else \
{ \
	delete pRet; \
	pRet = NULL; \
	return NULL; \
} \
}

#define CREATE_FUNC_SCENE(_TYPE_)\
	static Scene* createScene(Ref* pSender = NULL)\
{\
	Scene* scene = Scene::create(); \
	scene->setTag(SCENE_##_TYPE_); \
	_TYPE_* layer = _TYPE_::create(pSender); \
	layer->setTag(0); \
	scene->addChild(layer); \
	return scene; \
}

#define CREATE_FUNC_LAYER(_TYPE_)\
	static _TYPE_* create(Ref* pSender)\
{\
	_TYPE_* pRet = new _TYPE_(); \
if (pRet && pRet->init(pSender))\
{\
	pRet->autorelease(); \
	return pRet; \
}\
else\
{\
	delete pRet; \
	pRet = NULL; \
	return NULL; \
}\
}

#define GAME_CREATE_COMMON_LAYER(_LAYER_)\
	virtual bool init(Ref* pSender = NULL); \
	CREATE_FUNC_SCENE(_LAYER_); \
	CREATE_FUNC_LAYER(_LAYER_);

#define GAME_GOTO_SCENE_FUNC(__LAYER__) \
	void Goto##__LAYER__(Ref* pSender, TouchEventType teType)\
{\
if (teType != TOUCH_EVENT_ENDED)return; \
	Scene* cs = __LAYER__::createScene(pSender); \
	BaseScene::getInstance()->setCurrentScene(cs); \
}

#define SET_BUTTON_FUNC(__BUTTON__,__FUNC__) (__BUTTON__)->addTouchEventListener((Ref*)this, toucheventselector(__FUNC__))

#define SET_BUTTON_FUNC2(__BUTTON__,__FUNC__) (__BUTTON__)->addTouchEventListener(CC_CALLBACK_2(__FUNC__,this))

#define CREATE_PANEL_BY_SIZE_FUNC(_TYPE_) \
static _TYPE_* create(Size size) \
{ \
    _TYPE_* pRet = new _TYPE_(); \
    if(pRet && pRet->init(size)) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    delete pRet; \
    return NULL; \
}

//该宏主要用来快速注册.销毁.发送广播消息
#define POST_ND(nname,ndata) __NotificationCenter::getInstance()->postNotification(nname,ndata)
#define POST_N(nname) __NotificationCenter::getInstance()->postNotification(nname)
#define ADD_OBSERVER(target,selector,nname) __NotificationCenter::getInstance()->addObserver(target,selector,nname,NULL)
#define REMOVE_OBSERVER(target,nname) __NotificationCenter::getInstance()->removeObserver(target,nname)

#endif
