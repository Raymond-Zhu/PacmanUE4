// Fill out your copyright notice in the Description page of Project Settings.

#include "Pacman.h"
#include "PacmanCharacter.h"
#include "PacmanController.h"
#include "PacmanGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APacmanCharacter::APacmanCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Camera Setup
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SocketOffset = FVector(0, 35, 0);
	SpringArm->TargetOffset = FVector(0, 0, 55);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->AttachParent = GetRootComponent();

	PlayerCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	PlayerCameraComponent->AttachParent = SpringArm;

	bIsPoweredUp = false;

	static ConstructorHelpers::FClassFinder<ACharacter> PlayerPawnBPClass(TEXT("Blueprint'/Game/Pacman/BP_Pacman.BP_Pacman_C'"));
	if (PlayerPawnBPClass.Class) {
		PacmanBlueprint = (UClass*)PlayerPawnBPClass.Class;
	}

}

// Called when the game starts or when spawned
void APacmanCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APacmanCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void APacmanCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	check(InputComponent);
	//Movement
	InputComponent->BindAxis("MoveForward", this, &APacmanCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APacmanCharacter::MoveRight);
}

void APacmanCharacter::MoveForward(float Val) {
	if (Controller && Val != 0.0f) 
	{
		// Limit pitch when walking or falling
		const bool bLimitRotation = (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling());
		const FRotator Rotation = bLimitRotation ? GetActorRotation() : Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);

		AddMovementInput(Direction, Val);
	}
}

void APacmanCharacter::MoveRight(float Val) {
	if (Controller && Val != 0.f)
	{
		const FRotator Rotation = GetActorRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Val);
	}
}

void APacmanCharacter::Respawn()
{
	APacmanController* PlayerController = Cast<APacmanController>(GetController());
	APacmanGameMode* GameMode = Cast<APacmanGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	PlayerController->UnPossess();
	AActor* StartSpot = PlayerController->StartSpot.Get();
	
	FVector SpawnLocation = StartSpot->GetActorLocation();
	FRotator SpawnRotation = StartSpot->GetActorRotation();

	UWorld* const World = GetWorld();
	if (World)
	{
		APacmanCharacter* PacmanRespawned = (APacmanCharacter*)World->SpawnActor<ACharacter>(PacmanBlueprint, SpawnLocation, SpawnRotation);
		PlayerController->Possess(PacmanRespawned);
	}

	Destroy();
}