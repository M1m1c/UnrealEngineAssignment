#include "RaceCarMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include <FG_RacingGame/Game/RaceGameState.h>

URaceCarMovementComponent::URaceCarMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URaceCarMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	AActor* Owner = GetOwner();
	auto Pawn = Cast<APawn>(Owner);
	if (!ensure(Pawn)) { return; }
	
	auto localControl = Pawn->IsLocallyControlled();
	auto Role = Pawn->GetRemoteRole();

	if (Role == ENetRole::ROLE_AutonomousProxy && localControl)
	{
		auto Move = CreateNewMove(DeltaTime);
		UnusedMoves.Add(Move);
		Server_SendMove(Move);
	}
	else if(Role == ENetRole::ROLE_Authority && localControl)
	{
		auto Move = CreateNewMove(DeltaTime);
		Server_SendMove(Move);
	}
	else if (Role == ENetRole::ROLE_SimulatedProxy) 
	{
		SimulateMove(ServerState.PreviousMove);
	}
}

void URaceCarMovementComponent::AddForce(const FVector& Force)
{
	Velocity += Force * GetWorld()->GetDeltaSeconds();
}

void URaceCarMovementComponent::AddImpulse(const FVector& Impulse)
{
	Velocity += Impulse;
}

void URaceCarMovementComponent::Server_SendMove_Implementation(FRaceCarMove NewMove)
{
	SimulateMove(NewMove);
	ServerState.PreviousMove = NewMove;
	ServerState.Transform = GetOwner()->GetActorTransform();
	ServerState.Velocity = Velocity;
}

void URaceCarMovementComponent::SimulateMove(const FRaceCarMove& Move)
{
	AActor* Owner = GetOwner();

	// Apply acceleration
	Velocity += Owner->GetActorForwardVector() * Acceleration * Move.DriveForwardInput * Move.DeltaTime;

	// Apply friction
	FVector RollingVelocity = Velocity.ProjectOnTo(Owner->GetActorForwardVector());
	FVector GripVelocity = Velocity - RollingVelocity;

	RollingVelocity -= RollingVelocity * RollFriction * Move.DeltaTime;
	GripVelocity -= GripVelocity * GripFriction * Move.DeltaTime;

	Velocity = RollingVelocity + GripVelocity;

	// Apply movement
	float RemainingTime = Move.DeltaTime;
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
	Owner->AddActorWorldRotation(FRotator(0.f, Move.DriveSteerInput * TurnSpeed * Speed * Move.DeltaTime, 0.f));
}

void URaceCarMovementComponent::ClearUsedMoves(FRaceCarMove PreviousMove)
{
	TArray<FRaceCarMove> NewMoves;

	for (const FRaceCarMove& Move : UnusedMoves)
	{
		if (Move.TimeStamp > PreviousMove.TimeStamp)
		{
			NewMoves.Add(Move);
		}
	}
	UnusedMoves = NewMoves;
}

FRaceCarMove URaceCarMovementComponent::CreateNewMove(float DeltaTime)
{
	FRaceCarMove Move;
	Move.DeltaTime = DeltaTime;
	Move.DriveForwardInput = DriveForwardInput;
	Move.DriveSteerInput = DriveSteerInput;
	Move.TimeStamp = ARaceGameState::Get(this)->GetServerWorldTimeSeconds();
	return Move;
}

void URaceCarMovementComponent::OnRep_ServerState()
{
	GetOwner()->SetActorTransform(ServerState.Transform);
	Velocity = ServerState.Velocity;
	ClearUsedMoves(ServerState.PreviousMove);

	for (const FRaceCarMove& Move : UnusedMoves)
	{
		SimulateMove(Move);
	}
}


void URaceCarMovementComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URaceCarMovementComponent, ServerState);
}
