// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/OutbreakAttributesComponent.h"
#include "GameFramework/PlayerState.h"
#include "OutbreakPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class OUTBREAK_API AOutbreakPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AOutbreakPlayerState();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UOutbreakAttributesComponent* OutbreakAttributes;
	
};
