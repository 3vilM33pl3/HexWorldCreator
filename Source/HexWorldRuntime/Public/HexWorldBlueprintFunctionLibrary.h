// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexagonActor.h"
#include "HexWorldClient.h"
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
    static bool ConnectToServer(UHexWorldClient* Server);

	UFUNCTION(BlueprintCallable, Category="Hexagon World")
	static FPixelPoint ConvertAxialToPixelCoords(const struct FAxialCoordinates &Ac, const int Size, const bool FlatTop = true) 
	{
		double x = Size * (3.0 / 2.0 * Ac.Q);
		double y = Size * (sqrt(3.0)/2.0 * Ac.Q + sqrt(3.0) * Ac.R);
		return FPixelPoint(x, y);
	}

	UFUNCTION(BlueprintCallable, Category="Hexagon World")
	static FAxialCoordinates ConvertPixelToAxialCoords(float X, float Y, const int Size = 1500, const bool FlatTop = true)
	{
		if(FlatTop)
		{
			double Q = (2.0/3.0 * X) / Size;
			double R = (-1.0/3.0 * X + sqrt(3.0)/3.0 * Y) / Size;
			return FAxialCoordinates(Q,R);
		}
		else
		{
			double Q = (sqrt(3.0)/3.0 * X - 1.0/3.0 * Y) / Size;
			double R = (2.0 / 3.0 * Y) / Size;
			return FAxialCoordinates(Q, R);
		}
	}
	

	UFUNCTION(BlueprintCallable, Category="Hexagon World")
	static FTransform ConvertCubeToTransformCoordinates(const struct FHexagonCoordinates FHC, const int Size)
	{
		const double x = Size * (3.0 / 2.0 * FHC.X);
		const double y = Size * (sqrt(3.0)/2.0 * FHC.Z + sqrt(3.0) * FHC.X);
		return FTransform(FVector(x, y, 0));
	}

};
