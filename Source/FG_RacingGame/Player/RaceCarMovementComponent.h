#pragma once
#include "Components/ActorComponent.h"
#include "RaceCarMovementComponent.generated.h"

USTRUCT()
struct FRaceCarMove
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
		float DriveForwardInput = 0.f;

	UPROPERTY()
		float DriveSteerInput = 0.f;

	UPROPERTY()
		float DeltaTime;

	UPROPERTY()
		float TimeStamp;
};

USTRUCT()
struct FRaceCarState
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY()
		FTransform Transform;

	UPROPERTY()
		FVector Velocity;

	UPROPERTY()
		FRaceCarMove PreviousMove;
};

UCLASS(Meta = (BlueprintSpawnableComponent))
class URaceCarMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URaceCarMovementComponent();
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddForce(const FVector& Force);
	void AddImpulse(const FVector& Impulse);

	UPROPERTY(EditDefaultsOnly, Category = "Driving")
		float Acceleration = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Driving")
		float RollFriction = 0.8f;

	UPROPERTY(EditDefaultsOnly, Category = "Driving")
		float GripFriction = 3.8f;

	UPROPERTY(EditDefaultsOnly, Category = "Driving")
		float TurnSpeed = 0.5f;

	void ClearUsedMoves(FRaceCarMove LastMove);

	void SimulateMove(FRaceCarMove Move);

	UFUNCTION(Server, Reliable)
	void Server_SendMove(FRaceCarMove NewMove);


	UPROPERTY(ReplicatedUsing=OnRep_ServerState)
	FRaceCarState ServerState;


	UFUNCTION()
	void OnRep_ServerState();

	FVector Velocity;

	float DriveForwardInput = 0.f;
	float DriveSteerInput = 0.f;

	TArray<FRaceCarMove> UnusedMoves;
};