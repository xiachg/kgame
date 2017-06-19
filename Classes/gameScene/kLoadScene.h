//
//  kLoadScene.h
//  kgame
//  Created by  xiacg on 2017/6/19.

#ifndef kLoadScene_h
#define kLoadScene_h

#include "BaseLayer.h"
#include "GameConfig.h"

class kLoadScene:public BaseLayer
{
public:
    kLoadScene();
    ~kLoadScene();
    GAME_CREATE_COMMON_LAYER(kLoadScene);
private:
    void btnCallback(Ref* pSender,Widget::TouchEventType type);
};

#endif /* kLoadScene_h */
