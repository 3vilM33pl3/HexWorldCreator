// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logging/LogMacros.h"
#include "GameFramework/Pawn.h"
#include "Hexagon.h"
#include "HexWorldServer.h"
#include "HexWorldPawn.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogHexWorld, Log, All);

UCLASS()
class HEXWORLDRUNTIME_API AHexWorldPawn final : public APawn
{
	GENERATED_BODY()

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* NarrowBoatMesh;

	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

public:
	void InitialisePawn();
	AHexWorldPawn();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(Category = Mesh, BlueprintReadWrite, EditAnywhere)
	float CurrentForwardSpeed = 500.0f;

	UPROPERTY(Category=HexWorld, BlueprintReadWrite, EditAnywhere)
	FString ServerAddress;
	
	UPROPERTY(Category = Camera, BlueprintReadWrite, EditAnywhere)
	float SpringArmLength = -440.0f;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadOnly)
	UHexWorldServer* HexWorldServer;


	/** Returns PlaneMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetPlaneMesh() const { return NarrowBoatMesh; }
	/** Returns SpringArm subobject **/
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
	/** Returns Camera subobject **/
	FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }

	private:
	FAxialCoordinates CurrentLocationInAxialCoords;
	
};
