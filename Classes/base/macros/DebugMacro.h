#ifndef TowerCentury_DebugMacro_h
#define TowerCentury_DebugMacro_h

#include "cocos2d.h"
USING_NS_CC;

#define DEBUG_TEST_SERVER_ADDRESS 1 //服务器地址是否是正式地址 0是正式地址 1不是正式地址
#define DEBUG_SEND_DATA_EN 1   //发送到服务器的数据是否加密 0表示不加密 1表示加密
#define DEBUG_STR2JSON 0 //网服务器发送数据包的时字符串转换为json打印信息 0表示不打印 1表示打印
#define DEBUG_NetINFO 1 //网服务器发送数据包的时json打印信息 0表示不打印 1表示打印
#define DEBUG_REMOVE_VIEW 0

#endif