
namespace UnrealBuildTool.Rules
{

    public class HexagonAsset : ModuleRules
    {
        public HexagonAsset(ReadOnlyTargetRules Target) : base(Target)
        {
            PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                    "Core",
                    "CoreUObject",
                });

            PrivateIncludePaths.AddRange(
                new string[]
                {
                    "Runtime/HexagonAsset/Private",
                });
        }
    }
}
