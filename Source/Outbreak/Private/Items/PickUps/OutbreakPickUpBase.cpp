// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PickUps/OutbreakPickUpBase.h"

#include "Components/OutbreakInventoryComponent.h"
#include "GameFramework/Character.h"
#include "Items/OutbreakItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
AOutbreakPickUpBase::AOutbreakPickUpBase()
{
	bReplicates = true;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	SetRootComponent(ItemMesh);
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(ItemMesh);
	Sphere->InitSphereRadius(Radius);
}

void AOutbreakPickUpBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOutbreakPickUpBase::PickUp_Implementation_Implementation(ACharacter* MyChar)
{
	if (HasAuthority())
	{
		UOutbreakInventoryComponent* InventoryComponent = MyChar->FindComponentByClass<UOutbreakInventoryComponent>();
		if (InventoryComponent != nullptr)
		{
			//Need inventory logic here
			PlayPickUpSound();
			Destroy();
		}
	}
}

void AOutbreakPickUpBase::EnabledPromp()
{
}

void AOutbreakPickUpBase::DisabledPromp()
{
}

void AOutbreakPickUpBase::PlayPickUpSound_Implementation()
{
	if (ItemBase != nullptr)
	{
		//This will get the default object of the actor
		AOutbreakItemBase* DefaultItem = ItemBase.GetDefaultObject();
		if (DefaultItem->ItemData.PickupSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), DefaultItem->ItemData.PickupSound, GetActorLocation());
		}
	}
}

void AOutbreakPickUpBase::BeginPlay()
{
	Super::BeginPlay();
	//This binds the callback for the overlap and end overlap on the sphere component
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AOutbreakPickUpBase::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AOutbreakPickUpBase::EndOverlap);
}

void AOutbreakPickUpBase::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		if (OtherActor->ActorHasTag(FName("Player")))
		{
		}
	}
}

void AOutbreakPickUpBase::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr)
	{
		if (OtherActor->ActorHasTag(FName("Player")))
		{
		}
	}
}

void AOutbreakPickUpBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (Sphere != nullptr)
	{
		Sphere->SetSphereRadius(Radius);
	}
}

