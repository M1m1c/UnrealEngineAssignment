#include "RacePowerupPickup.h"
#include "Components/SphereComponent.h"
#include "RacePowerup.h"
#include "FG_RacingGame/Player/RaceCar.h"

ARacePowerupPickup::ARacePowerupPickup()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(Root);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ARacePowerupPickup::HandleOverlap);
}

void ARacePowerupPickup::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool bFromSweep, const FHitResult& SweepHit)
{
	int RandomIndex = FMath::RandRange(0, PowerupClasses.Num() - 1);
	auto PowerupClass = PowerupClasses[RandomIndex];

	ARaceCar* Car = Cast<ARaceCar>(OtherActor);
	if (!Car->HasEquippedPowerup())
	{
		Car->EquipPowerup(NewObject<URacePowerup>(Car, PowerupClass));
		Destroy();
	}
}
