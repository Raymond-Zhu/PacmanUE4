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

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	//Spring Arm. Mainly used for setting up the Camera. The "spring" is disabled in blueprint. TODO: Find a better way to handle the Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	//Camera Setup 
	PlayerCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	PlayerCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	PlayerCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//Creates Particle System
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Powered Up Particles"));
	ParticleSystem->AttachTo(RootComponent); 
	ParticleSystem->bAutoActivate = false;
	ParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));

	//Initializes PowerUp to false
	bIsPoweredUp = false;

	//Object that holds the Blueprint related to this Character class. Useful for respawning.
	static ConstructorHelpers::FClassFinder<ACharacter> PlayerPawnBPClass(TEXT("Blueprint'/Game/Pacman/BP_Pacman.BP_Pacman_C'"));
	if (PlayerPawnBPClass.Class) {
		PacmanBlueprint = (UClass*)PlayerPawnBPClass.Class;
	}

	//Initializes Value to -1 for moving left initially
	Value = -1.0f;
	
	if (Controller != NULL) 
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
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
	Super::Tick(DeltaTime);
	//Auto walks every tick. TODO: Make it more like original Pacman and more smooth.
	AddMovementInput(Direction, 2*Value);
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
	if ((Controller != NULL) && (Val != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		//AddMovementInput(Direction, Val);
		Value = Val;
	}
}

void APacmanCharacter::MoveRight(float Val) {
	if ((Controller != NULL) && (Val != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		Value = Val;
		// add movement in that direction
		//AddMovementInput(Direction, Val);
	}
} 

void APacmanCharacter::ParticleToggle()
{
	//Checks if Particle System and it's Template exists
	if (ParticleSystem && ParticleSystem->Template)
	{
		//Activates the particles if Pacman is powered up.
		if (bIsPoweredUp)
		{
			ParticleSystem->ActivateSystem();
		}
		//Deactivates the particles if he isn't. This happens at the end of the particle timer.
		else
		{
			ParticleSystem->DeactivateSystem();
		}
	}
}

void APacmanCharacter::PowerUp()
{
	//If Pacman wasn't previously powered up, Pacman becomes powered up and the Fire particles are activated.
	if (bIsPoweredUp == false)
	{
		bIsPoweredUp = true;
		ParticleToggle();
	}
	//Sets a timer for the particles to last 5 seconds
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APacmanCharacter::PowerDown, 5.0f, false);
}

void APacmanCharacter::PowerDown()
{
	//Powers Pacman down and deactivate the particles only if he was previously powered up(Just in case)
	if (bIsPoweredUp)
	{
		bIsPoweredUp = false;
		ParticleToggle();
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
