//
//  kMainScene.hpp
//  kgame
//
//  Created by  xiacg on 2017/6/19.
//
//

#ifndef kMainScene_h
#define kMainScene_h

#include "BaseLayer.h"

class kMianScene:public BaseLayer
{
public:
    kMianScene();
    ~kMianScene();
    GAME_CREATE_COMMON_LAYER(kMianScene);
private:
    void btnCallback(Ref* pSender, Widget::TouchEventType type);
};

#endif /* kMainScene_h */
