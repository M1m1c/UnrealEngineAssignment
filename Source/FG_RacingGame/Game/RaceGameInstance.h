#pragma once

#include "Engine/GameInstance.h"
#include "RaceGameInstance.generated.h"

class ARaceCar;

UCLASS()
class URaceGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Race|Game Instance", Meta = (DisplayName = "GetRaceGameInstance", WorldContext="WorldContext"))
	static URaceGameInstance* Get(UObject* WorldContext);

	void Init() override;

	UPROPERTY(BlueprintReadOnly)
	TArray<ARaceCar*> Cars;
};