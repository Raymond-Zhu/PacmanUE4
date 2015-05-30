// Fill out your copyright notice in the Description page of Project Settings.

#include "Pacman.h"
#include "PacmanPellet.h"
#include "PacmanCharacter.h"
#include "PacmanController.h"



void APacmanPellet::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	APacmanCharacter* Pacman = Cast<APacmanCharacter>(OtherActor);
	APacmanController* Controller = Cast<APacmanController>(Pacman->GetOwner());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));

	if (Pacman ) {
		APacmanController* Controller = Cast<APacmanController>(Pacman->GetController());
		if (Controller) {
			Controller->PlayerScore += 10;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Some variable values: x: %d"),Controller->PlayerScore));
		}
	}
	Destroy();
}