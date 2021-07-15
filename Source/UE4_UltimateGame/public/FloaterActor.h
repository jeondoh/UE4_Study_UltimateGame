// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloaterActor.generated.h"

UCLASS()
class UE4_ULTIMATEGAME_API AFloaterActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloaterActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="ActorMeshComponents")
	UStaticMeshComponent* StaticMesh;

	// Location used by SetActorLocation when beginPlay is called
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Floater Variables")
	FVector InitLocation;

	// Location of the Actor when dragged in from the editor
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="Floater Variables")
	FVector PlaceLocation;

	UPROPERTY(VisibleDefaultsOnly ,BlueprintReadOnly, Category="Floater Variables")
	FVector WorldOrigin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Floater Variables")
	FVector InitialDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Floater Variables")
	bool bShouldFloat;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Floater Variables")
	bool bInitializerFloaterLocations;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Floater Variables")
	FVector InitialForce;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Floater Variables")
	FVector InitialTorque;

	// Amplitude > 진동범위
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Floater Variables")
	float A;
	// Period > 진동주기
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Floater Variables")
	float B;
	// Phase Shift
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Floater Variables")
	float C;
	// Vertical Shift > 파동위치
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Floater Variables")
	float D;
	
private:
	float RunningTime;

	float BaseZLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
