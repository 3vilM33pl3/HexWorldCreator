// Fill out your copyright notice in the Description page of Project Settings.


#include "HexWorldServer.h"

UHexWorldServer::UHexWorldServer()
{
}

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
        UE_LOG(LogTemp, Display, TEXT("Conencted to to server"))
        return true;
    }
}
