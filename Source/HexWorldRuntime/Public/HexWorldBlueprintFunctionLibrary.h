// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexWorldServer.h"
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

	UFUNCTION(BlueprintCallable, Category="HexWorld")
    UHexWorldServer* ConnectToServer(FString ServerAddress);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UHexWorldServer* HexWorldServer;

};
