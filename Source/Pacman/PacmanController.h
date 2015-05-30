// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "PacmanController.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API APacmanController : public APlayerController
{
	GENERATED_BODY()

public:	
	//Default Contrusctor
	APacmanController(const FObjectInitializer& ObjectInitializer);

	//Keeps track of player score.
	int32 PlayerScore;

	//Keeps track of player lives.
	int32 PlayerLives;
};
