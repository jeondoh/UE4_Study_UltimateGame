// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "MainChar.h"

#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponStat : uint8
{
	EWS_PickUp	 UMETA(DisplayName="PickUp"),
	EWS_Equipped UMETA(DisplayName="Equipped"),

	EWS_MAX UMETA(DisplayName="DefaultMax")
};

/**
 * 
 */
UCLASS()
class UE4_ULTIMATEGAME_API AWeapon : public AItemActor
{
	GENERATED_BODY()
public:
	AWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Item")
	EWeaponStat WeaponStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item | Particles")
	bool bWeaponParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item | Sound")
	USoundCue* OnEquipSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="SkeletalMesh")
	USkeletalMeshComponent* SkeletalMesh;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	void Equip(AMainChar* Player);

	FORCEINLINE void SetWeaponStat(EWeaponStat Stat){WeaponStat = Stat;}
	FORCEINLINE EWeaponStat GetWeaponStat(){return WeaponStat;}
};
