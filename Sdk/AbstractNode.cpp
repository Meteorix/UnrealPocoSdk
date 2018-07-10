#include "AbstractNode.h"



AbstractNode::AbstractNode()
{
}


AbstractNode::~AbstractNode()
{
}

std::vector<AbstractNode> AbstractNode::getChildren()
{
	UE_LOG(LogTemp, Warning, TEXT("AN:getChildren"))
	return std::vector<AbstractNode>();
}

json AbstractNode::getAttr(std::string attrName)
{
	json attrValue = nullptr;
	if (defaultAttrs.find(attrName) != defaultAttrs.end()) {
		attrValue = defaultAttrs[attrName];
	} 
	return attrValue;
}

json AbstractNode::enumerateAttrs()
{
	json ret;
	for (json::iterator it = defaultAttrs.begin(); it != defaultAttrs.end(); it++) {
		ret[it.key()] = getAttr(it.key());
	}
	return defaultAttrs;
}
