// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UE4_ULTIMATEGAME_API UMyObject : public UObject
{
	GENERATED_BODY()
public:
	UMyObject();

	UPROPERTY(BlueprintReadWrite, Category="Myvariables")
	float MyFloat;

	UFUNCTION(BlueprintCallable, Category="MyFunctions")
	void MyFunction();
};
