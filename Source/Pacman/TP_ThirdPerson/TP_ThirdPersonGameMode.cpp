// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Pacman.h"
#include "TP_ThirdPersonGameMode.h"
#include "TP_ThirdPersonCharacter.h"

ATP_ThirdPersonGameMode::ATP_ThirdPersonGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
