#pragma once
#include "CoreMinimal.h"
#include "RacePowerup.generated.h"

UCLASS(Blueprintable)
class URacePowerup : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void Setup();

	UFUNCTION(BlueprintNativeEvent)
	void OnPowerupActivated();

	UFUNCTION(BlueprintNativeEvent)
	bool ShouldDeactivate();

	UFUNCTION(BlueprintNativeEvent)
	void TickActive(float DeltaTime);

	UFUNCTION(Blueprintcallable)
	AActor* GetOwner() { return Cast<AActor>(GetOuter()); }
};