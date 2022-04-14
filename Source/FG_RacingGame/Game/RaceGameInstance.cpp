#include "RaceGameInstance.h"

URaceGameInstance* URaceGameInstance::Get(UObject* WorldContext)
{
	UWorld* World = WorldContext->GetWorld();
	return World->GetGameInstance<URaceGameInstance>();
}

void URaceGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Log, TEXT("URaceGameInstance::Init called wohooo"));
}
