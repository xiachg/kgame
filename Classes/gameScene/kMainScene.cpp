//
//  kMainScene.cpp
//  kgame
//
//  Created by  xiacg on 2017/6/19.

#include "kMainScene.h"
#include "GameConfig.h"
#include "BaseScene.h"
#include "kBattleScene.h"

kMianScene::kMianScene()
{

}

kMianScene::~kMianScene()
{

}

bool kMianScene::init(Ref* pSender)
{
    if(!BaseLayer::init(pSender)) return false;
    
    auto mainPanel = CSLoader::createNode(GameConfig::kMainScene_Csb);
    m_mainWidget->addChild(mainPanel);
    
    SET_BUTTON_FUNC2(dynamic_cast<Button*>(mainPanel->getChildByName("root")->getChildByName("bg1")->getChildByName("battleIcon")),kMianScene::btnCallback);
    
    return true;
}

void kMianScene::btnCallback(Ref* pSender, Widget::TouchEventType type)
{
    if(type != Widget::TouchEventType::ENDED) return;
    BaseScene::getInstance()->setCurrentScene(kBattleScene::createScene(),REPLACE_SCENE);
}
