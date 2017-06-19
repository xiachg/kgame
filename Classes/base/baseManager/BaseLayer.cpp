//
// BaseLayer.cpp
// kgame
// Created by xiacg on 16/6/18.

#include "BaseLayer.h"
BaseLayer::BaseLayer():
isFirstEnter(true),
isFirstShow(true)
{
    
}

void BaseLayer::onFirstEnter()
{
    
}

void BaseLayer::onEnter()
{
    Layer::onEnter();
    _touchEnabled = true;
    if (isFirstEnter)
    {
        onFirstEnter();
    }
}

void BaseLayer::onFirstEnterTransitionDidFinish()
{
    
}

void BaseLayer::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    if (isFirstEnter)
    {
        onFirstEnterTransitionDidFinish();
    }
    isFirstEnter = false;
}

void BaseLayer::onExit()
{
    Layer::onExit();
    _touchEnabled = false;
    _eventDispatcher->removeEventListener(listener);
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

BaseLayer::~BaseLayer()
{
    _eventDispatcher->removeEventListener(listener);
}

bool BaseLayer::onTouchBegan(Touch* touch, Event* m_event)
{
    return Layer::onTouchBegan(touch,m_event);
}

void BaseLayer::onTouchEnded(Touch* touch, Event* m_event)
{
    return Layer::onTouchEnded(touch, m_event);
}

bool BaseLayer::init(Ref* pSender)
{
    if (!Layer::init())return false;
    this->scheduleUpdate();
    m_canGoBack = true;
    _touchMode = Touch::DispatchMode::ONE_BY_ONE;
    listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(BaseLayer::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    m_mainWidget = Layout::create();
    m_mainWidget->setContentSize(Size(1136,640));
    m_mainWidget->setAnchorPoint(Vec2(0, 0));
    m_mainWidget->setPosition(Vec2(0, 0));
    m_mainWidget->setGlobalZOrder(30);
    addChild(m_mainWidget);
    return true;
}

void BaseLayer::addElementToWidget(Widget* element)
{
    m_mainWidget->addChild(element);
}

void BaseLayer::update(float dt)
{
    Layer::update(dt);
}

void BaseLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch(keyCode)
    {
        case EventKeyboard::KeyCode::KEY_ESCAPE:
        break;
        case EventKeyboard::KeyCode::KEY_MENU:
        break;
    }
}
