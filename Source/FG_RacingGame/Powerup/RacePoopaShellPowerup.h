#pragma once
#include "RacePowerup.h"
#include "RacePoopaShellPowerup.generated.h"

class ARacePoopaShell;

UCLASS(Abstract)
class URacePoopaShellPowerup : public URacePowerup
{
	GENERATED_BODY()

public:
	void OnPowerupActivated_Implementation() override;

	UPROPERTY(EditDefaultsOnly, Category = Poopa)
	TSubclassOf<ARacePoopaShell> PoopaClass;

	UPROPERTY(EditDefaultsOnly, Category = Poopa)
	float SpawnOffset = 200.f;
};