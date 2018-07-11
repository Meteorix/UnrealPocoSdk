#pragma once
#include "Sdk/AbstractDumper.h"
#include "UnrealNode.h"


class UnrealDumper: public AbstractDumper
{
public:
	UnrealDumper();
	~UnrealDumper();
	AbstractNode* getRoot();

	AActor *m_actor;

};
