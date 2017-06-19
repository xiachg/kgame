//
//  BaseScene.h
//  kgame
//  Created by xiacg on 16/6/17.

#ifndef BaseScene_h
#define BaseScene_h

#include "BaseLayer.h"

enum SCENE_SET_MODE
{
    PUSH_SCENE,
    REPLACE_SCENE,
    RUN_SCENE
};

class BaseScene : public Ref
{
public:
    BaseScene();
    ~BaseScene();
    static BaseScene* getInstance();
    void popScene();
    void setCurrentScene(Scene* cs, SCENE_SET_MODE mode = PUSH_SCENE);
    void popToScene(SceneTag tag);
    Scene* getCurrentScene();
    BaseLayer* getCurrentLayer();
    int indexOf(SceneTag tag);
    void setSceneTouchEnabled(bool val);
    void trace(const char* msg);
    void showTracePanel();
protected:
    Vector<Scene*>m_SceneStack;
    Scene* m_currentScene;
};

#endif /* BaseScene */
