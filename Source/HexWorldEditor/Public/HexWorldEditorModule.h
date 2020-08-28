// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Hexagon.h"
#include "hex_client.h"
#include "Modules/ModuleInterface.h"

DECLARE_LOG_CATEGORY_EXTERN(HexWorldEditor, All, All);

class FToolBarBuilder;
class FMenuBuilder;

class FHexWorldEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void PluginButtonClicked();
	
private:
	void RegisterMenus();
	HexagonClient* hexagonClient;
	TSharedPtr<class FUICommandList> PluginCommands;
	void PlaceHexagons(FHexagonCoordinates* hex) const;
};
