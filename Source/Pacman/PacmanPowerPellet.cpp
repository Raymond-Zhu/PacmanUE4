// Fill out your copyright notice in the Description page of Project Settings.

#include "Pacman.h"
#include "PacmanPowerPellet.h"
#include "PacmanCharacter.h"



void APacmanPowerPellet::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) 
{
	/*Checks if the collision of the OtherActor is Pacman*/
	APacmanCharacter* Pacman = Cast<APacmanCharacter>(OtherActor);
	
	/*If it is Pacman, he is powered up and can eat ghosts and the pellet is destroyed.*/
	if (Pacman) 
	{
		Pacman->bIsPoweredUp = true;
		Destroy();
	}
}