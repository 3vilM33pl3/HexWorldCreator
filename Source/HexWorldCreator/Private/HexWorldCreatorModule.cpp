// Copyright Epic Games, Inc. All Rights Reserved.

#include "HexWorldCreatorModule.h"

#include <sstream>

#include "HexWorldCreatorStyle.h"
#include "HexWorldCreatorCommands.h"
#include "LevelEditorViewport.h"
#include "Misc/MessageDialog.h"
#include "Editor.h"
#include "Hexagon.h"
#include "ToolMenus.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMeshActor.h"

DEFINE_LOG_CATEGORY(HexWorldEditor);

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

PixelPoint ConvertAxialToPixelCoordsLocal(const struct AxialCoordinates &ac, const int size) {
    double x = size * (3.0 / 2.0 * ac.Q);
    double y = size * (sqrt(3.0)/2.0 * ac.Q + sqrt(3.0) * ac.R);
    return PixelPoint(x, y);
}

void FHexWorldCreatorModule::PlaceHexagons(FHexagonCoordinates* hex) const
{
	UE_LOG(LogTemp, Warning, TEXT("Placing Hexagon\n"));
	PixelPoint px = ConvertAxialToPixelCoordsLocal(AxialCoordinates(hex->X, hex->Z), 1500);


	
	FVector objectPosition(px.X, px.Y, 0);
	FRotator objectRotation(0, 0, 0); //in degrees
	FVector objectScale(1, 1, 1);
	FTransform objectTrasform(objectRotation, objectPosition, objectScale);

	UWorld* currentWorld = GEditor->GetEditorWorldContext().World();
	ULevel * currentLevel = currentWorld->GetCurrentLevel();
	UClass * staticMeshClass = AStaticMeshActor::StaticClass();

	AActor * newActorCreated = GEditor->AddActor(currentLevel, staticMeshClass, objectTrasform, true, RF_Public | RF_Standalone | RF_Transactional);

	UStaticMesh* HexAsset = Cast<UStaticMesh>(StaticLoadObject( UStaticMesh::StaticClass(), nullptr, *FName("/HexWorldCreator/HexagonBase.HexagonBase").ToString() ));

	AStaticMeshActor * smActor = Cast<AStaticMeshActor>(newActorCreated);

	smActor->GetStaticMeshComponent()->SetStaticMesh(HexAsset);
	smActor->SetActorScale3D(objectScale);
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
	
IMPLEMENT_MODULE(FHexWorldCreatorModule, HexWorldCreator)