// Fill out your copyright notice in the Description page of Project Settings.

#include "Pacman.h"
#include "PacmanConsumable.h"


// Sets default values
APacmanConsumable::APacmanConsumable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Make root component a sphere that deals with physics
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Root Component"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(10.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Destructible"));

	//Mesh
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere Mesh"));
	MeshComponent->AttachTo(RootComponent);

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
