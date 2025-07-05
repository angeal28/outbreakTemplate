// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Controllers/OutbreakWidgetController.h"

void UOutbreakWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	OutbreakPlayerState = Cast<AOutbreakPlayerState>(WCParams.OutbreakPlayerState);
}

void UOutbreakWidgetController::BroadcastInitialValues()
{
}

void UOutbreakWidgetController::BindCallbacksToDependencies()
{
}
