// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

#include "MainChar.generated.h"

UCLASS()
class UE4_ULTIMATEGAME_API AMainChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainChar();

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
	
};
