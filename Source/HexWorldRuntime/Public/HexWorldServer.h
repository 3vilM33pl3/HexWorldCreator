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
class HEXWORLDRUNTIME_API AHexWorldServer final : public AActor
{
	GENERATED_BODY()

	public:
	AHexWorldServer()
	{
		HexagonPlain = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HexagonPlain"));
	};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Hexworld")
	FString ServerAddress;

	UFUNCTION(BlueprintCallable, Category="HexWorld")
	bool GetHexagonRing();

	UFUNCTION(BlueprintCallable, Category="HexWorld")
	bool ConnectToBackend();

	UStaticMeshComponent* HexagonPlain;
	void PlaceHexagon(Hexagon *Hex);

private:
	HexagonClient* HexagonClient;
};
