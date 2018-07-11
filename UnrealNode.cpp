#include "UnrealNode.h"
#include "EngineUtils.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectIterator.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


UnrealNode::UnrealNode()
{
}


UnrealNode::~UnrealNode()
{
}

std::vector<AbstractNode> UnrealNode::getChildren()
{
	UE_LOG(LogTemp, Warning, TEXT("UN:getChildren"))
	return std::vector<AbstractNode>();
}



// Root Node 

RootNode::RootNode()
{
}

std::vector<AbstractNode> RootNode::getChildren()
{
	const APlayerController* const PlayerController = UGameplayStatics::GetPlayerController(m_actor->GetWorld(), 0);
	UE_LOG(LogTemp, Warning, TEXT("RN:getChildren"));

	//for (TActorIterator<AStaticMeshActor> ActorItr(m_actor->GetWorld()); ActorItr; ++ActorItr)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("%s"), *ActorItr->GetName());
	//	FVector WorldLocation = ActorItr->GetActorLocation();
	//	FVector2D ScreenLocation;
	//	PlayerController->ProjectWorldLocationToScreen(WorldLocation, ScreenLocation);

	//	FTransform transform = ActorItr->GetTransform();
	//	FVector origin;
	//	FVector boxExtent;
	//	FVector2D origin_2d, extent_2d;
	//	FVector2D size;
	//	ActorItr->GetActorBounds(false, origin, boxExtent);
	//	PlayerController->ProjectWorldLocationToScreen(origin, origin_2d);
	//	PlayerController->ProjectWorldLocationToScreen(boxExtent, extent_2d);
	//	size = extent_2d - origin_2d;

	//	UE_LOG(LogTemp, Warning, TEXT("%s"), *ScreenLocation.ToString());
	//	//UE_LOG(LogTemp, Warning, TEXT("%s"), *transform.ToString());
	//	//UE_LOG(LogTemp, Warning, TEXT("%s"), *box.ToString());
	//	UE_LOG(LogTemp, Warning, TEXT("%s"), *size.ToString());
	//}
	return std::vector<AbstractNode>();
}
