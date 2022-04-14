#include "RaceGameMode.h"
#include "Blueprint/UserWidget.h"
#include "FG_RacingGame/UI/RaceOverlayWidget.h"

ARaceGameMode* ARaceGameMode::Get(UObject* WorldContext)
{
	return WorldContext->GetWorld()->GetAuthGameMode<ARaceGameMode>();
}

ARaceGameMode::ARaceGameMode()
{
	DefaultPawnClass = nullptr;
}

void ARaceGameMode::StartMatch()
{
	OverlayWidget = NewObject<URaceOverlayWidget>(this, OverlayWidgetClass);
	OverlayWidget->AddToViewport();

	Super::StartMatch();
}
