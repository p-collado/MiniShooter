// Copyright Epic Games, Inc. All Rights Reserved.

#include "MiniShooterGameMode.h"
#include "UObject/ConstructorHelpers.h"

AMiniShooterGameMode::AMiniShooterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprint/Character/BP_Character"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}