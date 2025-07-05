// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAdvancedTransformInputBox.h"
#include "GameFramework/Actor.h"
#include "PickUps/OutbreakPickUpBase.h"
#include "OutbreakItemBase.generated.h"

UENUM()
enum class EItemType
{
	Item,
	Weapon,
	Consumable,
	Documents
};

UENUM()
enum class EItemTag
{
	KeyItem,
	Health,
	Equipment,
	Ammunition
};

USTRUCT(BlueprintType, Blueprintable) 
struct FItemData
{
	GENERATED_BODY()

	FItemData() : Icon(nullptr), Type(EItemType::Item), Tag(EItemTag::KeyItem), Value(0), MaxAmount(0), CanBeUsed(false), CanBeExamine(false),
	              CanBeDrop(false),
	              CanBeEquipped(false),
	              ExaminationMesh(nullptr),
	              ExaminationMeshOffset(0),
	              ExaminationDefaultMeshRotation(FRotator::ZeroRotator)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemTag Tag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int MaxAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSubclassOf<AOutbreakPickUpBase> PickUpActor; // 👈 This is how you choose a class

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool CanBeUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool CanBeExamine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool CanBeDrop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool CanBeEquipped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UStaticMeshComponent* ExaminationMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ExaminationMeshOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FRotator ExaminationDefaultMeshRotation;
};

UCLASS(Abstract)
class OUTBREAK_API AOutbreakItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOutbreakItemBase();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemData ItemData;
};
