// Copyright Epic Games, Inc. All Rights Reserved.

#include "NewWorld_AIGameMode.h"
#include "NewWorld_AICharacter.h"
#include "UObject/ConstructorHelpers.h"

ANewWorld_AIGameMode::ANewWorld_AIGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
