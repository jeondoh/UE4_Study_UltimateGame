// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"

#include "Collider.generated.h"

UCLASS()
class UE4_ULTIMATEGAME_API ACollider : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UPawnMovementComponent* GetMovementComponent() const override;
	
	UPROPERTY(VisibleAnywhere, Category="Movement")
	class UColliderMovementComponent* OurMovementComponent;

	UPROPERTY(VisibleAnywhere, Category="Mesh")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category="Mesh")
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, Category="Mesh")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category="Mesh")
	USpringArmComponent* SpringArmComponent;
	
	FORCEINLINE UStaticMeshComponent* GetMeshComponent(){return MeshComponent;}
	FORCEINLINE void SetMeshComponent(UStaticMeshComponent* Component){MeshComponent = Component;}

	FORCEINLINE USphereComponent* GetSphereComponent(){return SphereComponent;}
	FORCEINLINE void SetSphereComponent(USphereComponent* Component){SphereComponent = Component;}

	FORCEINLINE UCameraComponent* GetCamera() {return Camera;}
	FORCEINLINE void SetCamera(UCameraComponent* Component){Camera = Component;}

	FORCEINLINE USpringArmComponent* GetSpringArmComponent() {return SpringArmComponent;}
	FORCEINLINE void SetSpringArmComponent(USpringArmComponent* Component) {SpringArmComponent = Component;}

private:
	void MoveForward(float Value);
	void MoveRight(float Value);

	void CameraYaw(float AxisValue);
	void CameraPitch(float AxisValue);

	FVector2D CameraInput;
};
