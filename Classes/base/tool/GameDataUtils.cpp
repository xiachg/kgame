#include "GameDataUtils.h"
#include <array>
#include "DebugMacro.h"

string  GameDataUtils::int2String(int value)
{
	auto temp = __String::createWithFormat("%d", value);
	return string(temp->getCString());
}

int GameDataUtils::string2Int(string value)
{
	return atoi(value.c_str());
}

int GameDataUtils::pString2Int(__String* value)
{
    auto temp = string(value->getCString());
    return atoi(temp.c_str());
}

vector<string> GameDataUtils::split(string str, string pattern)
{
    string::size_type pos;
    vector<string> result;
    if(!str.empty())
    {
        str += pattern;
        string::size_type size = str.size();
        for(string::size_type i = 0; i < size; i++)
        {
            pos = str.find(pattern,i);
            if(pos < size)
            {
                string s = str.substr(i, pos - i);
                result.push_back(s);
                i = pos + pattern.size() -1;
            }
        }
    }
    return result;
}

void GameDataUtils::stringReplace(string &strBig, string &strsrc, string &strdst)
{
    string::size_type pos = 0;
    string::size_type srclen = strsrc.size();
    string::size_type dstlen = strdst.size();
    while ((pos = strBig.find(strsrc,pos)) != string::npos)
    {
        strBig.replace(pos, srclen,strdst);
        pos += dstlen;
    }
}

void GameDataUtils::delayCall(float delay, Ref* target, SEL_SCHEDULE fuc)
{
	Director::getInstance()->getScheduler()->schedule(fuc, target, 0.0f, 0, delay, false);
}

void GameDataUtils::changeParent(Widget* target, Widget* newParent)
{
	target->retain();
	target->removeFromParent();
	newParent->addChild(target);
	target->release();
}

string GameDataUtils::GetStringByKeyInCString(const char* str, string key)
{
    int now = 0;
    string res = "";
    while(str[now])
    {
        string k = "";
        for(; str[now] && str[now] != '=' && str[now] != '&'; now++)k += str[now];
        
        if(k == key)
        {
            res = "";
            for(now++;str[now] && str[now] != '&'; now++)
            {
                res += str[now];
            }
            return res;
        }
        
        for(;str[now] && str[now] != '&'; now++);
        if(!str[now])break;
        now++;
    }
    return res;
}

int GameDataUtils::GetIntByKeyInCString(const char* str, string key)
{
    return atoi(GetStringByKeyInCString(str, key).c_str());
}

Rect GameDataUtils::getGuideNodeRect(Widget* node,Widget* targetCoordinateSpace)
{
    Point nodePos = node->getPosition();
    Size nodeSize = node->getContentSize();
    Point nodeAp = node->getAnchorPoint();
    nodePos.x = nodePos.x - nodeAp.x * nodeSize.width;
    nodePos.y = nodePos.y - nodeAp.y * nodeSize.height;
    Widget* parent = dynamic_cast<Widget*>(node->getParent());
    Point worldPos = parent ? parent->convertToWorldSpace(nodePos) : nodePos;
    Rect worldRect(worldPos.x,worldPos.y,nodeSize.width,nodeSize.height);
    if(targetCoordinateSpace)
    {
        Point localPos = targetCoordinateSpace->getVirtualRenderer()->convertToNodeSpace(worldPos);
        AffineTransform localTransform = targetCoordinateSpace->getVirtualRenderer()->getNodeToParentAffineTransform();
        Size localSize(nodeSize.width * localTransform.a, nodeSize.height * localTransform.d);
        return Rect(localPos.x,localPos.y,localSize.width,localSize.height);
    }
    return worldRect;
}



