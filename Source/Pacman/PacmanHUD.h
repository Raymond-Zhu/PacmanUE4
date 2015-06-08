// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "PacmanHUD.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API APacmanHUD : public AHUD
{
	GENERATED_BODY()

	APacmanHUD(const FObjectInitializer& ObjectInitializer);

	UPROPERTY()
	UFont* HUDFont;

	UPROPERTY()
	FCanvasIcon Lives;

	virtual void DrawHUD() override;
	
};
