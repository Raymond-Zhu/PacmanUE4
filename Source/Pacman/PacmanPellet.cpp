// Fill out your copyright notice in the Description page of Project Settings.

#include "Pacman.h"
#include "PacmanPellet.h"
#include "PacmanCharacter.h"
#include "PacmanController.h"


void APacmanPellet::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {

	/*Checks if the Actor colliding is Pacman*/
	APacmanCharacter* Pacman = Cast<APacmanCharacter>(OtherActor);
	if (Pacman ) {

		/*Gets the Controller of Pacman*/
		APacmanController* Controller = Cast<APacmanController>(Pacman->GetController());

		/*If it is Pacman and Controller exists, the Player's score is increased by ten and the pellet is destroyed*/
		if (Controller) {
			Controller->PlayerScore += 10;
			Destroy();
		}
	}
}