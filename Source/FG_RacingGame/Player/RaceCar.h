#pragma once
#include "GameFramework/Pawn.h"
#include "RaceCar.generated.h"

class UBoxComponent;
class URaceCarMovementComponent;
class URacePowerup;

UCLASS()
class ARaceCar : public APawn
{
	GENERATED_BODY()

public:
	ARaceCar();

	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type Reason) override;
	void Tick(float DeltaTime) override;

	void SetupPlayerInputComponent(UInputComponent* InputComp) override;

	void HandleActivatePowerup();
	void HandleAccelerateInput(float Value);
	void HandleTurnRightInput(float Value);

	void EquipPowerup(URacePowerup* NewPowerup);
	bool HasEquippedPowerup() { return Powerup != nullptr; }

	UFUNCTION(Server, Reliable)
	void Server_HandleAccelerateInput(float Value);

	UFUNCTION(Server, Reliable)
	void Server_HandleTurnRightInput(float Value);

	UPROPERTY(BlueprintReadOnly, Replicated)
	int PlayerIndex = 0;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere)
	URaceCarMovementComponent* MoveComp;

	UPROPERTY()
	URacePowerup* Powerup;
	bool bPowerupActivated = false;
};