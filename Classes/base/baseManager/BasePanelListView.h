//
// BasePanelListView.h
// kgame
// Created by xiacg on 16/6/20.

#ifndef __kgame__BasePanelListView__
#define __kgame__BasePanelListView__

#include "cocos2d.h"
USING_NS_CC;

#include "BasePanel.h"
#include "GameMacro.h"

typedef void (Ref::*ViewStackChangeHandler)(BasePanel* panel);
#define viewStackChangeHandler_selector(_SELECTOR) (ViewStackChangeHandler)(&_SELECTOR)

class BasePanelListView :public Layout
{
public:
    BasePanelListView();
    ~BasePanelListView();
    CREATE_PANEL_BY_SIZE_FUNC(BasePanelListView);
    static BasePanelListView* create(Widget* source);
    virtual bool init(Size size);
    void addView(BasePanel* panel);
    CC_PROPERTY(BasePanel*, _selectedView, SelectedView);
    CC_PROPERTY(int, _selectedIndex, SelectedIndex);
    void setChangedHandler(Ref* target, ViewStackChangeHandler callback);
protected:
    __Array* viewList;  
private:
    Ref* _changedHandlerTarget;
    ViewStackChangeHandler _changedHandler;
};


#endif /* defined(__kgame__BasePanelListView__) */
