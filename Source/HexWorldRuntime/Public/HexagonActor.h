#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexagonActor.generated.h"

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

USTRUCT(BlueprintType)
struct FAxialCoordinates {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Hexagon World")
	int32 Q;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Hexagon World")
	int32 R;

	FAxialCoordinates(int32 Q, int32 R): Q(Q), R(R)	{}
	FAxialCoordinates(): Q(0), R(0) {}
	
};

USTRUCT(BlueprintType)
struct FPixelPoint {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Hexagon World")
	int32 X;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Hexagon World")
	int32 Y;

	FPixelPoint(int64_t X, int64_t Y): X(X), Y(Y) {}
	FPixelPoint() {}; 
	
};

UCLASS(BlueprintType)
class HEXWORLDRUNTIME_API AHexagonActor final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexagonActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	UStaticMeshComponent* HexagonPlain;

	UPROPERTY()
	UStaticMesh* HexMesh;

	UFUNCTION(BlueprintCallable, Category="HexWorld")
	void TransformAndSpawn(FHexagonCoordinates HexCoord);

private:
};
