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

	//Calculates Left and Right Movements;
	void MoveRight(float Val);

	//Calculates Forward and Backward Movements;
	void MoveForward(float Val);

	void Respawn();

	TSubclassOf<class APacmanCharacter> PacmanBlueprint;

	/*Toggles Fire particles*/
	void ParticleToggle();

	/*Powers Pacman up for a limited time*/
	void PowerUp();

	/*Powers down Pacman*/
	void PowerDown();

	/*Spring Arm*/
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* CameraBoom;

	/* Player Camera */
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* PlayerCameraComponent;

	/*Manages Particle*/
	UPROPERTY(EditAnywhere, Category = "Particle")
	UParticleSystemComponent* ParticleSystem;

	/*Boolean used for checking if Pacman is powered up or not*/
	bool bIsPoweredUp;
	
	/*Timer Handle for Power Up*/
	FTimerHandle TimerHandle;

	/*Handles the direction of movement for the automove*/
	FVector Direction;

	/*Value used to pass into movement input*/
	float Value;
};
