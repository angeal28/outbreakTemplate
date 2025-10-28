// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OutbreakStructInventoryItems.generated.h"

class AOutbreakItemBase;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FOutbreakStructInventoryItems : public FTableRowBase
{
	GENERATED_BODY()

public:
	// --- Gameplay Data ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AOutbreakItemBase> ItemBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Amount = 0;
	
};
