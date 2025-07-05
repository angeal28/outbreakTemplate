// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/OutbreakCharacterBase.h"

// Sets default values
AOutbreakCharacterBase::AOutbreakCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AOutbreakCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

