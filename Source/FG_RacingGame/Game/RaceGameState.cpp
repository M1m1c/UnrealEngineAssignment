#include "RaceGameState.h"

ARaceGameState* ARaceGameState::Get(UObject* WorldContext)
{
	UWorld* World = WorldContext->GetWorld();
	return World->GetGameState<ARaceGameState>();
}