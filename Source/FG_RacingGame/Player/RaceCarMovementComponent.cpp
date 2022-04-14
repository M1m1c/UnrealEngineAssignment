#include "RaceCarMovementComponent.h"

URaceCarMovementComponent::URaceCarMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URaceCarMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	AActor* Owner = GetOwner();

	// Apply acceleration
	Velocity += Owner->GetActorForwardVector() * Acceleration * DriveForwardInput * DeltaTime;

	// Apply friction
	FVector RollingVelocity = Velocity.ProjectOnTo(Owner->GetActorForwardVector());
	FVector GripVelocity = Velocity - RollingVelocity;

	RollingVelocity -= RollingVelocity * RollFriction * DeltaTime;
	GripVelocity -= GripVelocity * GripFriction * DeltaTime;

	Velocity = RollingVelocity + GripVelocity;

	// Apply movement
	float RemainingTime = DeltaTime;
	int Iterations = 0;

	while (RemainingTime > 0.f && ++Iterations < 10)
	{
		FHitResult Hit;
		Owner->AddActorWorldOffset(Velocity * RemainingTime, true, &Hit);

		// Ooof, we hit something
		if (Hit.bBlockingHit)
		{
			// Uh oh! Depenetration time baybee!!
			if (Hit.bStartPenetrating)
			{
				Owner->AddActorWorldOffset(Hit.Normal * (Hit.PenetrationDepth + 0.1f));
			}
			// otherwise, just redirect and keep going :)
			else
			{
				Velocity = FVector::VectorPlaneProject(Velocity, Hit.Normal);
				RemainingTime -= RemainingTime * Hit.Time;
			}
		}
		else
		{
			break;
		}
	}

	if (Iterations == 10)
	{
		UE_LOG(LogTemp, Log, TEXT("WE'RE STUCK!!!"));
	}

	float Speed = FVector::DotProduct(Velocity, Owner->GetActorForwardVector());
	Owner->AddActorWorldRotation(FRotator(0.f, DriveSteerInput * TurnSpeed * Speed * DeltaTime, 0.f));
}

void URaceCarMovementComponent::AddForce(const FVector& Force)
{
	Velocity += Force * GetWorld()->GetDeltaSeconds();
}

void URaceCarMovementComponent::AddImpulse(const FVector& Impulse)
{
	Velocity += Impulse;
}
