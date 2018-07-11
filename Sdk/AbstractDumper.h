#pragma once
#include "AbstractNode.h"


class AbstractDumper
{
public:
	AbstractDumper();
	~AbstractDumper();

	virtual AbstractNode* getRoot();
	json dumpHierarchy(json params);

protected:
	json dumpHierarchyImpl(AbstractNode *node, bool onlyVisibleNode);
};
