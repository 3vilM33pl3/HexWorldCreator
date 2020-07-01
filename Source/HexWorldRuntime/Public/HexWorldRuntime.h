#pragma once
#include "Modules/ModuleInterface.h"

DECLARE_LOG_CATEGORY_EXTERN(HexWorldRuntime, All, All);

class FHexWorldRuntime : public IModuleInterface
{
public:
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    
};
