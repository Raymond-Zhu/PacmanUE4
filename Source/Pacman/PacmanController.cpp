// Fill out your copyright notice in the Description page of Project Settings.

#include "Pacman.h"
#include "PacmanController.h"
#include "PacmanCharacter.h"

APacmanController::APacmanController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	PlayerScore = 0;
	PlayerLives = 3;
}
