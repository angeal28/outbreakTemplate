// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OutbreakInventoryGridSlotWidget.generated.h"

class UOutbreakInventorySlotWidget;
/**
 * 
 */
UCLASS()
class OUTBREAK_API UOutbreakInventoryGridSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Slot")
	TSubclassOf<UOutbreakInventorySlotWidget> InventorySlotWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Slot")
	TArray<TObjectPtr<UOutbreakInventorySlotWidget>> SlotWidgetArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Slot")
	int32 SlotPerRow = 4;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Slot")
	float SlotPadding = 10.0f;
	
};
 