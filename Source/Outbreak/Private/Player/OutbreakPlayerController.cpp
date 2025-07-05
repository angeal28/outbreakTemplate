// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/OutbreakPlayerController.h"

//For Input Mapping
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/PickUps/OutbreakPickUpBase.h"

AOutbreakPlayerController::AOutbreakPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AOutbreakPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	/**
	 * This code will check if the stamina of the character still not zero then continue running
	 * if not then stop running and regenerate the stamina
	 */
	if (IsRunning && OutbreakHUD != nullptr)
	{
		if (!(OutbreakHUD->PlayerState->OutbreakAttributes->GetStamina() <= 0))
		{
			UpdateCharacterRun(true);
		}
		else
		{
			UpdateCharacterRun(false);
		}
	}
	else
	{
		if (OutbreakHUD != nullptr && !(OutbreakHUD->PlayerState->OutbreakAttributes->GetStamina() >= OutbreakHUD->PlayerState->OutbreakAttributes->GetMaxStamina()))
		{
			UpdateCharacterRun(false);
		}
	}
}

void AOutbreakPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//Check If Set if not crash the game and input it to error logs
	checkf(OutbreakContext, TEXT("Input mapping context is null"));

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem != nullptr)
	{
		Subsystem->AddMappingContext(OutbreakContext, 0);
	}
}

void AOutbreakPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//Cast Check If not set then crash
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	//Movement
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AOutbreakPlayerController::Move);
	//Camera Look
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AOutbreakPlayerController::Look);
	//Running
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &AOutbreakPlayerController::Run);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AOutbreakPlayerController::StopRun);
	//Pick Up
	EnhancedInputComponent->BindAction(PickUpAction, ETriggerEvent::Triggered, this, &AOutbreakPlayerController::PickUp);
	//Inventory
	EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Triggered, this, &AOutbreakPlayerController::Inventory);
}

void AOutbreakPlayerController::SetOutbreakHUD(AOutbreakHUD* value)
{
	OutbreakHUD = value;
}

void AOutbreakPlayerController::CenterMouseCursor()
{
	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	// Calculate the center position
	FVector2D CenterPosition(ViewportSize.X / 2, ViewportSize.Y / 2);
	// Set the mouse position to the center
	if(FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().SetCursorPos(FVector2D(CenterPosition.X, CenterPosition.Y));
	}
}

void AOutbreakPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AOutbreakPlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerYawInput(InputAxisVector.X);
		ControlledPawn->AddControllerPitchInput(InputAxisVector.Y);
	}
}

void AOutbreakPlayerController::Run(const FInputActionValue& InputActionValue)
{
	UpdateCharacterRun(true);
}

void AOutbreakPlayerController::StopRun(const FInputActionValue& InputActionValue)
{
	UpdateCharacterRun(false);
}

void AOutbreakPlayerController::UpdateCharacterRun(bool Running)
{
	IsRunning = Running;
	ACharacter* OwningCharacter = GetCharacter();
	if (OwningCharacter->GetVelocity().SizeSquared() != 0)
	{
		if (IsRunning)
		{
			OwningCharacter->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
			OutbreakHUD->MainWidget->ToggleStaminaBar();
		}
		else
		{
			OwningCharacter->GetCharacterMovement()->MaxWalkSpeed = 250.0f;
			OutbreakHUD->MainWidget->UnToggleStaminaBar();
		}
		Server_TryRun(IsRunning, OwningCharacter);
	}
}


void AOutbreakPlayerController::Server_TryRun_Implementation(bool value, ACharacter* MyChar)
{
	if (value)
	{
		MyChar->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
	else
	{
		MyChar->GetCharacterMovement()->MaxWalkSpeed = 250.0f;
	}
}

void AOutbreakPlayerController::PickUp(const FInputActionValue& InputActionValue)
{
	TArray<AActor*> OverlappingActors;
	GetCharacter()->GetOverlappingActors(OverlappingActors, AOutbreakPickUpBase::StaticClass());
	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (OverlappingActor != nullptr)
		{
			if (OverlappingActor->GetClass()->ImplementsInterface(UOutbreakPickUpInterface::StaticClass()))
			{
				Server_TryPickup(OverlappingActor);
				break; // 👈 Just get only one from the array the first one
			}
		}
	}
}

void AOutbreakPlayerController::Server_TryPickup_Implementation(AActor* ActorToPickup)
{
	if (ActorToPickup->GetClass()->ImplementsInterface(UOutbreakPickUpInterface::StaticClass()))
	{
		IOutbreakPickUpInterface::Execute_PickUp(ActorToPickup);
	}
}

void AOutbreakPlayerController::Inventory(const FInputActionValue& InputActionValue)
{
	if (OutbreakHUD != nullptr)
	{
		FInputModeGameAndUI InputModeData;
		ACharacter* OutbreakCharacter = GetCharacter();
		if (IsInventoryOpen)
		{
			OutbreakHUD->ToggleInventoryMenu(IsInventoryOpen);
			OutbreakCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
			IsInventoryOpen = false;
			SetShowMouseCursor(false);
			ResetIgnoreLookInput();
			SetInputMode(FInputModeGameOnly());
		}
		else
		{
			//CenterMouseCursor(); This will set the mouse cursor to the middle of the screen
			OutbreakHUD->ToggleInventoryMenu(IsInventoryOpen);
			OutbreakCharacter->GetCharacterMovement()->SetMovementMode(MOVE_None);
			IsInventoryOpen = true;
			SetIgnoreLookInput(true);
			SetShowMouseCursor(true);
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			InputModeData.SetHideCursorDuringCapture(true);
			SetInputMode(InputModeData);
		}
	}
}