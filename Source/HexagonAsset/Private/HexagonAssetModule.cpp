﻿#pragma once

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

class FHexagonAssetModule : public IModuleInterface
{
public:
    virtual void StartupModule() override { }
    virtual void ShutdownModule() override { }

    virtual bool SupportsDynamicReloading() override
    {
        return true;
    }    
};

IMPLEMENT_MODULE(FHexagonAssetModule, HexagonAsset);