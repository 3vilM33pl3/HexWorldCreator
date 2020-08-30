// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonActor.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HexWorldBlueprintFunctionLibrary.h"
#include "Interfaces/IPluginManager.h"

// Sets default values
AHexagonActor::AHexagonActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HexagonPlain = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HexagonPlain"));
	RootComponent = HexagonPlain;

	HexMesh = Cast<UStaticMesh>(StaticLoadObject( UStaticMesh::StaticClass(), nullptr, *FName("/HexWorldCreator/HexagonBase.HexagonBase").ToString() ));
	// static ConstructorHelpers::FObjectFinder<UStaticMesh> HexMesh(TEXT("/HexWorldCreator/HexagonBase.HexagonBase"));
	HexagonPlain->SetStaticMesh(HexMesh);
	
}

// Called when the game starts or when spawned
void AHexagonActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHexagonActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHexagonActor::TransformAndSpawn(FHexagonCoordinates Hex) 
{

	const FPixelPoint Px = UHexWorldBlueprintFunctionLibrary::ConvertAxialToPixelCoords(FAxialCoordinates(Hex.X, Hex.Z), 1500);
	const FVector ObjectPosition(Px.X, Px.Y, 0);
	const FRotator ObjectRotation(0, 0, 0); //in degrees
	const FVector ObjectScale(1, 1, 1);
	const FTransform ObjectTransform(ObjectRotation, ObjectPosition, ObjectScale);

	HexagonPlain->SetRelativeTransform(ObjectTransform);
	HexagonPlain->SetWorldTransform(ObjectTransform);

}
