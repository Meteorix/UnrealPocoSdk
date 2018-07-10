#include "UnrealDumper.h"


UnrealDumper::UnrealDumper()
{
}


UnrealDumper::~UnrealDumper()
{
}


AbstractNode UnrealDumper::getRoot()
{
	RootNode rootNode = RootNode();
	UE_LOG(LogTemp, Warning, TEXT("============UD getRoot==========="));
	rootNode.m_actor = m_actor;
	return rootNode;
}


json UnrealDumper::dumpHierarchy(json params)
{
	bool onlyVisibleNode = true;
	if (params.size() > 0) {
		onlyVisibleNode = params[0];
	}
	AbstractNode rootNode = getRoot();
	return dumpHierarchyImpl(rootNode, onlyVisibleNode);
}