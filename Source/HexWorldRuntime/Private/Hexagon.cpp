// Fill out your copyright notice in the Description page of Project Settings.


#include "Hexagon.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HexWorldBlueprintFunctionLibrary.h"
#include "Interfaces/IPluginManager.h"

// Sets default values
AHexagon::AHexagon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HexagonPlain = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HexagonPlain"));

}

// Called when the game starts or when spawned
void AHexagon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHexagon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHexagon::TransformAndSpawn(FHexagonCoordinates HexCoord) 
{

	const PixelPoint Px = UHexWorldBlueprintFunctionLibrary::ConvertAxialToPixelCoordsLocal(AxialCoordinates(HexCoord.X, HexCoord.Z), 1500);
	const FVector ObjectLocation(Px.X, Px.Y, 0);
	const FRotator ObjectRotation(0, 0, 0); //in degrees

	SetActorTransform(FTransform(ObjectLocation));

	UStaticMesh* HexAsset = Cast<UStaticMesh>(StaticLoadObject( UStaticMesh::StaticClass(), nullptr, *FName("/HexWorldCreator/HexagonBase.HexagonBase").ToString() ));

	// HexagonPlain->SetupAttachment(RootComponent);
	// HexagonPlain->bHiddenInGame = false;
	// HexagonPlain->SetMobility(EComponentMobility::Stationary);
	HexagonPlain->SetStaticMesh(HexAsset);

}