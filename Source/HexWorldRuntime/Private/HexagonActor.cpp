#include "HexagonActor.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HexWorldBlueprintFunctionLibrary.h"
#include "Interfaces/IPluginManager.h"

AHexagonActor::AHexagonActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HexagonComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HexagonPlain")); 
	RootComponent = HexagonComponent;

	HexagonMeshCollection.Base = Cast<UStaticMesh>(StaticLoadObject( UStaticMesh::StaticClass(), nullptr, *FName("/HexWorldCreator/HexagonBase.HexagonBase").ToString() ));
	// static ConstructorHelpers::FObjectFinder<UStaticMesh> HexMesh(TEXT("/HexWorldCreator/HexagonBase.HexagonBase"));
	HexagonComponent->SetStaticMesh(HexagonMeshCollection.Base);

	// TODO Set default values for the other meshed in the collection
	
}

void AHexagonActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHexagonActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHexagonActor::TransformAndSpawn(FHexagonCoordinates HexCoord) const
{

	const FPixelPoint Px = UHexWorldBlueprintFunctionLibrary::ConvertAxialToPixelCoords(FAxialCoordinates(HexCoord.X, HexCoord.Z), 1500);
	const FVector ObjectPosition(Px.X, Px.Y, 0);
	const FRotator ObjectRotation(0, 0, 0); //in degrees
	const FVector ObjectScale(1, 1, 1);
	const FTransform ObjectTransform(ObjectRotation, ObjectPosition, ObjectScale);

	HexagonComponent->SetRelativeTransform(ObjectTransform);
	HexagonComponent->SetWorldTransform(ObjectTransform);

}
