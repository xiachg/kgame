//
//  kLoadScene.cpp
//  kgame
//  Created by  xiacg on 2017/6/19.

#include "kLoadScene.h"
#include "kMainScene.h"
#include "BaseScene.h"

kLoadScene::kLoadScene()
{

}

kLoadScene::~kLoadScene()
{
    
}

bool kLoadScene::init(Ref* pSender)
{
    if(!BaseLayer::init(pSender)) return false;
    
    auto loadPanel = CSLoader::createNode(GameConfig::kLoadScene_Csb);
    m_mainWidget->addChild(loadPanel);
    
    SET_BUTTON_FUNC2(dynamic_cast<Button*>(loadPanel->getChildByName("root")->getChildByName("startGameBtn")),kLoadScene::btnCallback);
    
    return true;
}

void kLoadScene::btnCallback(Ref* pSender,Widget::TouchEventType type)
{
    if(type != Widget::TouchEventType::ENDED) return;
    BaseScene::getInstance()->setCurrentScene(kMianScene::createScene(),REPLACE_SCENE);
}
