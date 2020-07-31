// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonAssetActions.h"
#include "AssetData.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions"

HexagonAssetActions::HexagonAssetActions(const TSharedRef<ISlateStyle>& InStyle) : Style(InStyle)
{ }

FText HexagonAssetActions::GetName() const
{
    return LOCTEXT("HexagonAssetTypeActionsName", "Hexagon Asset");
}

UClass* HexagonAssetActions::GetSupportedClass() const
{
    
}

FColor HexagonAssetActions::GetTypeColor() const
{
}

uint32 HexagonAssetActions::GetCategories()
{
}

bool HexagonAssetActions::HasActions(const TArray<UObject*>& InObjects) const
{
}

void HexagonAssetActions::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder)
{
}

void HexagonAssetActions::OpenAssetEditor(const TArray<UObject*>& InObjects,
    TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
}

bool HexagonAssetActions::CanFilter()
{
}
