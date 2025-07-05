// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/OutbreakCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HUD/OutbreakHUD.h"
#include "Player/OutbreakPlayerController.h"

AOutbreakCharacter::AOutbreakCharacter()
{
	//Rotate toward movement | Auto-face movement direction
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//How fast it turns | Smooth or snappy turning
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	//Force flat movement | Ideal for 2D or top-down
	// GetCharacterMovement()->bConstrainToPlane = true;
	//Align at spawn | Prevent floating offset
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	//No manual rotation | Let movement control rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;	

	//This will get the character movement component
	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
	if (CharacterMovementComponent != nullptr)
	{
		// Set new walk speed
		CharacterMovementComponent->MaxWalkSpeed = 250.f;

		// Set new acceleration
		CharacterMovementComponent->MaxAcceleration = 1500.0f;

		//Set new gravity scale
		CharacterMovementComponent->GravityScale = 1.0f;

		//Set new breaking friction
		CharacterMovementComponent->BrakingFriction = 0.0f;
	}

	//Add tag
	Tags.Add(FName("Player"));
}

void AOutbreakCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//Init HUD actor info for the server
	InitCharacterHUD();
}

void AOutbreakCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//Init HUD actor info for the client
	InitCharacterHUD();
}

void AOutbreakCharacter::InitCharacterHUD()
{
	AOutbreakPlayerState* OutbreakPlayerState = GetPlayerState<AOutbreakPlayerState>();
	checkf(OutbreakPlayerState, TEXT("There is no outbreak player state."));
	
	if (AOutbreakPlayerController* OutbreakPlayerController = Cast<AOutbreakPlayerController>(GetController()))
	{
		if (AOutbreakHUD* OutbreakHUD = Cast<AOutbreakHUD>(OutbreakPlayerController->GetHUD())	)
		{
			OutbreakHUD->InitMainWidget(OutbreakPlayerState);
			OutbreakHUD->InitInventoryMenuWidget();
			OutbreakHUD->InitPlayerState(OutbreakPlayerState);
			OutbreakPlayerController->SetOutbreakHUD(OutbreakHUD);
		}
	}
}
