// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "hex_lib.h"
#include "CoreMinimal.h"
#include "Hexagon.h"
#include "hex_client.h"


#include "HexWorldServer.generated.h"
/**
 * 
 */
UCLASS(BlueprintType)
class HEXWORLDRUNTIME_API UHexWorldServer final : public UObject
{
	GENERATED_BODY()

	public:
	UHexWorldServer()
	{
		
	};


	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Hexworld")
	FString ServerAddress;

	UFUNCTION(BlueprintCallable, Category="HexWorld")
	// TODO use Unreal container class instead of vector (garbage collection)
	TArray<FHexagonCoordinates> GetHexagonRing() const;

	UFUNCTION(BlueprintCallable, Category="HexWorld")
	bool ConnectToBackend();

private:
	HexagonClient* HexagonClient;
};
