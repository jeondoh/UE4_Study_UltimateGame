// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UE4_ULTIMATEGAME_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	// Reference to the UMG Asset in the editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Widgets")
	TSubclassOf<class UUserWidget> HUDOverlayAsset;

	// 위젯 담을 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Widgets")
	UUserWidget* HUDOverlay;

	// Enemy HealthBar
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Widgets")
	TSubclassOf<class UUserWidget> WEnemyHealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Widgets")
	UUserWidget* EnemyHealthBar;

	bool bEnemyHealthBarVisible;

	void DisplayEnemyHealthBar();
	void RemoveEnemyHealthBar();

	FVector EnemyLocation;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
};
