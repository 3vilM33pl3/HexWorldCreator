// Fill out your copyright notice in the Description page of Project Settings.

#include "HexagonActorFactory.h"
#include "Hexagon.h"


const FName UHexagonActorFactory::HexagonBase("/HexWorldCreator/HexagonBase.HexagonBase");
const FName UHexagonActorFactory::HexagonCanalCurve("/HexWorldCreator/HexagonCanalCurve.HexagonCanalCurve");
const FName UHexagonActorFactory::HexagonCanalSplit("/HexWorldCreator/HexagonCanalSplit.HexagonCanalSplit");
const FName UHexagonActorFactory::HexagonCanalStraight("/HexWorldCreator/HexagonCanalStraight.HexagonCanalStraight");

void UHexagonActorFactory::PostSpawnActor(UObject* Asset, AActor* NewActor)
{
        UE_LOG(LogTemp, Warning, TEXT("Lalala") );
}
bool UHexagonActorFactory::CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg)
{
    if ( !AssetData.IsValid() || !AssetData.GetClass()->IsChildOf( UStaticMesh::StaticClass() ) )
    {
        OutErrorMsg = NSLOCTEXT("CanCreateActor", "NoStaticMesh", "A valid static mesh must be specified.");
        return false;
    }

    return true;   
}
