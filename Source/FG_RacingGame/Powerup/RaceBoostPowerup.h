#pragma once

#include "RacePowerup.h"
#include "RaceBoostPowerup.generated.h"

class URaceCarMovementComponent;

UCLASS()
class URaceBoostPowerup : public URacePowerup
{
	GENERATED_BODY()

public:
	void Setup_Implementation() override;
	void OnPowerupActivated_Implementation() override;
	bool ShouldDeactivate_Implementation() override;
	void TickActive_Implementation(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly)
		FText PowerupName;

	UPROPERTY()
	URaceCarMovementComponent* MoveComp;

	float BoostTime;
};