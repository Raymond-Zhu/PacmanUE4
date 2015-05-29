// Fill out your copyright notice in the Description page of Project Settings.

#include "Pacman.h"
#include "PacmanPellet.h"
#include "PacmanCharacter.h"



void APacmanPellet::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	APacmanCharacter* Pacman = Cast<APacmanCharacter>(OtherActor);
	if (Pacman) {
		Pacman->PlayerScore += 10;
	}
	Destroy();
}