//
//  kBattleScene.hpp
//  kgame
//
//  Created by  xiacg on 2017/6/22.
//
//

#ifndef kBattleScene_h
#define kBattleScene_h

#include "BaseLayer.h"

class kBattleScene:public BaseLayer
{
public:
    kBattleScene();
    ~kBattleScene();
public:
    GAME_CREATE_COMMON_LAYER(kBattleScene);
    
};

#endif /* kBattleScene_hpp */
