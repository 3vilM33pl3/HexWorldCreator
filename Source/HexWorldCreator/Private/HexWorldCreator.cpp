// Copyright Epic Games, Inc. All Rights Reserved.

#include "HexWorldCreator.h"

#include <sstream>

#include "HexWorldCreatorStyle.h"
#include "HexWorldCreatorCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName HexWorldCreatorTabName("HexWorldCreator");

#define LOCTEXT_NAMESPACE "FHexWorldCreatorModule"

void FHexWorldCreatorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	hexagonClient = new HexagonClient("hexcloud-j6feiuh7aa-ue.a.run.app:443");
	auto status = hexagonClient->ConnectToServer();
	if(status != HEXWORLD_CONNECTION_READY)
	{
		UE_LOG(LogTemp, Warning, TEXT("Error connecting to server") );	
	}

	
	FHexWorldCreatorStyle::Initialize();
	FHexWorldCreatorStyle::ReloadTextures();

	FHexWorldCreatorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FHexWorldCreatorCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FHexWorldCreatorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FHexWorldCreatorModule::RegisterMenus));
}

void FHexWorldCreatorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FHexWorldCreatorStyle::Shutdown();

	FHexWorldCreatorCommands::Unregister();
}

void FHexWorldCreatorModule::PluginButtonClicked()
{
	auto result = hexagonClient->GetHexagonRing(new Hexagon(0, 0, 0), 2);
	std::ostringstream resultStream;
	for(auto hex: result) {
		resultStream << "[X: " << hex.X << ", Y: " << hex.Y << ", Z: " << hex.Z << "]\n";
	}

	FString msg(resultStream.str().c_str());	


	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::FromString(*msg);
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FHexWorldCreatorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FHexWorldCreatorCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FHexWorldCreatorCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHexWorldCreatorModule, HexWorldCreator)