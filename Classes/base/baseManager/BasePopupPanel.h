//
// BasePopupPanel.h
// kgame
//
// Created by xiacg on 16/6/18.

#ifndef __kgame__BasePopupPanel__
#define __kgame__BasePopupPanel__

#include "BasePanel.h"
#include "BaseScene.h"
#include "GameMacro.h"
#include "GameNotificationsAPI.h"
#include <vector>
#include <map>
using std::vector;
using std::map;
/*
 class PopManager introduce：弹出窗口管理器
 */
class BasePopupPanel : public Ref
{
public:
    BasePopupPanel();
    ~BasePopupPanel();
    static BasePopupPanel* getInstance();
    /*
     弹出一个窗口到当前场景
     @param panel: 要弹出的窗口的实例
     @param parent: 弹出窗口添加到的父容器 默认值为NULL
     @param belongQueue: 弹出窗口所从属的窗口的队列,若为NULL,则默认添加到当前活跃队列中
     */
    void addPopup(BasePanel* panel, cocos2d::ui::Widget* parent = NULL, PanelName belongQueue = PANEL_NAME_NULL);
    void removePopup(BasePanel* panel);
    void removeAllPopup();
    BasePanel* getShowingPanel(PanelName panelName);
    vector<PanelName>conflictQueue;
    void removeCurrentQueue();
    bool hasActiveQueue();
private:
    __Dictionary* _popupWindows;
    vector<PanelName>_activeQueue;
    PanelName getCurrentQueue();
    PanelName getQueueName(__Array* theQueue);
    void removeQueue(PanelName queueName);
    void onPopupRemoved(BasePanel* target);
    __Array* getPanelBelongQueue(BasePanel* target);
    PanelName getConflictQueue(PanelName panelName);
};

#define POPUP_MANAGER (BasePopupPanel::getInstance())

//此宏用以快速生成一个按钮点击侦听函数，该函数中实现了将面板添加到主界面上当前活动队列中的功能
#define CLICK_TO_SHOW_PANEL(panel,panelName,queueName) \
void clickToShowPanel##panel(cocos2d::Ref* pSender,Widget::TouchEventType teType) \
{ \
if(teType != Widget::TouchEventType::ENDED)return; \
BasePanel* p = POPUP_MANAGER->getShowingPanel(panelName); \
if(p) \
{ \
p->beforeHide(); \
} \
else \
{ \
POST_ND(SHOW_WINDOW_IN_MAIN_LAYER_N,ShowWindowNotificationData::create(panel::create(),queueName)); \
} \
}

//此宏用以快速生成一个按钮点击侦听函数，该函数中实现了点击按钮后弹出一个面板到当前活跃队列中的功能，该面板会覆盖整个屏幕
#define CLICK_TO_POP_UP_PANEL(panel,panelName,queueName) \
void clickToPopUpPanel##panel(cocos2d::Ref* pSender,Widget::TouchEventType teType) \
{ \
if(teType != Widget::TouchEventType::ENDED)return; \
BasePanel* p = POPUP_MANAGER->getShowingPanel(panelName); \
if(p) \
{ \
p->beforeHide(); \
} \
else \
{ \
POST_ND(SHOW_WINDOW_IN_MAP_LAYER_N,ShowWindowNotificationData::create(panel::create(),queueName)); \
} \
}


#endif /* defined(__KingdomExpedition3__BasePopupPanel__) */
