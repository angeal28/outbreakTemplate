// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/OutbreakInventoryComponent.h"

#include "Characters/OutbreakCharacter.h"
#include "HUD/OutbreakHUD.h"
#include "Items/OutbreakItemBase.h"
#include "Player/OutbreakPlayerController.h"
#include "UI/Inventory/OutbreakInventoryGridSlotWidget.h"
#include "UI/Inventory/OutbreakInventorySlotWidget.h"

// Sets default values for this component's properties
UOutbreakInventoryComponent::UOutbreakInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UOutbreakInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	AOutbreakCharacter* Char = Cast<AOutbreakCharacter>(GetOwner());
	if (Char)
	{
		AController* CharController = Char->GetController();
		if (CharController)
		{
			AOutbreakPlayerController* PlayerController = Cast<AOutbreakPlayerController>(CharController);\
			if (PlayerController)
			{
				OutbreakHUD = PlayerController->GetOutbreakHUD();
			}
		}
	}
}

void UOutbreakInventoryComponent::Initialize(int32 InventorySlot, AOutbreakHUD* Hud)
{
	//This will resize the array
	InventorySlots.SetNum(InventorySlot);
	OutbreakHUD = Hud;
}

void UOutbreakInventoryComponent::ValidateInventoryItem(TSubclassOf<AOutbreakItemBase> ItemBase, int32 Amount)
{
	AddItem(ItemBase, Amount);
}

void UOutbreakInventoryComponent::AddItem(TSubclassOf<AOutbreakItemBase> ItemBase, int32 Amount)
{
	FItemSlot Slot = CheckFreeInventorySlots();
	if (Slot.Success)
	{
		FOutbreakStructInventoryItems& InventorySlot = InventorySlots[Slot.SlotIndex];
		InventorySlot.ItemBase = ItemBase;
		InventorySlot.Amount = Amount;
		if (OutbreakHUD != nullptr)
		{
			// const FString Msg = FString::Printf(TEXT("HELLO"));
			// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, Msg);
			UOutbreakInventorySlotWidget* SlotWidget = OutbreakHUD->InventoryMenuWidget->OutbreakInventoryGridSlotWidget->SlotWidgetArray[Slot.SlotIndex];
			if (SlotWidget != nullptr)
			{
				SlotWidget->UpdateSlot(Cast<AOutbreakCharacter>(GetOwner()));
			}
		}
	}
	//This will print it like a print string on the blueprint
	if (GEngine)
	{
		int32 SlotIndex = 0;
		for (FOutbreakStructInventoryItems& InvSlot : InventorySlots)
		{
			if (InvSlot.ItemBase != nullptr)
			{
				//First get the class of the inventory slot
				UClass* ItemClass = InvSlot.ItemBase.Get();
				//Then get the default object assign to it
				AOutbreakItemBase* DefaultItem = ItemClass->GetDefaultObject<AOutbreakItemBase>();
				const FString Msg = FString::Printf(TEXT("picked up %s put it on slot %d"), *DefaultItem->ItemData.ItemName.ToString(), SlotIndex);
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, Msg);
			}
			SlotIndex++;
		}
	}
}

FItemSlot UOutbreakInventoryComponent::CheckFreeInventorySlots()
{
	int32 SlotIndex = 0;
	FItemSlot ItemSlot = FItemSlot();
	for (FOutbreakStructInventoryItems& Slot : InventorySlots)
	{
		if (Slot.Amount == 0)
		{
			ItemSlot.Success = true;
			ItemSlot.SlotIndex = SlotIndex;
			return ItemSlot;
		}
		SlotIndex++;
	}
	return ItemSlot;
}

FItemBase UOutbreakInventoryComponent::GetItemByIndex(int32 SlotIndex)
{
	FItemBase ItemBase = FItemBase();
	FOutbreakStructInventoryItems& InvSlot = InventorySlots[SlotIndex];
	//First get the class of the inventory slot
	UClass* ItemClass = InvSlot.ItemBase.Get();
	//Then get the default object assign to it
	ItemBase.Item = ItemClass->GetDefaultObject<AOutbreakItemBase>();
	ItemBase.Amount = InvSlot.Amount;
	return ItemBase;
}
