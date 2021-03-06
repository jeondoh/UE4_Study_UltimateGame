// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp.h"

#include "MainChar.h"

APickUp::APickUp()
{
	CoinCount = 1;
}

void APickUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	UE_LOG(LogTemp, Warning, TEXT("APickUp::OnOverlapBegin()"));

	if(OtherActor)
	{
		AMainChar* MainPlayer = Cast<AMainChar>(OtherActor);
		if(MainPlayer)
		{
			MainPlayer->IncrementCoins(CoinCount);
			MainPlayer->PickUpLocations.Add(GetActorLocation());
			Destroy();
		}
	}
}

void APickUp::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	UE_LOG(LogTemp, Warning, TEXT("APickUp::OnOverlapEnd()"));
}
