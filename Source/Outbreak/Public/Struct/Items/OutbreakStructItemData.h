// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "OutbreakStructItemData.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Consumable UMETA(DisplayName="Consumable"),
	KeyItem UMETA(DisplayName="Key Item"),
	Weapon UMETA(DisplayName="Weapon"),
	Miscellaneous UMETA(DisplayName="Miscellaneous"),
	Backpack UMETA(DisplayName = "Backpack")
};

USTRUCT(BlueprintType)
struct FOutbreakStructItemData : public FTableRowBase
{

	GENERATED_BODY()

public:
	// --- Base Data --
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Base Data")
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Base Data")
	FText Description;

	// Type of item (weapon, key item, etc.)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Base Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Base Data")
	TObjectPtr<UTexture2D> Icon = nullptr;

	// Static mesh for world pickup
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Base Data")
	TObjectPtr<UStaticMesh> Mesh = nullptr;

	// Optional sound for pickup
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Base Data")
	TObjectPtr<USoundCue> PickupSound = nullptr;

	// --- Gameplay Data ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Gameplay Data")
	int32 Quantity = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Gameplay Data")
	int32 MaxStack = 10;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Gameplay Data")
	bool bCanBeUsed = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Gameplay Data")
	bool bCanBeExamine = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Gameplay Data")
	bool bCanBeDrop = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Gameplay Data")
	bool bIsStackable = false;

	// --- Item-specific stats ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Specific Stats")
	float Weight = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Specific Stats")
	float HealAmount = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Specific Stats")
	float DamageAmount = 0.f;
	
};
