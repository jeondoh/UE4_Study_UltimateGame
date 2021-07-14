// Fill out your copyright notice in the Description page of Project Settings.


#include "FloaterActor.h"

// Sets default values
AFloaterActor::AFloaterActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CustomStaticMesh"));

	InitLocation = FVector(0.0f);
	PlaceLocation = FVector(0.0f);
	WorldOrigin = FVector(0.0f);

	InitialDirection = FVector(0.0f);
	
	bInitializerFloaterLocations = false;
	bShouldFloat = false;

	InitialForce = FVector(2000000.f, 0.0f, 0.0f);
	InitialTorque = FVector(2000000.f, 0.0f, 0.0f);
}

// Called when the game starts or when spawned
void AFloaterActor::BeginPlay()
{
	Super::BeginPlay();

	PlaceLocation = GetActorLocation();

	if(bInitializerFloaterLocations)
	{
		SetActorLocation(InitLocation);		
	}
	
	StaticMesh->AddForce(InitialForce);
	StaticMesh->AddTorqueInRadians(InitialTorque);
}

// Called every frame
void AFloaterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bShouldFloat)
	{
		FHitResult HitResult;
		AddActorLocalOffset(InitialDirection, true, &HitResult);

		FVector HitLocation = HitResult.Location;
	}
	FRotator Rotation = FRotator(0.0f, 0.0f, 1.0f);
	
	// AddActorLocalRotation(Rotation);
}

