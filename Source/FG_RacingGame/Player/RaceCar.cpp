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
	/*if (Powerup != nullptr)
	{
		FColor MsgColor = bPowerupActivated ? FColor::Green : FColor::Red;

		GEngine->AddOnScreenDebugMessage(
			INDEX_NONE,
			0.f,
			MsgColor,
			Powerup->GetClass()->GetName(),
			true,
			FVector2D(4.f)
		);

		if (bPowerupActivated)
		{
			Powerup->TickActive(DeltaTime);
			if (Powerup->ShouldDeactivate())
			{
				bPowerupActivated = false;
				EquipPowerup(nullptr);
			}
		}
	}*/
}

void ARaceCar::SetupPlayerInputComponent(UInputComponent* InputComp)
{
	InputComp->BindAxis(TEXT("Accelerate"), this, &ARaceCar::HandleAccelerateInput);
	//InputComp->BindAxis(TEXT("Accelerate"), this, &ARaceCar::Server_HandleAccelerateInput);
	InputComp->BindAxis(TEXT("TurnRight"), this, &ARaceCar::HandleTurnRightInput);
	//InputComp->BindAxis(TEXT("TurnRight"), this, &ARaceCar::Server_HandleTurnRightInput);
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
	/*GEngine->AddOnScreenDebugMessage(
		INDEX_NONE,
		0.f,
		FColor::Magenta,
		FString::Printf(TEXT("Accelerate: %f"), Value)
	);*/

	MoveComp->DriveForwardInput = Value;

}

void ARaceCar::HandleTurnRightInput(float Value)
{
	/*GEngine->AddOnScreenDebugMessage(
		INDEX_NONE,
		0.f,
		FColor::Red,
		FString::Printf(TEXT("Turn right: %f"), Value)
	);*/

	MoveComp->DriveSteerInput = Value;
}

void ARaceCar::EquipPowerup(URacePowerup* NewPowerup)
{
	Powerup = NewPowerup;
	if (Powerup != nullptr)
		Powerup->Setup();

	//auto* GameMode = ARaceGameMode::Get(this);
	//auto* StatusWidget = GameMode->OverlayWidget->StatusWidgets[PlayerIndex];

	//StatusWidget->SetEquippedPowerup(NewPowerup);
}


//TODO Cleanup code and maybe add checkpoints/laps

void ARaceCar::Server_HandleAccelerateInput_Implementation(float Value)
{
	HandleAccelerateInput(Value);
}

void ARaceCar::Server_HandleTurnRightInput_Implementation(float Value)
{
	HandleTurnRightInput(Value);
}

void ARaceCar::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARaceCar, PlayerIndex);
}