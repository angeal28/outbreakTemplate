// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/SizeBox.h"
#include "Components/Button.h"
#include "Components/Overlay.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Struct/Inventory/OutbreakStructInventoryItems.h"
#include "OutbreakInventorySlotWidget.generated.h"

class AOutbreakCharacter;
/**
 * 
 */
UCLASS()
class OUTBREAK_API UOutbreakInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UOutbreakInventorySlotWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void UpdateSlot(AOutbreakCharacter* MyChar);

protected:
	virtual void NativeConstruct() override;
	
public:
	//If the Blueprint child defines those widgets (same names), C++ will bind to them.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slot", meta=(BindWidget))
	TObjectPtr<USizeBox> SizeBoxRoot;

	//If the Blueprint child defines those widgets (same names), C++ will bind to them.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slot", meta=(BindWidget))
	TObjectPtr<UButton> SlotButton;

	//If the Blueprint child defines those widgets (same names), C++ will bind to them.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slot", meta=(BindWidget))
	TObjectPtr<UOverlay> OverlayRoot;

	//If the Blueprint child defines those widgets (same names), C++ will bind to them.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slot", meta=(BindWidget))
	TObjectPtr<UImage> ItemIcon;

	//If the Blueprint child defines those widgets (same names), C++ will bind to them.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slot", meta=(BindWidget))
	TObjectPtr<UTextBlock> ItemCount;
	
	// Example variable you want to set at creation time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	int32 SlotIndex;

	// Reference to static data from DataTable or asset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Data")
	FOutbreakStructInventoryItems InventoryItem;

private:
	UFUNCTION()
	void SlotButtonClicked();
};
