// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ObjectMacros.h"

#include "Hexagon.generated.h"

USTRUCT(Blueprintable)
struct FHexagonCoordinates {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Hexagon World")
    int32 X;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Hexagon World")
	int32 Y;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Hexagon World")
	int32 Z;

	FHexagonCoordinates(int x_, int y_, int z_):X(x_), Y(y_), Z(z_) {};
	FHexagonCoordinates() {};
};

struct AxialCoordinates {
	int32_t Q;
	int32_t R;

	AxialCoordinates(int32_t Q_, int32_t R_) {
		Q = Q_;
		R = R_;
	}
};

struct PixelPoint {
	int64_t X;
	int64_t Y;

	PixelPoint(int64_t X_, int64_t Y_)
	{
		X = X_;
		Y = Y_;
	}
};

UCLASS(BlueprintType)
class HEXWORLDRUNTIME_API AHexagon final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexagon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable, Category="HexWorld")
	void TransformAndSpawn(FHexagonCoordinates HexCoord);

private:
	UStaticMeshComponent* HexagonPlain;
};
