// Fill out your copyright notice in the Description page of Project Settings.

#include "HexWorldClient.h"

#include "FHexWorldRunnable.h"
#include "hex_lib.h"
#include "hex_client.h"
#include "hex_com_state.h"
#include "Misc/MessageDialog.h"

bool UHexWorldClient::ConnectToBackend()
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

TArray<FHexagonCoordinates> UHexWorldClient::GetHexagonRing(const FAxialCoordinates Center) const
{

    Hexagon* CenterHex = new Hexagon(Center.Q, - Center.Q - Center.R, Center.R);
    const auto ConnectionState = HexagonClient->GetConnectionState();
    if(ConnectionState == hw_conn_state::HEXWORLD_CONNECTION_READY || ConnectionState == hw_conn_state::HEXWORLD_CONNECTION_IDLE)
    {
        
        
        FHexWorldRunnable::RunLambdaOnBackgroundThread(HexCoordData,[&]
        {
            TArray<FHexagonCoordinates> HexCoList;
            std::vector<Hexagon> HexCV = HexagonClient->GetHexagonRing(CenterHex, 1);
            for(int i=0; i< HexCV.size(); i++)
            {
                FHexagonCoordinates Hc{ static_cast<int>(HexCV[i].X),  static_cast<int>(HexCV[i].Y),  static_cast<int>(HexCV[i].Z)};
                
                HexCoList.Add(Hc);
                HexCoordData->Enqueue(Hc);
            }
        
            for (auto Hex : HexCoList)
            {
                UE_LOG(LogTemp, Display, TEXT("[%d, %d, %d ]"), Hex.X, Hex.Y, Hex.Z);

                
            }
        });

        
        TArray<FHexagonCoordinates>empty;
        return empty;
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
