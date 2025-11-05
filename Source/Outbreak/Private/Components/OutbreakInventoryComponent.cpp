// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/OutbreakInventoryComponent.h"

#include "Characters/OutbreakCharacter.h"
#include "Helpers/OutbreakDebug.h"
#include "HUD/OutbreakHUD.h"
#include "Items/OutbreakItemBase.h"
#include "Net/UnrealNetwork.h"
#include "Player/OutbreakPlayerController.h"
#include "UI/Inventory/OutbreakInventoryGridSlotWidget.h"
#include "UI/Inventory/OutbreakInventorySlotWidget.h"

// Sets default values for this component's properties
UOutbreakInventoryComponent::UOutbreakInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ✅ This makes it replicate when the owner replicates
	SetIsReplicatedByDefault(true);
	// ...
}


// Called when the game starts
void UOutbreakInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UOutbreakInventoryComponent::InitializeInventorySlots(int32 InventorySlot)
{
	Server_TryInitializeInventorySlots(InventorySlot);
}

void UOutbreakInventoryComponent::Server_TryInitializeInventorySlots_Implementation(int32 InventorySlot)
{
	//This will resize the array
	InventorySlots.SetNum(InventorySlot);
}

void UOutbreakInventoryComponent::InitializeOutbreakHUD(AOutbreakHUD* Hud)
{
	OutbreakHUD = Hud;
}

void UOutbreakInventoryComponent::InitializeOutbreakCharacter(AOutbreakCharacter* Character)
{
	OutbreakCharacter = Character;
}

void UOutbreakInventoryComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UOutbreakInventoryComponent, InventorySlots);
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
		if (GetOwner()->HasAuthority())
		{
			if (OutbreakHUD != nullptr)
			{
				UOutbreakInventorySlotWidget* SlotWidget = OutbreakHUD->InventoryMenuWidget->OutbreakInventoryGridSlotWidget->SlotWidgetArray[Slot.SlotIndex];
				if (SlotWidget != nullptr)
				{
					SlotWidget->UpdateSlot(OutbreakCharacter);
				}
			}
		}
	}
	//This will print it like a print string on the blueprint
	int32 SlotIndex = 0;
	for (FOutbreakStructInventoryItems& InvSlot : InventorySlots)
	{
		if (InvSlot.ItemBase != nullptr)
		{
			//First get the class of the inventory slot
			UClass* ItemClass = InvSlot.ItemBase.Get();
			//Then get the default object assign to it
			AOutbreakItemBase* DefaultItem = ItemClass->GetDefaultObject<AOutbreakItemBase>();
			FOutbreakDebug::Get().Print(FString::Printf(TEXT("picked up %s put it on slot %d"), *DefaultItem->ItemData.ItemName.ToString(), SlotIndex));
		}
		SlotIndex++;
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
	if (ItemClass != nullptr)
	{
		//Then get the default object assign to it
		ItemBase.Item = ItemClass->GetDefaultObject<AOutbreakItemBase>();
		ItemBase.Amount = InvSlot.Amount;
		return ItemBase;
	}
	return ItemBase;
}

void UOutbreakInventoryComponent::OnRep_InventorySlots()
{
	if (InventorySlots.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventorySlots is empty on client."));
		return;
	}

	if (!OutbreakHUD || !OutbreakHUD->InventoryMenuWidget || !OutbreakHUD->InventoryMenuWidget->OutbreakInventoryGridSlotWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("HUD or widgets not ready yet."));
		return;
	}

	//Update UI
	for (int32 i = 0; i < InventorySlots.Num(); i++)
	{
		UOutbreakInventorySlotWidget* SlotWidget = OutbreakHUD->InventoryMenuWidget->OutbreakInventoryGridSlotWidget->SlotWidgetArray[i];
		if (SlotWidget && OutbreakCharacter)
		{
			SlotWidget->UpdateSlot(OutbreakCharacter);
		}
	}
}

