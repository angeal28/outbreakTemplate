// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/OutbreakInventoryMenuWidget.h"

#include "UI/Inventory/OutbreakDropDownMenuWidget.h"

UOutbreakInventoryMenuWidget::UOutbreakInventoryMenuWidget(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
}

void UOutbreakInventoryMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UOutbreakInventoryMenuWidget::CloseDropDownMenu()
{
	OutbreakInventoryDropdownMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UOutbreakInventoryMenuWidget::InitPlayerController(AOutbreakPlayerController* value)
{
	MyPlayerController = value;
}
