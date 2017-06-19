#pragma once

#include<string>
#include <vector>
#include <algorithm>
#include <set>
#include <stdarg.h>
#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "GameMacro.h"
#include "Defination.h"

using namespace rapidjson;
USING_NS_CC;
USING_NS_CC_EXT;

using namespace std;
using std::string;
using std::vector;
using std::set;

class GameDataUtils
{
public:
	static string  int2String(int value);
	static int string2Int(string value);
    static int pString2Int(__String* value);
/*
按照指定的字符进行切割字符串
 @param str 需要进行切割的字符串
 @param pattern 切割字符串的标记字符
 return vector 按照指定字符切好的字符串数组
*/
    static vector<string> split(string str, string pattern);
/*
替换字符串中所有指定字符串替换成要替换的字符串
 @param strBig 原始字符串
 @param strsrc 需要替换的字符串(注意一旦指定 就是该字符串中所有的该字符都将被替换)
 @param strdst 需要替换成的字符串
 */
    static void stringReplace(string &strBig, string &strsrc, string &strdst);
    
	static void delayCall(float delay, Ref* target, SEL_SCHEDULE fuc);
	static void changeParent(Widget* target, Widget* newParent);
//该模板方法用来从一个vector中寻找一个元素索引位置,不存在返回-1
    template<typename T>static int indexOf(vector<T>& vec, T element, int from = 0)
    {
        typename vector<T>::iterator elemItr = find(vec.begin() + from, vec.end(), element);
        if(elemItr != vec.end())
        {
            return (int)(elemItr - vec.begin());
        }
        return -1;
    }
//该模板方法用来从一个vector中删除一个元素,删除成功返回true
    template<typename T>static bool deleteElemFromVector(vector<T>& vec, T element)
    {
        typename vector<T>::iterator i;
        for(i = vec.begin(); i != vec.end(); i++)
        {
            if((*i) == element)
            {
                vec.erase(i);
                return true;
            }
        }
        return false;
    }
    static string GetStringByKeyInCString(const char* str, string key);
    static int GetIntByKeyInCString(const char* str, string key);
    static cocos2d::Rect getGuideNodeRect(Widget* node,Widget* targetCoordinateSpace);
   
};

