#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "RaceGameState.generated.h"

class ARaceCar;
class ARaceCamera;

UCLASS()
class ARaceGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Race|Game State", Meta = (DisplayName = "GetRaceGameState", WorldContext = "WorldContext"))
		static ARaceGameState* Get(UObject* WorldContext);

	UPROPERTY(BlueprintReadOnly)
		TArray<ARaceCar*> Cars;

	UPROPERTY(BlueprintReadOnly)
		ARaceCamera* Camera;

};
