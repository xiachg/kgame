//
// BasePanel.cpp
// kgame
// Created by xiacg on 16/6/18.

#include "BasePanel.h"
#include <algorithm>

/*---------------------------------------privateFunction---------------------------------------*/

bool sortByPriority(Ref* obj1, Ref* obj2)
{
    BasePanelHideHandlerHolder* a = dynamic_cast<BasePanelHideHandlerHolder*>(obj1);
    BasePanelHideHandlerHolder* b = dynamic_cast<BasePanelHideHandlerHolder*>(obj2);
    return a->priority > b->priority;
}

/*---------------------------------------panelWatcher---------------------------------------*/
static PanelWatcher* _instance = NULL;

PanelWatcher* PanelWatcher::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new PanelWatcher();
        return _instance;
    }
    return _instance;
}

bool PanelWatcher::hasDataChanged(string dataName)
{
    if(_dataMap.count(dataName) == 0)
    {
        return false;
    }
    return _dataMap[dataName];
}

void PanelWatcher::markDataChanged(string dataName)
{
    _dataMap[dataName] = true;
}

void PanelWatcher::markDataUpdated(string dataName)
{
    _dataMap[dataName] = false;
}

void PanelWatcher::reset()
{
    _dataMap.clear();
}

/*---------------------------------------------------------TCPanel-------------------------------------------*/

BasePanel::BasePanel():
hideHandlerList(__Array::create()),
_isInitialized(false),
_isFirstShow(true),
_isShowing(false)
{
    CC_SAFE_RETAIN(hideHandlerList);
}

BasePanel::~BasePanel()
{
    CC_SAFE_RELEASE_NULL(hideHandlerList);
}

void BasePanel::initPanel()
{
    _isInitialized = true;
}

bool BasePanel::isInitialized()
{
    return _isInitialized;
}

void BasePanel::onShow(BasePanel* formPanel)
{
    if(_isFirstShow)
    {
        _isFirstShow = false;
        onFirstShow();
    }
}

void BasePanel::beforeHide()
{
    this->retain();
    Ref* iter;
    CCARRAY_FOREACH(hideHandlerList, iter)
    {
        dynamic_cast<BasePanelHideHandlerHolder*>(iter)->excuteHandler(this);
    }
    hideHandlerList->removeAllObjects();
    this->release();
}

bool BasePanel::onBeforeShow()
{
    return true;
}

bool BasePanel::show(cocos2d::ui::Widget* parent)
{
    if(!canShowPanel()) return false;
    
    if(_isShowing)
    {
        CCLOG("BasePanel is already showing");
        return false;
    }
    _isShowing = true;
    if(!isInitialized())
    {
        initPanel();
    }
    parent->addChild(this);
    if(onBeforeShow())
    {
        time2Show();
    }
    else
    {
        setVisible(false);
    }
    return true;
}

void BasePanel::hide()
{
    if(!_isShowing)
    {
        CCLOG("BasePanel is already hide");
        return;
    }
   _isShowing = false;
   removeFromParent();
}

void BasePanel::addHideHandler(Ref* target, PanelHideHandler hideHandlerCallback, int priority)
{
    if(getHideHanlderHolder(target, hideHandlerCallback))return;
    hideHandlerList->addObject(BasePanelHideHandlerHolder::create(target, hideHandlerCallback, priority));
    std::sort(hideHandlerList->data->arr, hideHandlerList->data->arr + hideHandlerList->data->num,sortByPriority);
}

void BasePanel::removeHideHandler(Ref* target, PanelHideHandler hideHanlderCallback)
{
    BasePanelHideHandlerHolder* holder = getHideHanlderHolder(target, hideHanlderCallback);
    if(holder)
    {
        hideHandlerList->removeObject(holder);
    }
}

BasePanelHideHandlerHolder* BasePanel::getHideHanlderHolder(Ref* target, PanelHideHandler hideHanlderCallback)
{
    Ref* iter;
    CCARRAY_FOREACH(hideHandlerList, iter)
    {
        BasePanelHideHandlerHolder* elem = dynamic_cast<BasePanelHideHandlerHolder*>(iter);
        if(elem->hideHandlerTarget == target && elem->hideHandlerCallback == hideHanlderCallback)return elem;
    }
    return NULL;
}

bool BasePanel::isShowing()
{
    return _isShowing;
}

/*------------------------------------------------private functions------------------------------------------------*/

void BasePanel::onCloseBtnClicked(Ref* target, cocos2d::ui::Widget::TouchEventType teType)
{
    if(teType != TouchEventType::ENDED)return;
    beforeHide();
}

void BasePanel::time2Show()
{
    setVisible(true);
//  Action* popupLayer = Sequence::create(ScaleTo::create(0.0, 0.0),ScaleTo::create(0.06, 1.05),ScaleTo::create(0.08, 0.95),ScaleTo::create(0.08, 1.0), NULL);
//  this->runAction(popupLayer);
    onShow(NULL);
}

void BasePanel::onHttpRequestFail(string api)
{
    beforeHide();
}
