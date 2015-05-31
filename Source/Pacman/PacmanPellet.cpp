// Fill out your copyright notice in the Description page of Project Settings.

#include "Pacman.h"
#include "PacmanPellet.h"
#include "PacmanCharacter.h"
#include "PacmanController.h"


void APacmanPellet::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	APacmanCharacter* Pacman = Cast<APacmanCharacter>(OtherActor);
if (Pacman ) {
		APacmanController* Controller = Cast<APacmanController>(Pacman->GetController());
		if (Controller) {
			Controller->PlayerScore += 10;
		}
	}
	Destroy();
}