#pragma once
#include "Blueprint/UserWidget.h"
#include "RacePlayerStatusWidget.generated.h"

class UTextBlock;
class URacePowerup;

UCLASS()
class URacePlayerStatusWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	UTextBlock* GetNameTextBlock();
	UFUNCTION(BlueprintImplementableEvent)
	UTextBlock* GetPowerupTextBlock();

	void SetPlayerName(const FString& Name);
	void SetEquippedPowerup(URacePowerup* Powerup);
};