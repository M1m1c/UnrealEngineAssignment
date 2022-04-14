#include "RaceStartLine.h"
#include "FG_RacingGame/Player/RaceCar.h"
#include "FG_RacingGame/Game/RaceGameInstance.h"
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

	FTransform SpawnTransform = GetActorTransform();

	for (int i = 0; i < NumberOfPlayers; ++i)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerControllerFromID(this, i);
		if (PlayerController == nullptr)
			PlayerController = UGameplayStatics::CreatePlayer(this, i);

		PlayerController->bAutoManageActiveCameraTarget = false;

		ARaceCar* Car = GetWorld()->SpawnActor<ARaceCar>(CarClass, SpawnTransform);
		Car->PlayerIndex = i;
		PlayerController->Possess(Car);

		URaceGameInstance* GameInstance = URaceGameInstance::Get(this);
		GameInstance->Cars.Add(Car);

		// Add player status widget
		ARaceGameMode* GameMode = ARaceGameMode::Get(this);
		GameMode->OverlayWidget->AddPlayerStatus(i);
		GameMode->OverlayWidget->StatusWidgets[i]->SetPlayerName(FString::Printf(TEXT("Player %d"), i + 1));

		SpawnTransform.AddToTranslation(GetActorRightVector() * 200.f);
	}

	UE_LOG(LogTemp, Log, TEXT("ARaceStartLine::BeginPlay"));
}
