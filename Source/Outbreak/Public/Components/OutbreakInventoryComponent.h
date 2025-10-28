// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OutbreakInventoryComponent.generated.h"


class AOutbreakHUD;
struct FOutbreakStructInventoryItems;
class AOutbreakItemBase;

USTRUCT(BlueprintType)
struct FItemSlot
{
	GENERATED_BODY()

	UPROPERTY()
	bool Success = false;

	UPROPERTY()
	int32 SlotIndex;
};

USTRUCT(BlueprintType)
struct FItemBase
{
	GENERATED_BODY()

	UPROPERTY()
	AOutbreakItemBase* Item;

	UPROPERTY()
	int32 Amount;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class OUTBREAK_API UOutbreakInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOutbreakInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	AOutbreakHUD* OutbreakHUD;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FOutbreakStructInventoryItems> InventorySlots;

	UFUNCTION(BlueprintCallable)
	void Initialize(int32 InventorySlot, AOutbreakHUD* Hud);

	UFUNCTION(BlueprintCallable)
	void ValidateInventoryItem(TSubclassOf<AOutbreakItemBase> ItemBase, int32 Amount);

	UFUNCTION(BlueprintCallable)
	void AddItem(TSubclassOf<AOutbreakItemBase> ItemBase, int32 Amount);

	//This will create a function that has two variable that can be return in the blueprint
	//UFUNCTION(BlueprintCallable)
	//void CheckFreeInventorySlots(bool& OutSuccess, int32& OutInventoryIndex);

	UFUNCTION(BlueprintCallable)
	FItemSlot CheckFreeInventorySlots();

	// UFUNCTION(BlueprintCallable)
	FItemBase GetItemByIndex(int32 SlotIndex);
};
