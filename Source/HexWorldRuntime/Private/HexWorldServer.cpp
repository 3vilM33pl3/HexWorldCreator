// Fill out your copyright notice in the Description page of Project Settings.


#include "HexWorldServer.h"

#include <sstream>


#include "Misc/MessageDialog.h"

bool UHexWorldServer::ConnectToBackend()
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

bool UHexWorldServer::GetHexagonRing() const
{
    const auto ConnectionState = HexagonClient->GetConnectionState();
    if(ConnectionState == hw_conn_state::HEXWORLD_CONNECTION_READY || ConnectionState == hw_conn_state::HEXWORLD_CONNECTION_IDLE)
    {
        auto result = HexagonClient->GetHexagonRing(new Hexagon(0, 0, 0), 2);
        std::ostringstream resultStream;
		
        for(auto hex: result) {
            resultStream << "[X: " << hex.X << ", Y: " << hex.Y << ", Z: " << hex.Z << "]\n";
            // PlaceHexagons(&hex);
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
