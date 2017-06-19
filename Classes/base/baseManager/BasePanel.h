//
// BasePanel.h
// kgame
//
// Created by xiacg on 16/6/18.

#ifndef __kgame__BasePanel__
#define __kgame__BasePanel__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defination.h"
#include <string>
#include <map>
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;
using namespace cocostudio;

using std::map;
using std::string;

USING_NS_CC;
USING_NS_CC_EXT;

class BasePanel;
class PanelWatcher
{
public:
    static PanelWatcher* getInstance();
    bool hasDataChanged(string dataName);
    void markDataChanged(string dataName);
    void markDataUpdated(string dataName);
    void reset();
private:
    map<string,bool>_dataMap;
};

typedef void (Ref::*PanelHideHandler)(BasePanel* panel);
#define PANEL_WATCHER PanelWatcher::getINstance()
#define panelHideHandler_selector(_SELECTOR)(PanelHideHandler)(&_SELECTOR)

class BasePanelHideHandlerHolder:public Ref
{
public:
    static BasePanelHideHandlerHolder* create(Ref* target, PanelHideHandler callback, int priority)
    {
        BasePanelHideHandlerHolder* result = new (std::nothrow) BasePanelHideHandlerHolder();
        if(!result)return NULL;
        result->autorelease();
        result->hideHandlerTarget = target;
        result->hideHandlerCallback = callback;
        result->priority = priority;
        return result;
    };
    
    void excuteHandler(BasePanel* target)
    {
        if(hideHandlerCallback && hideHandlerTarget)
        {
            (hideHandlerTarget->*hideHandlerCallback)(target);
        }
    };
    
    Ref* hideHandlerTarget;
    PanelHideHandler hideHandlerCallback;
    int priority;
};

class BasePanel :public cocos2d::ui::Widget
{
public:
    BasePanel();
    ~BasePanel();
    
    virtual void initPanel();
    bool isInitialized();
    virtual void onShow(BasePanel* formPanel);
    virtual void onFirstShow(){};
    virtual void beforeHide();
    /*
     这个函数用来控制是否立即显示面板 子类可以重写该方法 用来控制面板是否显示
     如果onBeforeShow() 返回值为true则立即显示面板,false不显示 默认是true
     如果网络交互数据,则不要立即显示 如果程序员想要在显示面板 调用time2Show()即可显示面板
     */
    virtual bool onBeforeShow();
    bool show(cocos2d::ui::Widget* parent);
    void hide();
    void addHideHandler(Ref* target, PanelHideHandler hideHandlerCallback, int priority = 0);
    void removeHideHandler(Ref* target, PanelHideHandler hideHanlderCallback);
    BasePanelHideHandlerHolder* getHideHanlderHolder(Ref* target, PanelHideHandler hideHanlderCallback);
    bool isShowing();
    PanelName getPanelName(){return _panelName;};
protected:
    __Array* hideHandlerList;
    bool _isFirstShow;
    PanelName _panelName;
    virtual void onCloseBtnClicked(Ref* target, cocos2d::ui::Widget::TouchEventType teType);
    virtual bool canShowPanel(){return true;};
    virtual void time2Show();
    virtual void onHttpRequestFail(string api);
private:
    bool _isInitialized;
    bool _isShowing;
};

#endif /* defined(__kgame__BasePanel__) */
