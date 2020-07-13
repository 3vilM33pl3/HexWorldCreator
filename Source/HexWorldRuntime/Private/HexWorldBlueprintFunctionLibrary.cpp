// Fill out your copyright notice in the Description page of Project Settings.

#include "HexWorldBlueprintFunctionLibrary.h"

UHexWorldBlueprintFunctionLibrary::UHexWorldBlueprintFunctionLibrary() : Super()
{
}

bool UHexWorldBlueprintFunctionLibrary::ConnectToServer(AHexWorldServer* Server) 
{
    return Server->ConnectToBackend();    
}
