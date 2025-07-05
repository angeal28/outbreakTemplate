// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Main/OutbreakMainWidget.h"

void UOutbreakMainWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = Cast<UOutbreakMainWidgetController>(InWidgetController);
	WidgetControllerSet();
}

void UOutbreakMainWidget::ToggleStaminaBar()
{
	WidgetController->UpdateStamina(.5f);
	StaminaBarToggle();
}

void UOutbreakMainWidget::UnToggleStaminaBar()
{
	WidgetController->RegenerateStamina(1.0f);
	StaminaBarUnToggle();
}


