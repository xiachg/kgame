//
//  kBattleScene.cpp
//  kgame
//  Created by  xiacg on 2017/6/22.

#include "kBattleScene.h"
#include "GameConfig.h"

kBattleScene::kBattleScene()
{

}

kBattleScene::~kBattleScene()
{

}

bool kBattleScene::init(cocos2d::Ref *pSender)
{
    if(!BaseLayer::init(pSender)) return false;
    
    auto battleScene = CSLoader::createNode(GameConfig::kBattleScene_Csb);
    m_mainWidget->addChild(battleScene);
    
    return true;
}
