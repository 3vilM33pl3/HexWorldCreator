// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "hex_client.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FHexWorldCreator : public IModuleInterface
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
	void PlaceHexagons(Hexagon *hex) const;
};
