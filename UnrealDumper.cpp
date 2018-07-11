#include "UnrealDumper.h"


UnrealDumper::UnrealDumper()
{
}


UnrealDumper::~UnrealDumper()
{
}


AbstractNode* UnrealDumper::getRoot()
{
	RootNode *rootNode = new RootNode();
	UE_LOG(LogTemp, Warning, TEXT("============UD getRoot==========="));
	rootNode->m_actor = m_actor;
	return rootNode;
}
