#include "RaceStartLine.h"
#include "FG_RacingGame/Player/RaceCar.h"
#include "FG_RacingGame/Game/RaceGameState.h"
#include "FG_RacingGame/Game/RaceGameMode.h"
#include "FG_RacingGame/UI/RaceOverlayWidget.h"
#include "FG_RacingGame/UI/RacePlayerStatusWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

ARaceStartLine::ARaceStartLine()
{
	//bReplicates = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
}

void ARaceStartLine::BeginPlay()
{
	Super::BeginPlay();

	//TODO make the game state work here
	auto GameState = ARaceGameState::Get(this);

	if (HasAuthority())
	{
		SpawnTransform = GetActorTransform();

		ARaceGameMode* GameMode = ARaceGameMode::Get(this);

		for (int i = 0; i < NumberOfPlayers; ++i)
		{	

			ARaceCar* Car = GetWorld()->SpawnActor<ARaceCar>(CarClass, SpawnTransform);
			Car->PlayerIndex = -1;		
			GameState->Cars.Add(Car);

			SpawnTransform.AddToTranslation(GetActorRightVector() * 200.f);

			// Add player status widget
			GameMode->OverlayWidget->AddPlayerStatus(i);
			GameMode->OverlayWidget->StatusWidgets[i]->SetPlayerName(FString::Printf(TEXT("Player %d"), i + 1));
			OnRep_SpawnTransform();
		}
	}
	
	ARaceCar* AvailableCar = nullptr;

	for (auto Car : GameState->Cars)
	{
		if(Car->PlayerIndex == -1)
		{
			AvailableCar = Car;
			break;
		}
	}
	
	if (!AvailableCar) { return; }

	APlayerController* PlayerController = UGameplayStatics::GetPlayerControllerFromID(this, 0);
	if (PlayerController == nullptr)
		PlayerController = UGameplayStatics::CreatePlayer(this, 0);
	PlayerController->bAutoManageActiveCameraTarget = false;

	AvailableCar->PlayerIndex = PlayerController->GetUniqueID();
	PlayerController->Possess(AvailableCar);

	UE_LOG(LogTemp, Log, TEXT("ARaceStartLine::BeginPlay"));
}

void ARaceStartLine::OnRep_SpawnTransform()
{
	UE_LOG(LogTemp, Log, TEXT("SpawnTransform Updated"));
}

void ARaceStartLine::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARaceStartLine, SpawnTransform);
}