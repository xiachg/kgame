#pragma once

#include "cocos2d.h"

USING_NS_CC;

static const int ALERT_YES = 1 << 0;
static const int ALERT_NO = 1 << 1;
static const int ALERT_CANCEL = 1 << 2;

enum GameZOrder
{
	Game_ZOrder_Popup_Window = 10000,
	Game_ZOrder_Notification,
	Game_ZOrder_Global_Mask,
	Game_ZOrder_LoadingBar,
    Game_ZOrder_TracePanel
};

enum SceneTag
{
	SCENE_TestLayer,
	SCENE_NULL = 200,
    SCENE_kLoadScene,
    SCENE_kMianScene,
    SCENE_kBattleScene
};

enum PanelName
{
    PANEL_NAME_TestPanel,
    PANEL_NAME_NULL
};



