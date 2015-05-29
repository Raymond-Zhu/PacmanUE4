// Fill out your copyright notice in the Description page of Project Settings.

#include "Pacman.h"
#include "PacmanCharacter.h"


// Sets default values
APacmanCharacter::APacmanCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerScore = 0;

}

// Called when the game starts or when spawned
void APacmanCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APacmanCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void APacmanCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	//Movement
	InputComponent->BindAxis("MoveForward", this, &APacmanCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APacmanCharacter::MoveRight);
}

void APacmanCharacter::MoveForward(float Val) {
	if (Controller && Val != 0.0f) 
	{
		// Limit pitch when walking or falling
		const bool bLimitRotation = (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling());
		const FRotator Rotation = bLimitRotation ? GetActorRotation() : Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);

		AddMovementInput(Direction, Val);
	}
}

void APacmanCharacter::MoveRight(float Val) {
	if (Controller && Val != 0.f)
	{
		const FRotator Rotation = GetActorRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Val);
	}
}