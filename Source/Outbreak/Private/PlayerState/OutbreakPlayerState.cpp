// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/OutbreakPlayerState.h"

AOutbreakPlayerState::AOutbreakPlayerState()
{

	OutbreakAttributes = CreateDefaultSubobject<UOutbreakAttributesComponent>("OutbreakAttributes");
	
	/**
	* function in Unreal Engine used to control how often an actor replicates over the network. This can improve performance or ensure more responsive replication depending on your game's needs.
	* However, SetNetUpdateFrequency() is now deprecated in UE5. Instead, Epic encourages using replication graph or fine-tuning NetUpdateFrequency in another way.
	*/
	SetNetUpdateFrequency(100.0f);
}
