// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Struct/Items/OutbreakStructItemData.h"
#include "OutbreakItemBase.generated.h"

class AOutbreakCharacter;

UCLASS(Abstract)
class OUTBREAK_API AOutbreakItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOutbreakItemBase();

	// Reference to static data from DataTable or asset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Data")
	FOutbreakStructItemData ItemData;

protected:

	// === Actions ===
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Item Actions")
	void Use(AOutbreakCharacter* Player);
	virtual void Use_Implementation(AOutbreakCharacter* Player);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Item Actions")
	void Examine(AOutbreakCharacter* Player);
	virtual void Examine_Implementation(AOutbreakCharacter* Player);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Item Actions")
	void Drop(AOutbreakCharacter* Player);
	virtual void Drop_Implementation(AOutbreakCharacter* Player);
	
};
