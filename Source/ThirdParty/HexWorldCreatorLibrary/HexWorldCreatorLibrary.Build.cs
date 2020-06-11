using System.IO;
using UnrealBuildTool;

public class HexWorldCreatorLibrary : ModuleRules
{
    public HexWorldCreatorLibrary(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "hex_client_lib.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "libprotobuf.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "cares.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "grpc++.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "grpc.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "gpr.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "address_sorting.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "ssl.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "crypto.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "upb.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "zlibstatic.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "absl_base.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "absl_int128.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "absl_raw_logging_internal.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "absl_throw_delegate.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "absl_time.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "absl_time_zone.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "absl_str_format_internal.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "absl_strings_internal.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "absl_strings.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "absl_bad_optional_access.lib"));

            string[] paths = new string[]
            {
                "include/hexworld"
            };
            
            foreach(var item in paths)
            {
                PublicIncludePaths.Add(Path.Combine(ModuleDirectory, item));
            }
            
        }
        
        if (Target.Platform == UnrealTargetPlatform.Linux)
        {
                PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Linux", "Release", "libhex_client_lib.a"));
                PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Linux", "Release", "libaddress_sorting.a"));
                PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Linux", "Release", "libgpr.a"));
                PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Linux", "Release", "libgrpc++.a"));
                PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Linux", "Release", "libgrpc.a"));
                PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Linux", "Release", "libupb.a"));
                PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Linux", "Release", "libprotobuf.a"));
                PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Linux", "Release", "libcares.a"));
                PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Linux", "Release", "libssl.a"));
                PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Linux", "Release", "libcrypto.a"));
                PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Linux", "Release", "libz.a"));
                PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Linux", "Release", "libabsl_base.a"));
                PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Linux", "Release", "libabsl_int128.a"));
                PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Linux", "Release", "libabsl_raw_logging_internal.a"));
                PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Linux", "Release", "libabsl_throw_delegate.a"));
                PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Linux", "Release", "libabsl_time.a"));
                PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Linux", "Release", "libabsl_time_zone.a"));
                PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Linux", "Release", "libabsl_str_format_internal.a"));
                PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Linux", "Release", "libabsl_strings_internal.a"));
                PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Linux", "Release", "libabsl_strings.a"));
                PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Linux", "Release", "libabsl_bad_optional_access.a"));

                                   
            string[] paths = new string[]
            {
                "include/hexworld"
            };
            
            foreach(var item in paths)
            {
                PublicIncludePaths.Add(Path.Combine(ModuleDirectory, item));
            }
            
        }
    }
}
