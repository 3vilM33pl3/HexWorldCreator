// Fill out your copyright notice in the Description page of Project Settings.

#include "HexWorldBlueprintFunctionLibrary.h"

UHexWorldServer* UHexWorldBlueprintFunctionLibrary::ConnectToServer(FString ServerAddress)
{
    HexWorldServer->ServerAddress = ServerAddress;
    HexWorldServer->ConnectToBackend();
    return HexWorldServer;
    
}
