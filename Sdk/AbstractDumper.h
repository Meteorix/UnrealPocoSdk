#pragma once
#include "AbstractNode.h"


class AbstractDumper
{
public:
	AbstractDumper();
	~AbstractDumper();

	virtual AbstractNode getRoot();
	virtual json dumpHierarchy(json params);

protected:
	virtual json dumpHierarchyImpl(AbstractNode node, bool onlyVisibleNode);
};

