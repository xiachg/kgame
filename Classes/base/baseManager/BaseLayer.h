
#ifndef __kgame__BaseLayer__
#define __kgame__BaseLayer__

#include"cocos2d.h"
#include"cocos-ext.h"
#include "Defination.h"
#include "GameMacro.h"

USING_NS_CC;
USING_NS_CC_EXT;

class BaseLayer : public Layer
{
public:
    BaseLayer();
    ~BaseLayer();
        
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onFirstEnter();//该函数 用来加载新手引导引擎 需要引导的场景中 需要重写该函数 来实现新手引导的完成
    virtual void onFirstEnterTransitionDidFinish();
    virtual void onExit();
    
    virtual bool init(Ref* pSender = NULL);
    
    virtual bool onTouchBegan(Touch* touch, Event* m_event);
    virtual void onTouchEnded(Touch* touch, Event* m_event);
    
    SceneTag fromScene;
    bool m_canGoBack;
    
    Widget* GetMainWidget(){ return m_mainWidget;}
    void addElementToWidget(Widget* element);
    Layout* m_mainWidget;
    
protected:
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
protected:
    bool isFirstEnter;
    bool isFirstShow;
    void update(float dt);
    EventListenerKeyboard* listener;

};

#endif /* defined(__kgame__BaseLayer__) */
