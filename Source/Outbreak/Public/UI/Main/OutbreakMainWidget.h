// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Controllers/OutbreakMainWidgetController.h"
#include "OutbreakMainWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class OUTBREAK_API UOutbreakMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UOutbreakMainWidgetController> WidgetController;

	UFUNCTION(BlueprintCallable)
	void ToggleStaminaBar();

	UFUNCTION(BlueprintCallable)
	void UnToggleStaminaBar();
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();

	UFUNCTION(BlueprintImplementableEvent)
	void StaminaBarToggle();

	UFUNCTION(BlueprintImplementableEvent)
	void StaminaBarUnToggle();
};
