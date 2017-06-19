
//
// BasePanelListView.cpp
// kgame
// Created by xiacg on 16/6/20.

#include "BasePanelListView.h"

BasePanelListView::BasePanelListView():
viewList(__Array::create()),
_selectedIndex((int)CC_INVALID_INDEX),
_selectedView(NULL),
_changedHandlerTarget(NULL), _changedHandler(NULL)
{
    CC_SAFE_RETAIN(viewList);
}

BasePanelListView::~BasePanelListView()
{
    CC_SAFE_RELEASE_NULL(viewList);
}

bool BasePanelListView::init(Size size)
{
    if(!Layout::init())return false;
    setContentSize(size);
    return true;
}

BasePanelListView* BasePanelListView::create(Widget* source)
{
    CCASSERT(source, "BasePanelListView::create source can't be NULL");
    BasePanelListView* result = new BasePanelListView();
    if(result ->init(source->getContentSize()))
    {
        result->setPosition(source->getPosition());
        result->setLocalZOrder(source->getLocalZOrder());
        source->getParent()->addChild(result);
        source->removeFromParent();
        result->autorelease();
        return result;
    }
    delete result;
    return NULL;
}

void BasePanelListView::addView(BasePanel* panel)
{
    viewList->addObject(panel);
}

BasePanel* BasePanelListView::getSelectedView()
{
    return _selectedView;
}

void BasePanelListView::setSelectedView(BasePanel* panel)
{
    if(_selectedView == panel)return;
    if(_selectedView)
    {
        _selectedView->beforeHide();
        _selectedView->hide();
    }
    _selectedView = panel;
    if(_selectedView)
    {
        _selectedView->show(this);
        _selectedIndex = (int)(viewList->getIndexOfObject(_selectedView));
    }
    else
    {
        _selectedIndex = -1;
    }
    if(_changedHandler && _changedHandlerTarget)
    {
        (_changedHandlerTarget->*_changedHandler)(_selectedView);
    }
}

int BasePanelListView::getSelectedIndex()
{
    return _selectedIndex;
}

void BasePanelListView::setSelectedIndex(int var)
{
    if(var < 0 || var >= viewList->count())
    {
        setSelectedView(NULL);
    }
    else
    {
        setSelectedView(dynamic_cast<BasePanel*>(viewList->getObjectAtIndex(var)));
    }
}

void BasePanelListView::setChangedHandler(Ref* target, ViewStackChangeHandler callback)
{
    _changedHandlerTarget = target;
    _changedHandler = callback;
}
