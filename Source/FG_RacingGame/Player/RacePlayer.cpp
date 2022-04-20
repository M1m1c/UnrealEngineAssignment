// Fill out your copyright notice in the Description page of Project Settings.


#include "RacePlayer.h"
#include <FG_RacingGame/Game/RaceGameState.h>
#include "FG_RacingGame/Player/RaceCar.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

ARacePlayer::ARacePlayer()
{
	bAutoManageActiveCameraTarget = false;
}

void ARacePlayer::BeginPlay()
{
	Super::BeginPlay();
	auto GameState = ARaceGameState::Get(this);

	if (!ensure(GameState)) { return; }
	if (ensure(GameState->Camera))
	{
		SetViewTarget((AActor*)GameState->Camera);
	}

	ARaceCar* AvailableCar = nullptr;

	for (auto Car : GameState->Cars)
	{
		if (!Car) { continue; }
		if (Car->PlayerIndex == -1)
		{
			AvailableCar = Car;
			break;
		}
	}

	if (!AvailableCar) { return; }

	AvailableCar->PlayerIndex = GetUniqueID();
	Possess(AvailableCar);
}

void ARacePlayer::IncreaseLapCount_Implementation()
{
	LapCount++;
}

void ARacePlayer::SetCheckpointIndex(int newIndex)
{
	CheckpointIndex = newIndex;
}

int ARacePlayer::GetCheckpointIndex()
{
	return CheckpointIndex;
}
