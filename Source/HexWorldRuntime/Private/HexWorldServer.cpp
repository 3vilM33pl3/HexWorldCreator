// Fill out your copyright notice in the Description page of Project Settings.

#include "HexWorldServer.h"
#include "hex_lib.h"
#include "hex_client.h"
#include "hex_com_state.h"
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

TArray<FHexagonCoordinates> AHexWorldServer::GetHexagonRing() const
{
    const auto ConnectionState = HexagonClient->GetConnectionState();
    if(ConnectionState == hw_conn_state::HEXWORLD_CONNECTION_READY || ConnectionState == hw_conn_state::HEXWORLD_CONNECTION_IDLE)
    {
        /// TODO put HexCoord in function call
        std::vector<Hexagon> HexCV = HexagonClient->GetHexagonRing(new Hexagon(0, 0, 0), 2);
        
        TArray<FHexagonCoordinates> HexCoList;
        

        for(int i=0; i< HexCV.size(); i++)
        {
            HexCoList.Add(FHexagonCoordinates(HexCV[i].X, HexCV[i].Y, HexCV[i].Z));
        }

        return HexCoList;
    } else
    {
        // TODO Logging instead of dialog
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
        TArray<FHexagonCoordinates>empty;
        return empty;
    }
}
