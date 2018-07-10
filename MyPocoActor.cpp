// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPocoActor.h"


// Sets default values
AMyTcpActor::AMyTcpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyTcpActor::BeginPlay()
{
	Super::BeginPlay();

	unrealDumper.m_actor = this;

	// register rpc methods
	using namespace std::placeholders;
	std::function<json(json)> Dump = std::bind(&UnrealDumper::dumpHierarchy, unrealDumper, _1);
	rpcServer.register_rpc_method("Dump", Dump);

	rpcThread = std::thread(&RpcServer::start, rpcServer);
	UE_LOG(LogTemp, Warning, TEXT("============RpcServer Start==========="));
}

void AMyTcpActor::BeginDestroy()
{
	rpcThread.detach();
	rpcServer.close();
	Super::BeginDestroy();
}

// Called every frame
void AMyTcpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	serverTickDelta += DeltaTime;
	if (serverTickDelta > 1)
	{
		serverTickDelta = 0;
	}
}
