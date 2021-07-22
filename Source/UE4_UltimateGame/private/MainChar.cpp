// Fill out your copyright notice in the Description page of Project Settings.


#include "MainChar.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AMainChar::AMainChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Camera Boom (pulls towards the player if there's a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f; // Camera follows at this distance
	CameraBoom->bUsePawnControlRotation = true; // Rotate arm based on controller

	GetCapsuleComponent()->SetCapsuleSize(48.f, 105.f);

	// Create follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match
	// the controller orientation
	FollowCamera->bUsePawnControlRotation = false;
	// Set our turn rates for input
	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;

	// 회전과 함께 캐릭터를 회전하지 않음
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// Configure charachter movement
	// 키를 누른 방향대로 움직임
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the Direction of input
	// 방향을 바꿀때 얼마나 회전할지
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.0f); // at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 650.f;
	GetCharacterMovement()->AirControl = 0.2f;

	MaxHealth = 100.f;
	Health = 65.f;
	MaxStamina = 150.f;
	Stamina = 120.f;
	Coins = 0;

	RunningSpeed = 650.f;
	SprintingSpeed = 950.f;

	bShiftKeyDown = false;

	// init ENUM
	MovementStatus = EMovementStatus::EMS_Normal;
	StaminaStatus = EStaminaStatus::ESS_Normal;
	
	StaminaDrainRate = 25.f;
	MinSprintStamina = 50.f;
}

// Called when the game starts or when spawned
void AMainChar::BeginPlay()
{
	Super::BeginPlay();

	UKismetSystemLibrary::DrawDebugSphere(this, GetActorLocation() + FVector(0,0,175.f),
		25.f, 8, FLinearColor::Green, 10.f, 5.f);
	
}

// Called every frame
void AMainChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float DeltaStamina = StaminaDrainRate * DeltaTime;
	switch (StaminaStatus)
	{
		case EStaminaStatus::ESS_Normal:
			if (bShiftKeyDown)
			{
				if(Stamina - DeltaStamina <= MinSprintStamina)
				{
					SetStatminaStatus(EStaminaStatus::ESS_BelowMinimum);
				}
				Stamina -= DeltaStamina;
				SetMovementStatus(EMovementStatus::EMS_Sprinting);
			}
			else // shift key up
			{	
				if(Stamina + DeltaStamina >= MaxStamina)
				{
					Stamina = MaxStamina;
				}
				else
				{
					Stamina += DeltaStamina;
				}
				SetMovementStatus(EMovementStatus::EMS_Normal);
			}
			break;
		case EStaminaStatus::ESS_BelowMinimum:
			if(bShiftKeyDown)
			{
				if(Stamina - DeltaStamina <= 0.f)
				{
					SetStatminaStatus(EStaminaStatus::ESS_Exhausted);
					Stamina = 0;
					SetMovementStatus(EMovementStatus::EMS_Normal);
				}
				else
				{
					Stamina -= DeltaStamina;
					SetMovementStatus(EMovementStatus::EMS_Sprinting);
				}
			}
			else // shift key up
			{
				if(Stamina + DeltaStamina >= MinSprintStamina)
				{
					SetStatminaStatus(EStaminaStatus::ESS_Normal);
				}
				Stamina += DeltaStamina;
				SetMovementStatus(EMovementStatus::EMS_Normal);
			}
			break;
		case EStaminaStatus::ESS_Exhausted:
			if(bShiftKeyDown)
			{
				Stamina = 0.f;		
			}
			else // shift key up
			{
				SetStatminaStatus(EStaminaStatus::ESS_ExhaustedRecovering);
				Stamina += DeltaStamina;
			}
			SetMovementStatus(EMovementStatus::EMS_Normal);
			break;
		case EStaminaStatus::ESS_ExhaustedRecovering:
			if(Stamina + DeltaStamina >= MinSprintStamina)
			{
				SetStatminaStatus(EStaminaStatus::ESS_Normal);
			}
			Stamina += DeltaStamina;
			SetMovementStatus(EMovementStatus::EMS_Normal);
			break;
		default:
			;
	}
}

// Called to bind functionality to input
void AMainChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMainChar::ShiftKeyDown);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMainChar::ShiftKeyUp);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainChar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainChar::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("TurnRate", this, &AMainChar::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMainChar::LookUpRate);
}

void AMainChar::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMainChar::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AMainChar::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMainChar::LookUpRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMainChar::ShowPickUpLocations()
{
	for (int32 i=0; i<PickUpLocations.Num(); i++)
	{
		// 위치 디버깅 -> 코인을 먹은 자리에 Sphere 형태로 나타남
		UKismetSystemLibrary::DrawDebugSphere(this, PickUpLocations[i],
				25.f, 8, FLinearColor::Green, 10.f, 5.f);		
	}
}

void AMainChar::SetMovementStatus(EMovementStatus Status)
{
	MovementStatus = Status;
	if(MovementStatus == EMovementStatus::EMS_Sprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	}
}

void AMainChar::ShiftKeyDown()
{
	bShiftKeyDown = true;
}

void AMainChar::ShiftKeyUp()
{
	bShiftKeyDown = false;
}

void AMainChar::DecrementHealth(float Amount)
{
	Health -= Amount;
	if(Health - Amount <= 0.f)
	{
		
		Die();
	}
}

void AMainChar::IncrementCoins(int32 Amount)
{
	Coins += Amount;
}

void AMainChar::Die()
{
	
}

