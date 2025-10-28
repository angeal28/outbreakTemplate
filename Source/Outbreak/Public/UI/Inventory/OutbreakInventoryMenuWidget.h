// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "OutbreakInventoryMenuWidget.generated.h"

class UOutbreakDropDownMenuWidget;
class UOutbreakInventoryGridSlotWidget;
class AOutbreakPlayerController;
/**
 * 
 */
UCLASS(Abstract)
class OUTBREAK_API UOutbreakInventoryMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UOutbreakInventoryMenuWidget(const FObjectInitializer& ObjectInitializer);
	
protected:
	//The BlueprintReadWrite can expose the variable on the blueprint for you to GET and SET
	UPROPERTY(BlueprintReadWrite, Category = "Controller")
	TObjectPtr<AOutbreakPlayerController> MyPlayerController = nullptr;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void CloseDropDownMenu();
	
public:
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* CanvasPanel;
	
	UPROPERTY(meta = (BindWidget))
	UWidget* InventoryBackground;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CharacterName;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UOutbreakInventoryGridSlotWidget* OutbreakInventoryGridSlotWidget;

	// Category Buttons
	UPROPERTY(meta = (BindWidget))
	UButton* btnInventory;
	
	UPROPERTY(meta = (BindWidget))
	UButton* btnDocuments;
	
	UPROPERTY(meta = (BindWidget))
	UButton* btnMaps;

	// Item Description
	UPROPERTY(meta = (BindWidget))
	USizeBox* sizeBoxItemDescription;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* txtItemName;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* txtItemDescription;
	
	UPROPERTY(meta = (BindWidget))
	UOutbreakDropDownMenuWidget* OutbreakInventoryDropdownMenuWidget;

	UPROPERTY(meta = (BindWidget))
	UButton* btnCloseDropdownMenu;
	
	void InitPlayerController(AOutbreakPlayerController* value);
	
};
