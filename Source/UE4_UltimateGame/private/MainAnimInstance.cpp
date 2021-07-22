// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"

#include "MainChar.h"
#include "GameFramework/PawnMovementComponent.h"

void UMainAnimInstance::NativeInitializeAnimation()
{
	if(Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if(Pawn)
		{
			MainPlayer = Cast<AMainChar>(Pawn);
		}
	}
}

void UMainAnimInstance::UpdateAnimationProperties()
{
	if(Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}

	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LayeralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = LayeralSpeed.Size();

		bIsInAir = Pawn->GetMovementComponent()->IsFalling();

		if(MainPlayer == nullptr)
		{
			MainPlayer = Cast<AMainChar>(Pawn);
		}
	}
}
