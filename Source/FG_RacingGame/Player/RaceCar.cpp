#include "RaceCar.h"
#include "Components/BoxComponent.h"
#include "RaceCarMovementComponent.h"
#include "FG_RacingGame/Powerup/RacePowerup.h"
#include "FG_RacingGame/Game/RaceGameInstance.h"
#include "FG_RacingGame/Game/RaceGameMode.h"
#include "FG_RacingGame/UI/RaceOverlayWidget.h"
#include "FG_RacingGame/UI/RacePlayerStatusWidget.h"
#include "Net/UnrealNetwork.h"
#include "DrawDebugHelpers.h"

ARaceCar::ARaceCar()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bAlwaysRelevant = true;
	NetUpdateFrequency = 60.0f;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Block);
	RootComponent = BoxCollision;

	MoveComp = CreateDefaultSubobject<URaceCarMovementComponent>(TEXT("MovementComponent"));
	MoveComp->SetIsReplicated(true);
}

void ARaceCar::BeginPlay()
{
	Super::BeginPlay();
}

void ARaceCar::EndPlay(const EEndPlayReason::Type Reason)
{
	Super::EndPlay(Reason);

	URaceGameInstance* GameInstance = URaceGameInstance::Get(this);
	GameInstance->Cars.Remove(this);
}

void ARaceCar::Tick(float DeltaTime)
{
	FString temp;
	temp.AppendInt(PlayerIndex);
	DrawDebugString(GetWorld(), FVector(0, 0, 100), temp, this, FColor::White, DeltaTime);
}

void ARaceCar::SetupPlayerInputComponent(UInputComponent* InputComp)
{
	InputComp->BindAxis(TEXT("Accelerate"), this, &ARaceCar::HandleAccelerateInput);
	InputComp->BindAxis(TEXT("TurnRight"), this, &ARaceCar::HandleTurnRightInput);
	InputComp->BindAction(TEXT("ActivatePowerup"), IE_Pressed, this, &ARaceCar::HandleActivatePowerup);
}

void ARaceCar::HandleActivatePowerup()
{
	if (Powerup != nullptr && !bPowerupActivated)
	{
		Powerup->OnPowerupActivated();
		bPowerupActivated = true;
	}
}

void ARaceCar::HandleAccelerateInput(float Value)
{
	MoveComp->DriveForwardInput = Value;

}

void ARaceCar::HandleTurnRightInput(float Value)
{
	MoveComp->DriveSteerInput = Value;
}

void ARaceCar::EquipPowerup(URacePowerup* NewPowerup)
{
	Powerup = NewPowerup;
	if (Powerup != nullptr)
		Powerup->Setup();
}
//TODO Cleanup code and maybe add checkpoints/laps

void ARaceCar::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARaceCar, PlayerIndex);
}