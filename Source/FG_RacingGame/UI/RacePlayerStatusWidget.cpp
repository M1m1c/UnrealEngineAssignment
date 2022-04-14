#include "RacePlayerStatusWidget.h"
#include "Components/TextBlock.h"
#include "FG_RacingGame/Powerup/RacePowerup.h"

void URacePlayerStatusWidget::SetPlayerName(const FString& Name)
{
	GetNameTextBlock()->SetText(FText::FromString(Name));
}

void URacePlayerStatusWidget::SetEquippedPowerup(URacePowerup* Powerup)
{
	if (Powerup == nullptr)
	{
		GetPowerupTextBlock()->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		GetPowerupTextBlock()->SetVisibility(ESlateVisibility::Visible);
		GetPowerupTextBlock()->SetText(FText::FromString(Powerup->GetName()));
	}
}