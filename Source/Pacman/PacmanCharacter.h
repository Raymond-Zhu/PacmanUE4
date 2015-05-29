// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PacmanCharacter.generated.h"

UCLASS()
class PACMAN_API APacmanCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APacmanCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//Keeps track of player score;
	float PlayerScore;
	
	//Calculates Left and Right Movements;
	void MoveRight(float Val);

	//Calculates Forward and Backward Movements;
	void MoveForward(float Val);
};
