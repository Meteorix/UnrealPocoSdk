// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SimpleRpc/rpcserver.h"
#include "SimpleRpc/json.hpp"
#include "UnrealNode.h"
#include "UnrealDumper.h"

using nlohmann::json;


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPocoActor.generated.h"


UCLASS()
class CPPFPS_API AMyTcpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTcpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	RpcServer rpcServer;
	std::thread rpcThread;
	UnrealDumper unrealDumper;
	float serverTickDelta = 0;
	
};
