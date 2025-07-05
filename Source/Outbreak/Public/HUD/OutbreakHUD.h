// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerState/OutbreakPlayerState.h"
#include "UI/Controllers/OutbreakMainWidgetController.h"
#include "UI/Inventory/OutbreakInventoryMenuWidget.h"
#include "UI/Main/OutbreakMainWidget.h"
#include "OutbreakHUD.generated.h"

/**
 * 
 */
UCLASS()
class OUTBREAK_API AOutbreakHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UOutbreakInventoryMenuWidget> InventoryMenuWidget;

	UPROPERTY()
	TObjectPtr<UOutbreakMainWidget> MainWidget;

	UOutbreakMainWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	UPROPERTY()
	TObjectPtr<AOutbreakPlayerState> PlayerState;

	void InitMainWidget(APlayerState* PS);
	
	void InitInventoryMenuWidget();

	void InitPlayerState(AOutbreakPlayerState* value);

	void ToggleInventoryMenu(bool IsOpen);

	void ToggleMainWidget(bool IsOpen);

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOutbreakInventoryMenuWidget> InventoryMenuClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOutbreakMainWidget> MainClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UOutbreakMainWidgetController> OutbreakMainWidgetController;
};
