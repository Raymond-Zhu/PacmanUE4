// Fill out your copyright notice in the Description page of Project Settings.

#include "Pacman.h"
#include "PacmanGhostCharacter.h"


// Sets default values
APacmanGhostCharacter::APacmanGhostCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent->OnComponentHit.AddDynamic(this, &APacmanGhostCharacter::OnHit);
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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));
}
