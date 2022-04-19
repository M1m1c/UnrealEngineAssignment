#pragma once
#include "GameFramework/Actor.h"
#include "RaceCamera.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ARaceCamera : public AActor
{
	GENERATED_BODY()

public:
	ARaceCamera();

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Camera Follow|Advanced")
	float FollowSpeed = 5.f;


	UPROPERTY(EditDefaultsOnly, Category = Camera)
	float MinCameraArmLength = 300.0f;

	UPROPERTY(Replicated)
	float CurrentCameraArmLength;

};