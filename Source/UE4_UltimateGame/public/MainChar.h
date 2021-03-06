// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MainPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Sound/SoundCue.h"

#include "MainChar.generated.h"

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_Normal UMETA(DisplayName = "Normal"),
	EMS_Sprinting UMETA(DisplayName = "Sprinting"), 
	EMS_Dead UMETA(DisplayName = "Dead"),
	
	EMS_Max UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EStaminaStatus : uint8
{
	ESS_Normal UMETA(DisplayName = "Normal"),
	ESS_BelowMinimum UMETA(DisplayName = "BelowMinimum"),
	ESS_Exhausted UMETA(DisplayName = "Exhausted"),
	ESS_ExhaustedRecovering UMETA(DisplayName = "ExhaustedRecovering"),
	ESS_MAX UMETA(DisplayName="DefaultMax")
};

UCLASS()
class UE4_ULTIMATEGAME_API AMainChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainChar();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	bool bHasCombatTarget;

	FORCEINLINE void SetHasCombatTarget(bool HasTarget){bHasCombatTarget = HasTarget;}
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Combat")
	FVector CombatTargetLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Controller")
	AMainPlayerController* MainPlayerController;

	TArray<FVector> PickUpLocations;

	float InterpSpeed;

	bool bInterpToEnemy;

	void SetInterpToEnemy(bool Interp);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	class AEnemy* CombatTarget;

	FORCEINLINE void SetCombatTarget(AEnemy* Target) {CombatTarget = Target;}

	FRotator GetLookAtRotationYaw(FVector Target);
	
	// -------------------------------------------------------------------- //
	// Player Movement
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Enums")
	EMovementStatus MovementStatus;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Running")
	float RunningSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Running")
	float SprintingSpeed;

	bool bShiftKeyDown;

	// Player Movement END
	// -------------------------------------------------------------------- //

	// -------------------------------------------------------------------- //
	// Player Stamina
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Enums")
	EStaminaStatus StaminaStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Movement")
	float StaminaDrainRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Movement")
	float MinSprintStamina;
	
	FORCEINLINE void SetStatminaStatus(EStaminaStatus Status){StaminaStatus = Status;}
	
	// Player Stamina END
	// -------------------------------------------------------------------- //

	// Camera boom positioning the Camera Behind the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta =(AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	// Follow Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta =(AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	// Base turn rates to scale turning functions for the camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera");
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera");
	float BaseLookUpRate;

	// -------------------------------------------------------------------- //
	// Player Stats
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Stats")
	float MaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Stats")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Stats")
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Stats")
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Stats")
	int32 Coins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	USoundCue* HitSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called for forwards/backwards input
	void MoveForward(float Value);

	// Called for side to side input
	void MoveRight(float Value);

	// Called via input to turn at a given rate
	void TurnAtRate(float Rate);

	// Called via input to look up/down at a given rate
	void LookUpRate(float Rate);

	virtual void Jump() override;

	bool bLMBDown;
	void LMBDown();
	void LMBUp();

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const{return CameraBoom;}
	FORCEINLINE class UCameraComponent* GetFollowCamera() const{return FollowCamera;}

	UFUNCTION(BlueprintCallable)
	void ShowPickUpLocations();
	
	// Set movement status and running speed
	void SetMovementStatus(EMovementStatus Status);

	void ShiftKeyDown();

	void ShiftKeyUp();
	
	// -------------------------------------------------------------------- //
	// Player Stats
	void DecrementHealth(float Amount);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent,
		class AController * EventInstigator, AActor * DamageCauser) override;

	void IncrementCoins(int32 Amount);

	void Die();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Anims")
	bool bAttacking;

	void Attack();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Anims")
	UAnimMontage* CombatMontage;

	UFUNCTION(BlueprintCallable)
	void PlaySwingSound();
	
	UFUNCTION(BlueprintCallable)
	void DeathEnd();

	// -------------------------------------------------------------------- //
	// Player Weapon
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Items")
	class AWeapon* EquippedWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Items")
	class AItemActor* ActivateOverlappingItem;

	FORCEINLINE AWeapon* GetEquippedWeapon(){return EquippedWeapon;}
	FORCEINLINE void SetEquippedWeapon(AWeapon* WeaponToSet);
	FORCEINLINE void SetActiveOverlappingItem(AItemActor* AItemToSet){ActivateOverlappingItem = AItemToSet;}

};
