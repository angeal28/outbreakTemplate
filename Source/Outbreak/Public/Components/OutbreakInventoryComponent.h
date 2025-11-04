// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OutbreakInventoryComponent.generated.h"


class AOutbreakCharacter;
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

	UPROPERTY()
	AOutbreakCharacter* OutbreakCharacter;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", ReplicatedUsing=OnRep_InventorySlots)
	TArray<FOutbreakStructInventoryItems> InventorySlots;

	UFUNCTION(BlueprintCallable)
	void ValidateInventoryItem(TSubclassOf<AOutbreakItemBase> ItemBase, int32 Amount);

	UFUNCTION(BlueprintCallable)
	void AddItem(TSubclassOf<AOutbreakItemBase> ItemBase, int32 Amount);

	UFUNCTION(BlueprintCallable)
	void InitializeInventorySlots(int32 InventorySlot);
	
	UFUNCTION(Server, Reliable) //👈 To replicate the pickup from the client to server or vise versa
	void Server_TryInitializeInventorySlots(int32 InventorySlot);

	//Remember the UI exist only on the player side don't send it to the server
	UFUNCTION(BlueprintCallable)
	void InitializeOutbreakHUD(AOutbreakHUD* Hud);

	UFUNCTION(BlueprintCallable)
	void InitializeOutbreakCharacter(AOutbreakCharacter* Character);

	// UFUNCTION(Server, Reliable) //👈 To replicate the pickup from the client to server or vise versa
	// void Server_TryInitializeOutbreakCharacter(AOutbreakCharacter* Character);

	//This will create a function that has two variable that can be return in the blueprint
	//UFUNCTION(BlueprintCallable)
	//void CheckFreeInventorySlots(bool& OutSuccess, int32& OutInventoryIndex);

	UFUNCTION(BlueprintCallable)
	FItemSlot CheckFreeInventorySlots();

	// UFUNCTION(BlueprintCallable)
	FItemBase GetItemByIndex(int32 SlotIndex);

	UFUNCTION()
	void OnRep_InventorySlots();
	
};
