// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// ✅ Simple global debug utility usable anywhere
class FOutbreakDebug
{
public:
	// Singleton access
	static FOutbreakDebug& Get()
	{
		static FOutbreakDebug Instance;
		return Instance;
	}

	// Show on-screen message
	void Print(const FString& Message, FColor Color = FColor::Green, float Duration = 3.f)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, Duration, Color, Message);
		}
	}

	// Optional: print to both log and screen
	void LogAndPrint(const FString& Message, FColor Color = FColor::Green, float Duration = 3.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
		Print(Message, Color, Duration);
	}
	
private:
	// Private constructor to enforce singleton
	FOutbreakDebug() {}
};
