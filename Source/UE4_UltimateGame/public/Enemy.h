// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AIController.h"
#include "MainChar.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Sound/SoundCue.h"

#include "Enemy.generated.h"

UENUM(BlueprintType)
enum class EEnemyMovementStatus : uint8
{
	EMS_Idle			UMETA(DisplayName="Idle"),
	EMS_MoveToTarget	UMETA(DisplayName="MoveToTarget"),
	EMS_Attacking		UMETA(DisplayName="Attacking"),
	EMS_Dead			UMETA(DisplayName="Dead"),
	
	EMS_MAX				UMETA(DisplayName="DefaultMAX")
};

UCLASS()
class UE4_ULTIMATEGAME_API AEnemy : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AEnemy();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
	USphereComponent* AgroSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
	USphereComponent* CombatSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
	AAIController* AIController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement")
	EEnemyMovementStatus EnemyMovementStatus;

	FORCEINLINE EEnemyMovementStatus GetEnemyMovementStatus(){return EnemyMovementStatus;}
	FORCEINLINE void SetEnemyMovementStatus(EEnemyMovementStatus Status){EnemyMovementStatus = Status;}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	float Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	float MaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	USoundCue* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	USoundCue* SwingSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Combat")
	UBoxComponent* CombatCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	UAnimMontage* CombatMontage;

	UFUNCTION(BlueprintCallable)
	void ActivateCollision();

	UFUNCTION(BlueprintCallable)
	void DeActivateCollision();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	bool bAttacking;

	UFUNCTION()
	void Attack();
	
	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	FTimerHandle AttackTimer;

	FTimerHandle DeathTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	float DeathDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	float AttackMinTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	float AttackMaxTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	TSubclassOf<UDamageType> DamageTypeClass;
	
	FRotator GetLookAtRotationYaw(FVector Target);

	float InterpSpeed;
	
	bool bInterpToPlayer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual void AgroShpereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION()
	virtual void AgroShpereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	virtual void CombatSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION()
	virtual void CombatSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void CombatOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void CombatOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void MoveToTarget(AMainChar* Target);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="AI")
	bool bOverlappingCombatSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="AI")
	AMainChar* CombatTarget;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent,
		class AController * EventInstigator, AActor * DamageCauser) override;

	void Die();

	UFUNCTION(BlueprintCallable)
	void DeathEnd();

	bool Alive();

	void Disappear();
};
