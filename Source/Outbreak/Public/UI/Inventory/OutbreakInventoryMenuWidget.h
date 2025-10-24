// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OutbreakInventoryMenuWidget.generated.h"

class AOutbreakPlayerController;
/**
 * 
 */
UCLASS(Abstract)
class OUTBREAK_API UOutbreakInventoryMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	//The BlueprintReadWrite can expose the variable on the blueprint for you to GET and SET
	UPROPERTY(BlueprintReadWrite, Category = "Controller")
	TObjectPtr<AOutbreakPlayerController> MyPlayerController = nullptr;

public:
	void InitPlayerController(AOutbreakPlayerController* value);
	
};
