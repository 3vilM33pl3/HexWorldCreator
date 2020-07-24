// Fill out your copyright notice in the Description page of Project Settings.


#include "HexWorldPawn.h"
#include "Hexagon.h"
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
	SpringArm->SetupAttachment(RootComponent);	// Attach SpringArm to RootComponent
	SpringArm->TargetArmLength = SpringArmLength; // The camera follows at this distance behind the character	
	SpringArm->SocketOffset = FVector(0.f,0.f,80.f);
	SpringArm->bEnableCameraLag = false;	// Do not allow camera to lag
	SpringArm->CameraLagSpeed = 15.f;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);	// Attach the camera
	Camera->bUsePawnControlRotation = false; // Don't rotate camera with controller
	
	
}

// Sets default values
AHexWorldPawn::AHexWorldPawn()
{
 	PrimaryActorTick.bCanEverTick = true;
    InitialisePawn();
	
}

// Called when the game starts or when spawned
void AHexWorldPawn::BeginPlay()
{
	const FVector Loc = GetActorLocation();
	CurrentLocationInAxialCoords = UHexWorldBlueprintFunctionLibrary::ConvertPixelToAxialCoords(Loc.X, Loc.Y);
	HexWorldServer = NewObject<UHexWorldServer>();
	HexWorldServer->ConnectToBackend();
	Super::BeginPlay();
}

// Called every frame
void AHexWorldPawn::Tick(float DeltaTime)
{
	const FVector LocalMove = FVector(CurrentForwardSpeed * DeltaTime, 0.f, 0.f);
	AddActorLocalOffset(LocalMove, false);

	FVector LocVec = GetActorLocation();
	FAxialCoordinates Location = UHexWorldBlueprintFunctionLibrary::ConvertPixelToAxialCoords(LocVec.X, LocVec.Y);
	if(CurrentLocationInAxialCoords.Q != Location.Q || CurrentLocationInAxialCoords.R != Location.R)
	{
		CurrentLocationInAxialCoords = Location;
		HexWorldServer->GetHexagonRing(CurrentLocationInAxialCoords);
	}
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHexWorldPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

