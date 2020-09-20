#include "HexWorldPawn.h"
#include "HexagonActor.h"
#include "HexWorldBlueprintFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// DEFINE_LOG_CATEGORY(LogHexWorld);


void AHexWorldPawn::InitialisePawn()
{
	
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> NarrowBoatMesh;
		FConstructorStatics()
			: NarrowBoatMesh(TEXT("/HexWorldCreator/Narrowboat.Narrowboat"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;
	
	NarrowBoatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Narrowboat"));
	NarrowBoatMesh->SetStaticMesh(ConstructorStatics.NarrowBoatMesh.Get());
	RootComponent = NarrowBoatMesh;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeLocation(FVector(-550.f,0.f,240.f));
	SpringArm->SetRelativeRotation(FRotator(-45.f,0.0f,0.0f));
	SpringArm->TargetArmLength = 600.0f;	
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);	// Attach the camera
	Camera->bUsePawnControlRotation = false; // Don't rotate camera with controller

	HexagonPlain = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HexagonPlain"));

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
}

AHexWorldPawn::AHexWorldPawn()
{
 	PrimaryActorTick.bCanEverTick = true;
    InitialisePawn();
	
}

void AHexWorldPawn::BeginPlay()
{
	const FVector Loc = GetActorLocation();
	CurrentLocationInAxialCoords = UHexWorldBlueprintFunctionLibrary::ConvertPixelToAxialCoords(Loc.X, Loc.Y);
	HexWorldServer = NewObject<UHexWorldClient>();
	HexWorldServer->ConnectToBackend();
	Super::BeginPlay();
}

void AHexWorldPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	const FVector LocalMove = FVector(CurrentForwardSpeed * DeltaTime, 0.f, 0.f);
	AddActorLocalOffset(LocalMove, false);

	FVector LocVec = GetActorLocation();
	FAxialCoordinates Location = UHexWorldBlueprintFunctionLibrary::ConvertPixelToAxialCoords(LocVec.X, LocVec.Y);
	if(CurrentLocationInAxialCoords.Q != Location.Q || CurrentLocationInAxialCoords.R != Location.R)
	{
		CurrentLocationInAxialCoords = Location;
		HexWorldServer->GetHexagonRing(CurrentLocationInAxialCoords);
		
	}
	if(!HexWorldServer->HexCoordData->IsEmpty())
	{
		FHexagonCoordinates* Hex = new FHexagonCoordinates();
		if(HexWorldServer->HexCoordData->Dequeue(*Hex))
		{
			AHexagonActor* HexMesh = NewObject<AHexagonActor>();
			HexMesh->TransformAndSpawn(*Hex);
			AllTheHexagons.Push(HexMesh);
			HexMesh->HexagonComponent->RegisterComponentWithWorld(GetWorld());
			
			// UStaticMesh* HexAsset = Cast<UStaticMesh>(StaticLoadObject( UStaticMesh::StaticClass(), nullptr, *FName("/HexWorldCreator/HexagonBase.HexagonBase").ToString() ));
			//
			// const FPixelPoint Px = UHexWorldBlueprintFunctionLibrary::ConvertAxialToPixelCoords(FAxialCoordinates(Hex->X, Hex->Z), 1500);
			// const FVector ObjectPosition(Px.X, Px.Y, 0);
			// const FRotator ObjectRotation(0, 0, 0); //in degrees
			// const FVector ObjectScale(1, 1, 1);
			// const FTransform ObjectTransform(ObjectRotation, ObjectPosition, ObjectScale);
			//
			// HexMesh->HexagonPlain->SetWorldTransform(ObjectTransform);
			// HexMesh->HexagonPlain->SetStaticMesh(HexAsset);
			
		}
	}
	
}

// Called to bind functionality to input
void AHexWorldPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("ScrollWheelForward", IE_Pressed, this, &AHexWorldPawn::CameraZoomForward);
	InputComponent->BindAction("ScrollWheelBack", IE_Pressed, this, &AHexWorldPawn::CameraZoomBack);

}

void AHexWorldPawn::CameraZoomForward()
{
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength - 50.0f, 600.0f, 5000.0f);
}

void AHexWorldPawn::CameraZoomBack()
{
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength + 50.0f, 600.0f, 5000.0f);
}



