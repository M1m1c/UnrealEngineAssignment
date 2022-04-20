// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceCheckpoint.h"
#include <FG_RacingGame/Player/RacePlayer.h>
#include "Components/ShapeComponent.h"

ARaceCheckpoint::ARaceCheckpoint()
{
	UShapeComponent* collcomp = GetCollisionComponent();
	collcomp->OnComponentBeginOverlap.AddDynamic(this, &ARaceCheckpoint::OnOverlapBegin);
}

void ARaceCheckpoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Pawn = Cast<APawn>(OtherActor);
	if (!Pawn) { return; }
	if (!Pawn->IsLocallyControlled()) { return; }

	auto Controller = Pawn->GetController();
	if (!Controller) { return; }

	auto RacePlayer = Cast<ARacePlayer>(Controller);
	if (!RacePlayer) { return; }

	auto PlayerIndex = RacePlayer->GetCheckpointIndex();
	if (PlayerIndex == MaxIndex && Index == MinIndex)
	{
		RacePlayer->SetCheckpointIndex(Index);
		RacePlayer->IncreaseLapCount();
	}
	else if ((PlayerIndex + 1) == Index) 
	{
		RacePlayer->SetCheckpointIndex(Index);
	}
}
