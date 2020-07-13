// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaticMeshComponent.h"
#include "HexWorldServer.h"

#include <sstream>



#include "HexWorldBlueprintFunctionLibrary.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/MessageDialog.h"

bool AHexWorldServer::ConnectToBackend()
{
    HexagonClient = new ::HexagonClient(std::string(TCHAR_TO_UTF8(*ServerAddress)));

    const auto Status = HexagonClient->ConnectToServer();

    if(Status != HEXWORLD_CONNECTION_READY)
    {
        UE_LOG(LogTemp, Warning, TEXT("Error connecting to server"));
        return false;
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("Connected to server"))
        return true;
    }
}


void AHexWorldServer::PlaceHexagon(Hexagon* Hex) 
{
    

    // const FString ContentDir = IPluginManager::Get().FindPlugin(TEXT("HexWorldCreator"))->GetContentDir();
    // const FName HexMeshName(ContentDir + "HexagonBase.HexagonBase");
    UStaticMesh* HexAsset = Cast<UStaticMesh>(StaticLoadObject( UStaticMesh::StaticClass(), nullptr, *FName("/HexWorldCreator/HexagonBase.HexagonBase").ToString() ));

    const PixelPoint Px = UHexWorldBlueprintFunctionLibrary::ConvertAxialToPixelCoordsLocal(AxialCoordinates(Hex->X, Hex->Z), 1500);
    const FVector ObjectLocation(Px.X, Px.Y, 0);
    const FRotator ObjectRotation(0, 0, 0); //in degrees

    AHexWorldServer* SpawnedActor1 = (AHexWorldServer*) GetWorld()->SpawnActor(AHexWorldServer::StaticClass(), &ObjectLocation, &ObjectRotation);

    SpawnedActor1->HexagonPlain->SetStaticMesh(HexAsset);

}

bool AHexWorldServer::GetHexagonRing() 
{
    const auto ConnectionState = HexagonClient->GetConnectionState();
    if(ConnectionState == hw_conn_state::HEXWORLD_CONNECTION_READY || ConnectionState == hw_conn_state::HEXWORLD_CONNECTION_IDLE)
    {
        auto result = HexagonClient->GetHexagonRing(new Hexagon(0, 0, 0), 2);
        std::ostringstream resultStream;
		
        for(auto hex: result) {
            resultStream << "[X: " << hex.X << ", Y: " << hex.Y << ", Z: " << hex.Z << "]\n";
            PlaceHexagon(&hex);
        }

        FString msg(resultStream.str().c_str());	
        // Put your "OnButtonClicked" stuff here
        FText DialogText = FText::FromString(*msg);
        FMessageDialog::Open(EAppMsgType::Ok, DialogText);
        return true;
    } else
    {
        FText DialogText = FText::FromString("Unknown state");
        switch (ConnectionState)
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
        return false;
    }
}
