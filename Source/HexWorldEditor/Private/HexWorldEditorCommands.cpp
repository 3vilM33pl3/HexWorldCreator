// Copyright Epic Games, Inc. All Rights Reserved.

#include "HexWorldEditorCommands.h"

#define LOCTEXT_NAMESPACE "FHexWorldEditorModule"

void FHexWorldEditorCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "HexWorldEditor", "Execute HexWorldEditor action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
