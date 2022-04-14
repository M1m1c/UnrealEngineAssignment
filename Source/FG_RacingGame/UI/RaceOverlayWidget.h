#pragma once
#include "Blueprint/UserWidget.h"
#include "RaceOverlayWidget.generated.h"

class UCanvasPanel;
class URacePlayerStatusWidget;

UCLASS()
class URaceOverlayWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;
	void AddPlayerStatus(int PlayerIndex);

	UFUNCTION(BlueprintImplementableEvent)
	UCanvasPanel* GetMainCanvas();

	UPROPERTY(EditAnywhere, Category = RaceOverlay)
	TSubclassOf<URacePlayerStatusWidget> PlayerWidgetClass;

	UPROPERTY()
	TArray<URacePlayerStatusWidget*> StatusWidgets;
};
