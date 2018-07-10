#pragma once
#include "iostream"
#include <vector>
#include <map>
#include <string>
#include "../SimpleRpc/json.hpp"


using json = nlohmann::json;
using std::string;


class AbstractNode
{
public:
	AbstractNode();
	~AbstractNode();

	virtual std::vector<AbstractNode> getChildren();
	virtual json getAttr(std::string attrName);
	virtual json enumerateAttrs();
protected:
	json defaultAttrs = {
		{ "name", "<Root>" },
		{ "type", "Root" },
		{ "visible", true },
		{ "pos",{ 0.0f, 0.0f } },
		{ "size",{ 0.0f, 0.0f } },
		{ "scale",{ 1.0f, 1.0f } },
		{ "anchorPoint",{ 0.5f, 0.5f } },
		{ "zOrders",{ { "local", 0 },{ "global", 0 } } }
	};
};
