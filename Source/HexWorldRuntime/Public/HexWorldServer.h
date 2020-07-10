// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "hex_client.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HexWorldServer.generated.h"
/**
 * 
 */
UCLASS()
class HEXWORLDRUNTIME_API UHexWorldServer : public UObject
{
	GENERATED_BODY()

	public:
	UHexWorldServer();

	explicit UHexWorldServer(const FObjectInitializer& ObjectInitializer)
		: UObject(ObjectInitializer)
	{
	}

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Hexworld")
	FString ServerAddress;

	bool ConnectToBackend();
	
private:
	HexagonClient* HexagonClient;	
};
