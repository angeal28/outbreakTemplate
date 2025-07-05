// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Interfaces/OutbreakPickUpInterface.h"
#include "OutbreakPickUpBase.generated.h"

class AOutbreakItemBase;

UCLASS(Abstract)
class OUTBREAK_API AOutbreakPickUpBase : public AActor, public IOutbreakPickUpInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOutbreakPickUpBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Server, Reliable)
	virtual void PickUp_Implementation() override;

	//UFUNCTION(BlueprintNativeEvent) // 👈 must be BlueprintNativeEvent to override the function from the blueprint
	//void CallbackEvent();
	
	void EnabledPromp();

	void DisabledPromp();

	UFUNCTION(NetMulticast, Reliable) //👈 To replicate the sound from the client
	void PlayPickUpSound();

	virtual void BeginPlay() override;
	
	//This is the function of the callback to be called when the overlap trigger or end overlap
	//Note you can name it any like OnOverLapActor
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSubclassOf<AOutbreakItemBase> ItemBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float Radius = 90.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int Amount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<USoundCue> PickUpSound;

	//This is how to call a construction
	virtual void OnConstruction(const FTransform& Transform) override;
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(VisibleAnywhere)
	bool UpdateActor = false;
};
