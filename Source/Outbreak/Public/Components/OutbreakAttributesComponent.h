// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OutbreakAttributesComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OUTBREAK_API UOutbreakAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOutbreakAttributesComponent();

	UFUNCTION(BlueprintCallable)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	void SetHealth(float value);

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float value);

	UFUNCTION(BlueprintCallable)
	float GetStamina() const;

	UFUNCTION(BlueprintCallable)
	void SetStamina(float value);	

	UFUNCTION(BlueprintCallable)
	float GetMaxStamina() const;

	UFUNCTION(BlueprintCallable)
	void SetMaxStamina(float value);

private:
	UPROPERTY(EditAnywhere, Category = "Attributes")
	float Health = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	float Stamina = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	float MaxStamina = 100.0f;

		
};
