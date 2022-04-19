// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RacePlayer.generated.h"

/**
 * 
 */
UCLASS()
class FG_RACINGGAME_API ARacePlayer : public APlayerController
{
	GENERATED_BODY()
public:
		ARacePlayer();
		void BeginPlay() override;
};
