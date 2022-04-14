#pragma once

#include "GameFramework/Actor.h"
#include "RacePoopaShell.generated.h"

class USphereComponent;

UCLASS()
class ARacePoopaShell : public AActor
{
	GENERATED_BODY()

public:
	ARacePoopaShell();

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Collision;

	FVector ShellVelocity;
};