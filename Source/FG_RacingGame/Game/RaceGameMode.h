#pragma once
#include "GameFramework/GameMode.h"
#include "RaceGameMode.generated.h"

class URaceOverlayWidget;

UCLASS()
class ARaceGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Race|Game Mode", Meta = (DisplayName = "Get Race Game Mode", WorldContext="WorldContext"))
	static ARaceGameMode* Get(UObject* WorldContext);

	ARaceGameMode();

	void StartMatch() override;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<URaceOverlayWidget> OverlayWidgetClass;
	UPROPERTY()
	URaceOverlayWidget* OverlayWidget;
};