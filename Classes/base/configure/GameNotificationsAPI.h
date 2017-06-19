//
//  GameNotificationsAPI.h
//  kgame
//  Created by xiacg


#ifndef TowerCentury_GameNotificationsAPI_h
#define TowerCentury_GameNotificationsAPI_h

/*该文件主要用来记录发送广播通知的配置文件信息*/
class BasePanel;
/*需要将一个新的弹出面板添加到主界面中发送的通知*/
static const char* SHOW_WINDOW_IN_MAIN_LAYER_N = "showWindowInMainLayerNotification";

struct ShowWindowNotificationData : public Ref
{
    BasePanel* showPanel;
    PanelName belongQueue;
    bool autoClose;//若该标记为true，则在第二次发送弹出窗口通知时会关闭窗口，若该值为false则不会出现这种情况
    static ShowWindowNotificationData* create(BasePanel* showPanel,PanelName belongQueue=PANEL_NAME_NULL,bool autoClose=true)
    {
        ShowWindowNotificationData* result = new (std::nothrow) ShowWindowNotificationData();
        result->autorelease();
        result->showPanel = showPanel;
        result->belongQueue = belongQueue;
        result->autoClose = autoClose;
        return result;
    };
};

#endif
