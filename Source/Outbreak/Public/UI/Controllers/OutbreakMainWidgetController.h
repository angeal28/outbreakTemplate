// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Controllers/OutbreakWidgetController.h"
#include "OutbreakMainWidgetController.generated.h"

/**
 *  a macro in Unreal Engine used to declare a BlueprintAssignable delegate that broadcasts one parameter when called.
 *  It’s great for event-driven communication, especially when you want to notify Blueprints of a change.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChangedSignature, float, NewStamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxStaminaChangedSignature, float, NewMaxStamina);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class OUTBREAK_API UOutbreakMainWidgetController : public UOutbreakWidgetController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Outbreack|Attributes")
	FOnStaminaChangedSignature OnStaminaChanged;

	UPROPERTY(BlueprintAssignable, Category = "Outbreack|Attributes")
	FOnMaxStaminaChangedSignature OnMaxStaminaChanged;

	virtual void BroadcastInitialValues() override;

	void UpdateStamina(float value) const;

	void RegenerateStamina(float value) const;
	
};
