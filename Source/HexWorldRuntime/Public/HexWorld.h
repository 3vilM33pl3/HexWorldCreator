// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexWorld.generated.h"

/**
 * 
 */
UCLASS()
class HEXWORLDRUNTIME_API UHexWorld : public UObject
{
	GENERATED_BODY()

	public:
	bool ConnectToBackend();
	
};
