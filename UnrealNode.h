#pragma once
#include "Sdk/AbstractNode.h"
#include "GameFramework/Actor.h"


class UnrealNode: public AbstractNode
{
public:
	UnrealNode();
	~UnrealNode();
	std::vector<AbstractNode> getChildren() override;
};


class RootNode : public UnrealNode
{
public:
	RootNode();
	std::vector<AbstractNode> getChildren() override;

	AActor *m_actor = nullptr;
private:
	std::vector<UnrealNode> chilren = {};
};