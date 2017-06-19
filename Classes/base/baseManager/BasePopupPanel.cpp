//
// BasePopupPanel.cpp
// kgame
// Created by xiacg on 16/6/18.

#include "BasePopupPanel.h"
#include "GameDataUtils.h"

static BasePopupPanel* _instance = NULL;

BasePopupPanel::BasePopupPanel():_popupWindows(__Dictionary::create())
{
    _popupWindows->retain();
}

BasePopupPanel::~BasePopupPanel()
{
    CC_SAFE_RELEASE_NULL(_popupWindows);
}

BasePopupPanel* BasePopupPanel::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new (std::nothrow) BasePopupPanel();
    }
    return _instance;
}

void BasePopupPanel::addPopup(BasePanel* panel, cocos2d::ui::Widget* parent, PanelName belongQueue)
{
    if(panel->isShowing())
    {
        CCLOG("BasePopupPanel::addPopup panel is already poped!");
        return;
    }
    if(!parent)
    {
        parent = GET_GAME_MAIN_LAYER->m_mainWidget;
    }
    panel->setLocalZOrder(Game_ZOrder_Popup_Window);
    if(!panel->show(parent))return;
    panel->addHideHandler(this, panelHideHandler_selector(BasePopupPanel::onPopupRemoved),(int)CC_INVALID_INDEX);
    __Array* toQueue;
    if(belongQueue == PANEL_NAME_NULL)
    {
        if(getCurrentQueue() == PANEL_NAME_NULL)
        {
            CCLOG("BasePopupPanel::addPopup to active queue");
            return;
        }
        else
        {
            toQueue = dynamic_cast<__Array*>(_popupWindows->objectForKey(getCurrentQueue()));
        }
    }
    else
    {
        toQueue = dynamic_cast<__Array*>(_popupWindows->objectForKey(belongQueue));
        if(!toQueue)
        {
            toQueue = __Array::create();
            _popupWindows->setObject(toQueue, belongQueue);
        }
        
        if(GameDataUtils::indexOf(_activeQueue, belongQueue) == -1)
        {
            _activeQueue.push_back(belongQueue);
            PanelName conflictQ = getConflictQueue(belongQueue);
            while (conflictQ != PANEL_NAME_NULL)
            {
                removeQueue(conflictQ);
                conflictQ = getConflictQueue(belongQueue);
            }
        }
    }
    toQueue->addObject(panel);
}

void BasePopupPanel::removePopup(BasePanel *panel)
{
    __Array* belongQueue = getPanelBelongQueue(panel);
    if(!belongQueue)
    {
        CCLOG("BasePopupPanel::removePopup panel is not poped");
        return;
    }
    int panelIndex = (int)belongQueue->getIndexOfObject(panel);
    while (panelIndex != belongQueue->count() - 1)
    {
        BasePanel* removingPanel = dynamic_cast<BasePanel*>(belongQueue->getLastObject());
        removingPanel->removeHideHandler(this,panelHideHandler_selector(BasePopupPanel::onPopupRemoved));
        removingPanel->beforeHide();
        belongQueue->removeObject(removingPanel);
        removingPanel->hide();
    }
    int prePanelIndex = panelIndex - 1;
    if(prePanelIndex >= 0)
    {
        dynamic_cast<BasePanel*>(belongQueue->getObjectAtIndex(prePanelIndex))->onShow(panel);
    }
    belongQueue->removeObject(panel);
    panel->hide();
    if(belongQueue->count() == 0)
    {
        GameDataUtils::deleteElemFromVector(_activeQueue, getQueueName(belongQueue));
    }
}

void BasePopupPanel::removeAllPopup()
{
    while (!_activeQueue.empty())
    {
        removeQueue(_activeQueue[_activeQueue.size() - 1]);
    }
}

BasePanel* BasePopupPanel::getShowingPanel(PanelName panelName)
{
    Ref* iter; DictElement* dicElem; BasePanel* elem;
    CCDICT_FOREACH(_popupWindows, dicElem)
    {
        __Array* ary = dynamic_cast<__Array*>(dicElem->getObject());
        CCARRAY_FOREACH(ary,iter)
        {
            elem = dynamic_cast<BasePanel*>(iter);
            if(elem->getPanelName() == panelName)
            {
                return elem;
            }
        }
    }
    return NULL;
}

void BasePopupPanel::removeCurrentQueue()
{
    PanelName crtQueue = getCurrentQueue();
    if(crtQueue != PANEL_NAME_NULL)
    {
        removeQueue(crtQueue);
    }
}

bool BasePopupPanel::hasActiveQueue()
{
    return !_activeQueue.empty();
}

PanelName BasePopupPanel::getCurrentQueue()
{
    return _activeQueue.empty()? PANEL_NAME_NULL : _activeQueue[_activeQueue.size() -1];
}

PanelName BasePopupPanel::getQueueName(__Array *theQueue)
{
    DictElement* dicElem;
    CCDICT_FOREACH(_popupWindows, dicElem)
    {
        if(dicElem->getObject() == theQueue)
        {
            return static_cast<PanelName>(dicElem->getIntKey());
        }
    }
    return PANEL_NAME_NULL;
}

void BasePopupPanel::removeQueue(PanelName queueName)
{
    __Array* theQueue = NULL;
    for(vector<PanelName>::iterator i = _activeQueue.begin(); i != _activeQueue.end(); i++)
    {
        if((*i) == queueName)
        {
            theQueue = dynamic_cast<__Array*>(_popupWindows->objectForKey(queueName));
        }
    }
    if(theQueue)
    {
        dynamic_cast<BasePanel*>(theQueue->getObjectAtIndex(0))->beforeHide();
    }
}

void BasePopupPanel::onPopupRemoved(BasePanel *target)
{
    removePopup(target);
}

__Array* BasePopupPanel::getPanelBelongQueue(BasePanel *target)
{
    DictElement* dicElem;
    CCDICT_FOREACH(_popupWindows, dicElem)
    {
        __Array* ary = dynamic_cast<__Array*>(dicElem->getObject());
        if(ary->containsObject(target))
        {
            return ary;
        }
    }
    return NULL;
}

PanelName BasePopupPanel::getConflictQueue(PanelName panelName)
{
    if(!conflictQueue.empty() && GameDataUtils::indexOf(conflictQueue,panelName) != -1)
    {
        for(vector<PanelName>::iterator i = _activeQueue.begin(); i != _activeQueue.end(); i++)
        {
            PanelName n = *i;
            if(n != panelName && GameDataUtils::indexOf(conflictQueue,n) != -1)
            {
                return n;
            }
        }
    }
    return PANEL_NAME_NULL;
}
