// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "HexWorldCreatorStyle.h"

class FHexWorldCreatorCommands : public TCommands<FHexWorldCreatorCommands>
{
public:

	FHexWorldCreatorCommands()
		: TCommands<FHexWorldCreatorCommands>(TEXT("HexWorldCreator"), NSLOCTEXT("Contexts", "HexWorldCreator", "HexWorldCreator Plugin"), NAME_None, FHexWorldCreatorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
