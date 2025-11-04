// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Inventory/OutbreakInventorySlotWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Characters/OutbreakCharacter.h"
#include "Components/OutbreakInventoryComponent.h"
#include "Items/OutbreakItemBase.h"

UOutbreakInventorySlotWidget::UOutbreakInventorySlotWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

//NOTE NEED TO ADJUST THE CODE JUST GET OWNER
void UOutbreakInventorySlotWidget::UpdateSlot(AOutbreakCharacter* MyChar)
{
	// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, MyChar->GetName());
	UOutbreakInventoryComponent* InventoryComponent = MyChar->FindComponentByClass<UOutbreakInventoryComponent>();
	FItemBase ItemBase = InventoryComponent->GetItemByIndex(SlotIndex);
	if (ItemBase.Item != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item is %s"), *ItemBase.Item->ItemData.ItemName.ToString());
		ItemIcon->SetBrushFromTexture(ItemBase.Item->ItemData.Icon);
	}
}

void UOutbreakInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (SlotButton)
	{
		SlotButton->OnClicked.AddDynamic(this, &UOutbreakInventorySlotWidget::SlotButtonClicked);
	}
}

void UOutbreakInventorySlotWidget::SlotButtonClicked()
{
	// Your code here to execute when the button is clicked
	UE_LOG(LogTemp, Warning, TEXT("Button clicked!"));
}
