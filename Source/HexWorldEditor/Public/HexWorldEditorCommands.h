// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "HexWorldEditorStyle.h"

class FHexWorldEditorCommands : public TCommands<FHexWorldEditorCommands>
{
public:

	FHexWorldEditorCommands()
		: TCommands<FHexWorldEditorCommands>(TEXT("HexWorldCreator"), NSLOCTEXT("Contexts", "HexWorldCreator", "HexWorldCreator Plugin"), NAME_None, FHexWorldEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
