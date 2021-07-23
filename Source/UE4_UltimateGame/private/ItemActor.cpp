// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActor.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AItemActor::AItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionVolumn = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolumn"));
	RootComponent = CollisionVolumn;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	IdleParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	IdleParticleComp->SetupAttachment(GetRootComponent());

	bRotate = false;
	RotationRate = 60.f;
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionVolumn->OnComponentBeginOverlap.AddDynamic(this, &AItemActor::OnOverlapBegin);
	CollisionVolumn->OnComponentEndOverlap.AddDynamic(this, &AItemActor::OnOverlapEnd);
}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bRotate)
	{
		FRotator Rotation = GetActorRotation();
		Rotation.Yaw += DeltaTime * RotationRate;
		SetActorRotation(Rotation);
	}
}

void AItemActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Super::OnOverlapBegin()"));

	if(OverlapParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OverlapParticle, GetActorLocation(), FRotator(0.f), true);
	}
	if(OverlapSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), OverlapSound);
	}
}

void AItemActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Super::OnOverlapEnd()"));
}

