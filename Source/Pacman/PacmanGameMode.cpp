// Fill out your copyright notice in the Description page of Project Settings.

#include "Pacman.h"
#include "PacmanGameMode.h"
#include "PacmanCharacter.h"
#include "PacmanController.h"
#include "PacmanHUD.h"

APacmanGameMode::APacmanGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<ACharacter> PlayerPawnBPClass(TEXT("Blueprint'/Game/Pacman/BP_Pacman.BP_Pacman_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	//Sets Default Controller
	PlayerControllerClass = APacmanController::StaticClass();
	
	//Sets Default HUD
	HUDClass = APacmanHUD::StaticClass();
}


