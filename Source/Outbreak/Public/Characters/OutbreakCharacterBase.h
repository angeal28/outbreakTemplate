// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OutbreakCharacterBase.generated.h"

UCLASS(Abstract)
class OUTBREAK_API AOutbreakCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOutbreakCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
