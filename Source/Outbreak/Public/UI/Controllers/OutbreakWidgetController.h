// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerState/OutbreakPlayerState.h"
#include "OutbreakWidgetController.generated.h"

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams() {}
	FWidgetControllerParams(APlayerState* PS)
	: OutbreakPlayerState(PS) {}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> OutbreakPlayerState = nullptr;

};

/**
 * 
 */
UCLASS(Abstract)
class OUTBREAK_API UOutbreakWidgetController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);

	//virtual -> This function can be overridden in child classes.
	virtual void BroadcastInitialValues();
	//virtual -> This function can be overridden in child classes.
	virtual void BindCallbacksToDependencies();
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<AOutbreakPlayerState> OutbreakPlayerState;
};
