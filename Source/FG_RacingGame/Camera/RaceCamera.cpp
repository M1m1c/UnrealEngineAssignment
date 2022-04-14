#include "RaceCamera.h"
#include "Camera/CameraComponent.h"
#include "FG_RacingGame/Game/RaceGameInstance.h"
#include "FG_RacingGame/Player/RaceCar.h"
#include <Runtime/Engine/Classes/GameFramework/SpringArmComponent.h>

ARaceCamera::ARaceCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(Root);
	CameraArm->TargetArmLength = 800.0f; // The camera follows at this distance behind the character

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm);
}

void ARaceCamera::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	Controller->SetViewTarget(this);

	UE_LOG(LogTemp, Log, TEXT("ARaceCamera::BeginPlay"));
}

void ARaceCamera::Tick(float DeltaTime)
{
	int NumCars = 0;
	FVector LocationSum = FVector::ZeroVector;
	URaceGameInstance* GameInstance = URaceGameInstance::Get(this);

	float MaxDist = 0.f;

	for (int i = 0; i < GameInstance->Cars.Num(); i++)
	{
		auto CarCollection = GameInstance->Cars;

		ARaceCar* Car = CarCollection[i];
		if (!Car) { continue; }


		auto CurrentPos = Car->GetActorLocation();
		LocationSum += CurrentPos;
		NumCars++;

		auto nexIndex = i + 1;
		ARaceCar* NextCar = CarCollection.IsValidIndex(nexIndex) ? CarCollection[nexIndex] : nullptr;
		if (NextCar) 
		{
			auto NextPos = NextCar->GetActorLocation();
			MaxDist = FMath::Max(MaxDist, FVector::Dist(CurrentPos, NextPos));
		}
	}

	if (NumCars == 0)
		return;

	FVector TargetLocation = LocationSum / NumCars;
	FVector Location = GetActorLocation();
	Location = FMath::Lerp(Location, TargetLocation, FollowSpeed * DeltaTime);

	SetActorLocation(Location);

	CameraArm->TargetArmLength = MaxDist < 0.f ? MinCameraArmLength : MaxDist + MinCameraArmLength;
}
