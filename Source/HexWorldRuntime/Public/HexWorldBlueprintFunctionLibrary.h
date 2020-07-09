// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "hex_client.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/ObjectMacros.h"

#include "HexWorldBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class HEXWORLDRUNTIME_API UHexWorldBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	public:

	// UFUNCTION(BlueprintCallable, Category="HexWorld")
	// static 
	
	UFUNCTION(BlueprintCallable, Category="HexWorld")
	static bool ConnectToBackend();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Hexworld")
	FString ServerAddress;

	private:
	HexagonClient* HexagonClient;
	
};
