// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hexagon.h"
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
	UHexWorldBlueprintFunctionLibrary();
	
	UFUNCTION(BlueprintCallable, Category="Hexagon World")
    static bool ConnectToServer(AHexWorldServer* Server);

	static PixelPoint ConvertAxialToPixelCoordsLocal(const struct AxialCoordinates &Ac, const int Size)
	{
		const double x = Size * (3.0 / 2.0 * Ac.Q);
		const double y = Size * (sqrt(3.0)/2.0 * Ac.Q + sqrt(3.0) * Ac.R);
		return PixelPoint(x, y);
	}

	UFUNCTION(BlueprintCallable, Category="Hexagon World")
	static FTransform ConvertCubeToTransformCoordinates(const struct FHexagonCoordinates FHC, const int Size)
	{
		const double x = Size * (3.0 / 2.0 * FHC.X);
		const double y = Size * (sqrt(3.0)/2.0 * FHC.Z + sqrt(3.0) * FHC.X);
		return FTransform(FVector(x, y, 0));
	}

};
