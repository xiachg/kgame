//
//  kMainScene.cpp
//  kgame
//
//  Created by  xiacg on 2017/6/19.

#include "kMainScene.h"
#include "GameConfig.h"

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
    
    return true;
}
