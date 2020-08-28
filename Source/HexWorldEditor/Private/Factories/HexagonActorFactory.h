#pragma once

#include "CoreMinimal.h"
#include "ActorFactories/ActorFactoryStaticMesh.h"
#include "HexagonActorFactory.generated.h"

UCLASS()
class UHexagonActorFactory : public UActorFactory
{
	GENERATED_BODY()

	virtual bool CanCreateActorFrom( const FAssetData& AssetData, FText& OutErrorMsg ) override;
	virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;

	static const FName HexagonBase;
	static const FName HexagonCanalCurve;
	static const FName HexagonCanalStraight;
	static const FName HexagonCanalSplit;
	
};
