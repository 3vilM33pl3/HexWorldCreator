// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexagonActor.h"
#include "hex_client.h"
#include "Containers/CircularQueue.h"



#include "HexWorldClient.generated.h"
/**
 * 
 */
UCLASS(BlueprintType)
class HEXWORLDRUNTIME_API UHexWorldClient final : public UObject
{
	GENERATED_BODY()

	public:
	UHexWorldClient()
	{
		
	};


	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Hexworld")
	FString ServerAddress = "hexcloud-j6feiuh7aa-ue.a.run.app:443";

	UFUNCTION(BlueprintCallable, Category="HexWorld")
	// TODO use Unreal container class instead of vector (garbage collection)
	TArray<FHexagonCoordinates> GetHexagonRing(FAxialCoordinates Center) const;

	UFUNCTION(BlueprintCallable, Category="HexWorld")
	bool ConnectToBackend();

	TCircularQueue<FHexagonCoordinates>* HexCoordData = new TCircularQueue<FHexagonCoordinates>(12);

private:
	HexagonClient* HexagonClient;
};
