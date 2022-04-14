#pragma once

#include "GameFramework/Actor.h"
#include "RacePowerupPickup.generated.h"

class USphereComponent;
class URacePowerup;

UCLASS()
class ARacePowerupPickup : public AActor
{
	GENERATED_BODY()

public:
	ARacePowerupPickup();

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool bFromSweep, const FHitResult& SweepHit);

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<URacePowerup>> PowerupClasses;
};