#include "HexWorldRuntime/Public/HexWorldRuntime.h"

DEFINE_LOG_CATEGORY(HexWorldRuntime);

#define LOCTEXT_NAMESPACE "FHexWorldRuntimeModule"

void FHexWorldRuntime::StartupModule()
{
	UE_LOG(HexWorldRuntime, Warning, TEXT("Orfeas module has started!"));
}

void FHexWorldRuntime::ShutdownModule()
{
	UE_LOG(HexWorldRuntime, Warning, TEXT("Orfeas module has shut down"));
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHexWorldRuntime, HexWorldRuntime)
