// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/OutbreakHUD.h"

UOutbreakMainWidgetController* AOutbreakHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OutbreakMainWidgetController == nullptr)
	{
		OutbreakMainWidgetController = NewObject<UOutbreakMainWidgetController>();
		OutbreakMainWidgetController->SetWidgetControllerParams(WCParams);
		return OutbreakMainWidgetController;
	}
	return OutbreakMainWidgetController;
}

void AOutbreakHUD::InitMainWidget(APlayerState* PS)
{
	checkf(MainClass, TEXT("Main Widget Class uninitialized, please fill the BP_OutbreakHUD"));
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), MainClass);
	MainWidget = Cast<UOutbreakMainWidget>(Widget);
	MainWidget->SetVisibility(ESlateVisibility::Visible);
	const FWidgetControllerParams WidgetControllerParams(PS);
	UOutbreakMainWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	MainWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
}

void AOutbreakHUD::InitInventoryMenuWidget()
{
	checkf(InventoryMenuClass, TEXT("Inventory Menu Widget Class uninitialized, please fill the BP_OutbreakHUD"));
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), InventoryMenuClass);
	InventoryMenuWidget = Cast<UOutbreakInventoryMenuWidget>(Widget);
	InventoryMenuWidget->SetVisibility(ESlateVisibility::Collapsed); //Means hide take no space on the layout 
	Widget->AddToViewport();
}

void AOutbreakHUD::InitPlayerState(AOutbreakPlayerState* value)
{
	PlayerState = value;
}

void AOutbreakHUD::ToggleInventoryMenu(bool IsOpen)
{
	 if (IsOpen)
	 {
	 	ToggleMainWidget(true);
	 	InventoryMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	 }
	 else
	 {
	 	ToggleMainWidget(false);
		InventoryMenuWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	 }
}

void AOutbreakHUD::ToggleMainWidget(bool IsOpen)
{
	if (!IsOpen)
	{
		MainWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		MainWidget->SetVisibility(ESlateVisibility::Visible);
	}
}
