// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PacmanConsumable.h"
#include "PacmanPellet.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API APacmanPellet : public APacmanConsumable
{
	GENERATED_BODY()

		/* Destroys pellet and adds to Player Score*/
		virtual void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
};
