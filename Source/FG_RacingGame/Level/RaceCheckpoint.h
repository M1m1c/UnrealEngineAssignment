// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "RaceCheckpoint.generated.h"

/**
 * 
 */
UCLASS()
class FG_RACINGGAME_API ARaceCheckpoint : public ATriggerBox
{
	GENERATED_BODY()

		ARaceCheckpoint();
private:
		UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		
		UPROPERTY(EditDefaultsOnly)
			int MaxIndex = 3;

		UPROPERTY(EditDefaultsOnly)
			int MinIndex = 0;

		UPROPERTY(EditInstanceOnly)
			int Index = 0;
};
