// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "hex_client.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HexWorldServer.generated.h"
/**
 * 
 */
UCLASS(BlueprintType)
class HEXWORLDRUNTIME_API UHexWorldServer : public UObject
{
	GENERATED_BODY()

	public:
	UHexWorldServer(){};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Hexworld")
	FString ServerAddress;

	UFUNCTION(BlueprintCallable, Category="HexWorld")
	bool GetHexagonRing() const;

	UFUNCTION(BlueprintCallable, Category="HexWorld")
	bool ConnectToBackend();


private:
	HexagonClient* HexagonClient;	
};
