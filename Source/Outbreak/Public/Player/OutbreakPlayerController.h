// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "HUD/OutbreakHUD.h"
#include "UI/Inventory/OutbreakInventoryMenuWidget.h"
#include "OutbreakPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class OUTBREAK_API AOutbreakPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AOutbreakPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

	bool IsInventoryOpen = false;

	void SetOutbreakHUD(AOutbreakHUD* value);

	void CenterMouseCursor();

	void UpdateCharacterRun(bool Running);

	bool IsRunning = false;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY()
	TObjectPtr<AOutbreakHUD> OutbreakHUD;
	
private:
	UFUNCTION(Server, Reliable) //👈 To replicate the pickup from the client to server or vise versa
	void Server_TryPickup(AActor* ActorToPickup);

	UFUNCTION(Server, Reliable) //👈 To replicate the running from the client to server or vise versa
	void Server_TryRun(bool value, ACharacter* MyChar);
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> OutbreakContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> RunAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> PickUpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> InventoryAction;
	
	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);
	void Run(const FInputActionValue& InputActionValue);
	void StopRun(const FInputActionValue& InputActionValue);
	void PickUp(const FInputActionValue& InputActionValue);
	void Inventory(const FInputActionValue& InputActionValue);
};
