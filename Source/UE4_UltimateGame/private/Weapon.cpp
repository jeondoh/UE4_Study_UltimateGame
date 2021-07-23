// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AWeapon::AWeapon()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkelatalMesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());
	
	bWeaponParticle = false;
	WeaponStat = EWeaponStat::EWS_PickUp;
}

void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if((WeaponStat == EWeaponStat::EWS_PickUp) && OtherActor)
	{
		AMainChar* Player = Cast<AMainChar>(OtherActor);
		if(Player)
		{
			Player->SetActiveOverlappingItem(this);
		}
	}
}

void AWeapon::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	if(OtherActor)
	{
		AMainChar* Player = Cast<AMainChar>(OtherActor);
		if(Player)
		{
			Player->SetActiveOverlappingItem(nullptr);
		}
	}
}

void AWeapon::Equip(AMainChar* Player)
{
	if(Player)
	{
		// Ãæµ¹Ã³¸®
		SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		SkeletalMesh->SetSimulatePhysics(false);

		// ¼ÒÄÏ °¡Á®¿È
		const USkeletalMeshSocket* RightHandSocket = Player->GetMesh()->GetSocketByName("RightHandSocket");
		if(RightHandSocket)
		{
			RightHandSocket->AttachActor(this, Player->GetMesh());
			bRotate = false;

			Player->SetEquippedWeapon(this);
			Player->SetActiveOverlappingItem(nullptr);
		}
		// °Ë È¹µæ½Ã »ç¿îµå
		if(OnEquipSound)
		{
			UGameplayStatics::PlaySound2D(this, OnEquipSound);			
		}
		if(!bWeaponParticle)
		{
			IdleParticleComp->Deactivate();
		}
		
	}
}


