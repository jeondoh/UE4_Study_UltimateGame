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

	RunningTime = 0.f;

	A = 0.f;
	B = 0.f;
	C = 0.f;
	D = 0.f;
}

// Called when the game starts or when spawned
void AFloaterActor::BeginPlay()
{
	Super::BeginPlay();

	float InitialX = FMath::FRandRange(-500, 500);
	float InitialY = FMath::FRandRange(-500, 500);
	float InitialZ = FMath::FRandRange(0, 500);

	InitLocation.X = InitialX;
	InitLocation.Y = InitialY;
	InitLocation.Z = InitialZ;

	PlaceLocation = GetActorLocation();

	if(bInitializerFloaterLocations)
	{
		SetActorLocation(InitLocation);		
	}

	BaseZLocation = PlaceLocation.Z;
}

// Called every frame
void AFloaterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bShouldFloat)
	{
		FVector NewLocation = GetActorLocation();

		NewLocation.Z = BaseZLocation + A * FMath::Sin(B * RunningTime - C) + D;
		
		SetActorLocation(NewLocation);
		RunningTime += DeltaTime;
	}
}

