#include "AbstractDumper.h"


AbstractDumper::AbstractDumper()
{
}


AbstractDumper::~AbstractDumper()
{
}

AbstractNode* AbstractDumper::getRoot()
{
	AbstractNode *rootNode = new AbstractNode();
	return rootNode;
}

json AbstractDumper::dumpHierarchy(json params)
{
	bool onlyVisibleNode = true;
	if (params.size() > 0) {
		onlyVisibleNode = params[0];
	}
	AbstractNode* rootNode = getRoot();
	json dump = dumpHierarchyImpl(rootNode, onlyVisibleNode);
	delete rootNode;
	return dump;
}

json AbstractDumper::dumpHierarchyImpl(AbstractNode *node, bool onlyVisibleNode)
{
	json result;
	json payload = node->enumerateAttrs();
	json children = {};
	string name = node->getAttr(string("name"));

	result["name"] = name;
	result["payload"] = payload;

	for (AbstractNode child : node->getChildren()) {
		if (!onlyVisibleNode || child.getAttr(string("visible"))) {
			children.push_back(dumpHierarchyImpl(&child, onlyVisibleNode));
		}
	}

	if (children.size() > 0) {
		result["children"] = children;
	}
	return result;
}
