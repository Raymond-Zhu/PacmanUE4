// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PacmanConsumable.h"
#include "PacmanPowerPellet.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API APacmanPowerPellet : public APacmanConsumable
{
	GENERATED_BODY()
	
	
	virtual void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	
};
