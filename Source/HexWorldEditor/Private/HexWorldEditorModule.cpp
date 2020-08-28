// Copyright Epic Games, Inc. All Rights Reserved.

#include "HexWorldEditorModule.h"

#include <sstream>

#include "HexWorldEditorStyle.h"
#include "HexWorldEditorCommands.h"
#include "LevelEditorViewport.h"
#include "Misc/MessageDialog.h"
#include "Editor.h"
#include "Hexagon.h"
#include "HexWorldBlueprintFunctionLibrary.h"
#include "ToolMenus.h"
#include "Engine/StaticMeshActor.h"

DEFINE_LOG_CATEGORY(HexWorldEditor);

static const FName HexWorldEditorTabName("HexWorldEditor");

#define LOCTEXT_NAMESPACE "FHexWorldEditorModule"

void FHexWorldEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	hexagonClient = new HexagonClient("hexcloud-j6feiuh7aa-ue.a.run.app:443");
	auto status = hexagonClient->ConnectToServer();

	if(status != HEXWORLD_CONNECTION_READY)
	{
		UE_LOG(LogTemp, Warning, TEXT("Error connecting to server") );	
	}

	
	FHexWorldEditorStyle::Initialize();
	FHexWorldEditorStyle::ReloadTextures();

	FHexWorldEditorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FHexWorldEditorCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FHexWorldEditorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FHexWorldEditorModule::RegisterMenus));
}

void FHexWorldEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FHexWorldEditorStyle::Shutdown();

	FHexWorldEditorCommands::Unregister();
}

void FHexWorldEditorModule::PluginButtonClicked()
{
	auto connectionState = hexagonClient->GetConnectionState();
	if(connectionState == hw_conn_state::HEXWORLD_CONNECTION_READY || connectionState == hw_conn_state::HEXWORLD_CONNECTION_IDLE)
	{
		auto result = hexagonClient->GetHexagonRing(new Hexagon(0, 0, 0), 2);
		std::ostringstream resultStream;
		
		for(auto hex: result) {
			resultStream << "[X: " << hex.X << ", Y: " << hex.Y << ", Z: " << hex.Z << "]\n";
			FHexagonCoordinates hc(hex.X, hex.Y, hex.Z);
			
			PlaceHexagons(&hc);
		}

		

		FString msg(resultStream.str().c_str());	
		// Put your "OnButtonClicked" stuff here
		FText DialogText = FText::FromString(*msg);
		FMessageDialog::Open(EAppMsgType::Ok, DialogText);	
	} else
	{
		FText DialogText = FText::FromString("Unknown state");
		switch (connectionState)
		{
			case HEXWORLD_CONNECTION_FATAL:
	           DialogText = FText::FromString("Fatal");
				break;
			case HEXWORLD_CONNECTION_RETRY:
				DialogText = FText::FromString("Retry");
				break;
			case HEXWORLD_CONNECTION_TIMEOUT:
	        DialogText = FText::FromString("Timeout");
				break;
			case HEXWORLD_CONNECTING:
	        DialogText = FText::FromString("Connecting");
				break;
		}
		FMessageDialog::Open(EAppMsgType::Ok, DialogText);
	}
	
}

void FHexWorldEditorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FHexWorldEditorCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FHexWorldEditorCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}



void FHexWorldEditorModule::PlaceHexagons(FHexagonCoordinates* hex) const
{
	UE_LOG(LogTemp, Warning, TEXT("Placing Hexagon\n"));
	FPixelPoint px = UHexWorldBlueprintFunctionLibrary::ConvertAxialToPixelCoords(FAxialCoordinates(hex->X, hex->Z), 1500);


	const FVector ObjectPosition(px.X, px.Y, 0);
	const FRotator ObjectRotation(0, 90, 0); //in degrees
	const FVector ObjectScale(1, 1, 1);
	const FTransform ObjectTransform(ObjectRotation, ObjectPosition, ObjectScale);

	UWorld* currentWorld = GEditor->GetEditorWorldContext().World();
	ULevel * currentLevel = currentWorld->GetCurrentLevel();
	UClass * staticMeshClass = AStaticMeshActor::StaticClass();

	AActor * newActorCreated = GEditor->AddActor(currentLevel, staticMeshClass, ObjectTransform, true, RF_Public | RF_Standalone | RF_Transactional);

	UStaticMesh* HexAsset = Cast<UStaticMesh>(StaticLoadObject( UStaticMesh::StaticClass(), nullptr, *FName("/HexWorldCreator/HexagonBase.HexagonBase").ToString() ));

	AStaticMeshActor * smActor = Cast<AStaticMeshActor>(newActorCreated);

	smActor->GetStaticMeshComponent()->SetStaticMesh(HexAsset);
	smActor->SetActorScale3D(ObjectScale);
	// ID Name & Visible Name
	// smActor->Rename(TEXT("MyStaticMeshInTheWorld" + hex->X + hex->Y + hex->Z));
	// smActor->SetActorLabel("MyStaticMeshInTheWorld" + hex->X + hex->Y + hex->Z);

	GEditor->EditorUpdateComponents();
	smActor->GetStaticMeshComponent()->RegisterComponentWithWorld(currentWorld);
	currentWorld->UpdateWorldComponents(true, false);
	smActor->RerunConstructionScripts();

	// GLevelEditorModeTools().MapChangeNotify();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHexWorldEditorModule, HexWorldEditor)