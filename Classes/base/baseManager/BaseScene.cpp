//
//  KE3SceneManager.cpp
//  kgame
//  Created by xiacg on 16/6/17.

#include "BaseScene.h"

BaseScene::BaseScene():m_currentScene(NULL)
{
    
}

BaseScene::~BaseScene()
{
    CC_SAFE_RELEASE_NULL(m_currentScene);
}

static BaseScene* instanceTCSM = NULL;

BaseScene* BaseScene::getInstance()
{
    if (instanceTCSM == NULL)
    {
        instanceTCSM = new BaseScene();
    }
    return instanceTCSM;
}

void BaseScene::setCurrentScene(Scene* cs, SCENE_SET_MODE mode)
{
    if (mode == RUN_SCENE)
    {
        Director::getInstance()->runWithScene(cs);
        m_SceneStack.pushBack(cs);
    }
    else
    {
        int index = indexOf(static_cast<SceneTag>(cs->getTag()));
        if (index != -1)
        {
//            popToScene(static_cast<SceneTag>(cs->getTag()));
//            return;
        }
        if (mode == PUSH_SCENE)
        {
            Director::getInstance()->pushScene(cs);
            m_SceneStack.pushBack(cs);
        }
        else if (mode == REPLACE_SCENE)
        {
            Director::getInstance()->replaceScene(cs);
            m_SceneStack.popBack();
            m_SceneStack.pushBack(cs);
        }
    }
    GAME_SAFE_ASSIGN(m_currentScene, cs);
}

Scene* BaseScene::getCurrentScene()
{
    return m_currentScene;
}

BaseLayer* BaseScene::getCurrentLayer()
{
    return dynamic_cast<BaseLayer*>(m_currentScene->getChildren().back());
}

void BaseScene::popScene()
{
    m_SceneStack.popBack();
    Scene* nextScene = dynamic_cast<Scene*>(m_SceneStack.back());
    dynamic_cast<BaseLayer*>(nextScene->getChildren().back())->fromScene = static_cast<SceneTag>(m_currentScene->getTag());
    GAME_SAFE_ASSIGN(m_currentScene, nextScene);
    Director::getInstance()->popScene();
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

void BaseScene::popToScene(SceneTag tag)
{
    int index = indexOf(tag);
    if (index != -1)
    {
        int time = (int)m_SceneStack.size() - 1 - index;
        for (int i = 0; i < time; i++)
        {
            m_SceneStack.popBack();
        }
        Scene* nextScene = dynamic_cast<Scene*>(m_SceneStack.back());
        dynamic_cast<BaseLayer*>(nextScene->getChildren().back())->fromScene = tag;
        GAME_SAFE_ASSIGN(m_currentScene, nextScene);
        Director::getInstance()->popToSceneStackLevel(index + 1);
        Director::getInstance()->getTextureCache()->removeUnusedTextures();
    }
    else
    {
        CCLOG("BaseScene::popScene can't pop to specified scene");
    }
}

int BaseScene::indexOf(SceneTag tag)
{
    int index = -1;
    for (auto obj : m_SceneStack)
    {
        if (obj->getTag() == tag)
        {
            index = (int)m_SceneStack.getIndex(obj);
            break;
        }
    }
    return index;
}

void BaseScene::setSceneTouchEnabled(bool val)
{
   
}

void BaseScene::trace(const char* msg)
{
//    if(!_globalTracePanel)
//    {
//        _globalTracePanel = TracePanel::create(Size(1036,640));
//        _globalTracePanel->retain();
//        _globalTracePanel->setGlobalZOrder(Game_ZOrder_TracePanel);
//        _globalTracePanel->setPosition(Vec2(0,0));
//    }
//    _globalTracePanel->log(msg);
}

void BaseScene::showTracePanel()
{
//    if(!_globalTracePanel->getParent())
//    {
//        GET_GAME_MAIN_LAYER->addElementToWidget(_globalTracePanel);
//    }
}
