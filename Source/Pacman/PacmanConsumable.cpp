// Fill out your copyright notice in the Description page of Project Settings.

#include "Pacman.h"
#include "PacmanConsumable.h"


// Sets default values
APacmanConsumable::APacmanConsumable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Make root component a sphere that deals with physics
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Root Component"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(60.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Destructible"));
	SphereComponent->OnComponentHit.AddDynamic(this, &APacmanConsumable::OnHit);

	SphereComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	SphereComponent->CanCharacterStepUpOn = ECB_No;	
}

// Called when the game starts or when spawned
void APacmanConsumable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APacmanConsumable::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void APacmanConsumable::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
}
