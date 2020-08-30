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
    return nullptr;
}

FColor HexagonAssetActions::GetTypeColor() const
{
    return FColor{};
}

uint32 HexagonAssetActions::GetCategories()
{
    return 0;
}

bool HexagonAssetActions::HasActions(const TArray<UObject*>& InObjects) const
{
    return false;
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
    return false;;
}
