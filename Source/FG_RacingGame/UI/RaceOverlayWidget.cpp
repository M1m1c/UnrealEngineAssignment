#include "RaceOverlayWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "RacePlayerStatusWidget.h"

void URaceOverlayWidget::NativeConstruct()
{
	Super::NativeConstruct();
	StatusWidgets.SetNum(4);
}

void URaceOverlayWidget::AddPlayerStatus(int PlayerIndex)
{
	static FName SlotNames[] =
	{
		TEXT("Player0Slot"),
		TEXT("Player1Slot"),
		TEXT("Player2Slot"),
		TEXT("Player3Slot"),
	};

	/// CREATE SOME WIDGET ?????
	URacePlayerStatusWidget* PlayerStatus = NewObject<URacePlayerStatusWidget>(this, PlayerWidgetClass);
	StatusWidgets[PlayerIndex] = PlayerStatus;

	SetContentForSlot(SlotNames[PlayerIndex], PlayerStatus);
}
