// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Controllers/OutbreakMainWidgetController.h"


void UOutbreakMainWidgetController::BroadcastInitialValues()
{
	OnStaminaChanged.Broadcast(OutbreakPlayerState->OutbreakAttributes->GetStamina());
	OnMaxStaminaChanged.Broadcast(OutbreakPlayerState->OutbreakAttributes->GetMaxStamina());
}

void UOutbreakMainWidgetController::UpdateStamina(float value) const
{
	OutbreakPlayerState->OutbreakAttributes->SetStamina(OutbreakPlayerState->OutbreakAttributes->GetStamina() - value);
	OnStaminaChanged.Broadcast(OutbreakPlayerState->OutbreakAttributes->GetStamina());
}

void UOutbreakMainWidgetController::RegenerateStamina(float value) const
{
	OutbreakPlayerState->OutbreakAttributes->SetStamina(OutbreakPlayerState->OutbreakAttributes->GetStamina() + value);
	OnStaminaChanged.Broadcast(OutbreakPlayerState->OutbreakAttributes->GetStamina());
}
