// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/OutbreakCharacterBase.h"
#include "OutbreakCharacter.generated.h"

/**
 * 
 */
UCLASS()
class OUTBREAK_API AOutbreakCharacter : public AOutbreakCharacterBase
{
	GENERATED_BODY()

public:
	AOutbreakCharacter();

	//This function will be called when a Pawn (or Character) is possessed by a controller (e.g., a player or AI controller).
	//virtual -> This function can be overridden in child classes.
	virtual void PossessedBy(AController* NewController) override;

	//is part of Unreal Engine's replication system, and it's called automatically on clients when the PlayerState property of a Pawn or Character is replicated.
	//virtual -> This function can be overridden in child classes.
	virtual void OnRep_PlayerState() override;

	void InitCharacterHUD();
	
};
