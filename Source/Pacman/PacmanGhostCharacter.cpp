// Fill out your copyright notice in the Description page of Project Settings.

#include "Pacman.h"
#include "PacmanCharacter.h"
#include "PacmanController.h"
#include "PacmanGhostCharacter.h"
#include "PacmanGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APacmanGhostCharacter::APacmanGhostCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	Capsule->OnComponentHit.AddDynamic(this, &APacmanGhostCharacter::OnHit);
	Capsule->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	Capsule->CanCharacterStepUpOn = ECB_No;
}

// Called when the game starts or when spawned
void APacmanGhostCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APacmanGhostCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void APacmanGhostCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void APacmanGhostCharacter::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	APacmanCharacter* Pacman = Cast<APacmanCharacter>(OtherActor);
	if (Pacman) 
	{
		/*If Pacman is powered up, Ghost is eaten and respawned*/
		if (Pacman->bIsPoweredUp) 
		{
			//Temporarily destroys Ghost. TODO: Respawn ghost.
			Destroy();
		}
		/*If Pacman is not powered up, Pacman loses his life and respawns.*/
		else 
		{
			APacmanController* Controller = Cast<APacmanController>(Pacman->GetController());
			if (Controller)
			{
				//TODO: Respawn Pacman
				Controller->PlayerLives--;
				if (Controller->PlayerLives > 0)
				{
					Pacman->Respawn();
				}
				//TODO:Game OverScreen when lives hit zero
			}
		}

	}
}
