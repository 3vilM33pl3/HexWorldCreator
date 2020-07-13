#include "HexWorldRuntime/Public/HexWorldRuntimeModule.h"

DEFINE_LOG_CATEGORY(HexWorldRuntime);

#define LOCTEXT_NAMESPACE "FHexWorldRuntimeModule"

void FHexWorldRuntimeModule::StartupModule()
{
	UE_LOG(HexWorldRuntime, Warning, TEXT("Hexagon World Runtime module has started!"));
}

void FHexWorldRuntimeModule::ShutdownModule()
{
	UE_LOG(HexWorldRuntime, Warning, TEXT("Hexagon World Runtime module has shut down"));
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHexWorldRuntimeModule, HexWorldRuntime)
