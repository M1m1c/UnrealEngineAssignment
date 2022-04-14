#include "RacePoopaShell.h"
#include "Components/SphereComponent.h"
#include "FG_RacingGame/Player/RaceCar.h"

ARacePoopaShell::ARacePoopaShell()
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = Collision;
}

void ARacePoopaShell::BeginPlay()
{
	Super::BeginPlay();
	ShellVelocity = GetActorForwardVector() * 1500.f;
}

void ARacePoopaShell::Tick(float DeltaTime)
{
	FHitResult Hit;
	AddActorWorldOffset(ShellVelocity * DeltaTime, true, &Hit);

	if (Hit.bBlockingHit)
	{
		if (Hit.Actor->IsA<ARaceCar>())
		{
			Hit.Actor->Destroy();
			Destroy();

			return;
		}

		if (Hit.bStartPenetrating)
		{
			AddActorWorldOffset(Hit.Normal * (Hit.PenetrationDepth + 0.01f));
		}
		else
		{
			ShellVelocity = ShellVelocity.MirrorByVector(Hit.Normal);
		}
	}
}
