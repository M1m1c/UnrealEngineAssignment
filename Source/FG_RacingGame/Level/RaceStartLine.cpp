#include "RaceStartLine.h"
#include "FG_RacingGame/Player/RaceCar.h"
#include "FG_RacingGame/Game/RaceGameState.h"
#include "FG_RacingGame/Game/RaceGameMode.h"
#include "FG_RacingGame/UI/RaceOverlayWidget.h"
#include "FG_RacingGame/UI/RacePlayerStatusWidget.h"
#include "Kismet/GameplayStatics.h"


ARaceStartLine::ARaceStartLine()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
}

void ARaceStartLine::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		auto GameState = ARaceGameState::Get(this);
		SpawnTransform = GetActorTransform();

		ARaceGameMode* GameMode = ARaceGameMode::Get(this);

		for (int i = 0; i < NumberOfPlayers; ++i)
		{	

			ARaceCar* Car = GetWorld()->SpawnActor<ARaceCar>(CarClass, SpawnTransform);
			Car->PlayerIndex = -1;		
			GameState->Cars.Add(Car);

			SpawnTransform.AddToTranslation(GetActorRightVector() * 200.f);
		}
	}
}