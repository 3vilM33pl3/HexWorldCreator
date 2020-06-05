// Copyright Epic Games, Inc. All Rights Reserved.

#include "HexWorldCreatorCommands.h"

#define LOCTEXT_NAMESPACE "FHexWorldCreatorModule"

void FHexWorldCreatorCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "HexWorldCreator", "Execute HexWorldCreator action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
