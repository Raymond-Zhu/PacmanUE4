// Fill out your copyright notice in the Description page of Project Settings.

#include "Pacman.h"
#include "PacmanHUD.h"
#include "PacmanController.h"
#include "Kismet/GameplayStatics.h"

APacmanHUD::APacmanHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> HUDLivesObj(TEXT("/Game/Pacman/cute_ball_games.cute_ball_games"));
	Lives = UCanvas::MakeIcon(HUDLivesObj.Object);

	//Gets Font
	static ConstructorHelpers::FObjectFinder<UFont>HUDFontObj(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
	HUDFont = HUDFontObj.Object;
}

void APacmanHUD::DrawHUD()
{
	Super::DrawHUD();

	//Scales the HUD according to Canvas Size;
	float ScreenXRatio = Canvas->SizeX/ 1280.f;
	float ScreenYRatio = Canvas->SizeY/ 720.f;

	//Gets the Pawn Player 0(aka you) owns.
	APawn* Pacman = Cast<APawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	//Get Controller which stores the Player score and life
	APacmanController* Controller = Cast<APacmanController>(Pacman->GetController());

	//Draws it to HUD
	FString PlayerScore = FString::Printf(TEXT("%d"),Controller->PlayerScore);
	DrawText(PlayerScore, FColor::White, ScreenXRatio * 300, ScreenYRatio * 660, HUDFont, 2.0f, false); 

	for (int32 i = Controller->PlayerLives; i > 0; i--) 
	{
		float PositionX = 700.f + i * 64;
		Canvas->DrawIcon(Lives, PositionX * ScreenXRatio, 650 * ScreenYRatio, .125);
	}
}