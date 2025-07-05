// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/OutbreakAttributesComponent.h"

UOutbreakAttributesComponent::UOutbreakAttributesComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

float UOutbreakAttributesComponent::GetHealth() const
{
	return Health;
}

void UOutbreakAttributesComponent::SetHealth(float value)
{
	Health = value;
}

float UOutbreakAttributesComponent::GetMaxHealth() const
{
	return MaxHealth;
}

void UOutbreakAttributesComponent::SetMaxHealth(float value)
{
	MaxHealth = value;
}

float UOutbreakAttributesComponent::GetStamina() const
{
	return Stamina;
}

void UOutbreakAttributesComponent::SetStamina(float value)
{
	Stamina = value;
}

float UOutbreakAttributesComponent::GetMaxStamina() const
{
	return MaxStamina;
}

void UOutbreakAttributesComponent::SetMaxStamina(float value)
{
	MaxStamina = value;
}


