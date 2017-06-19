#pragma once
#include <string>
using std::string;

class GameConfig
{
public:
/*－－－－－－－－－－游戏中的字体设置，在此处统一配置－－－－－－－－*/
    
	static const float GAME_FPS;//游戏的FPS
	static const char SYSTEM_FONT_NAME[];
	static const char SYSTEM_IOS_FONT_NAME[];
	static const char SYSTEM_ANDROID_FONT_NAME[];
	static const char SYSTEM_WIN32_FONT_NAME[];
    
/*－－－－－－－－－－游戏中的字体大小设置，在此处统一配置－－－－－－－－－－*/
    
	static const float FONT_SIZE_BUTTON_TITLE;
	static const float FONT_SIZE_TITLE;
    
/*－－－－－－－－－－游戏中需要用到的提示错误和提示的文本,在此处统一配置－－－－－－－－－－－－－－－－－－－*/
   
    
/*－－－－－－－－－－游戏中的csb文件的路径配置－－－－－－－－－－－－－－－－－－－－－*/
    static const char* kLoadScene_Csb;
    static const char* kMainScene_Csb;
};

