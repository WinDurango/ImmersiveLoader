#pragma once
#include <filesystem>
#include <pugixml.hpp>

namespace WinDurango {
    class ImmersiveLoaderCore {
    public:
        ImmersiveLoaderCore(std::filesystem::path AppxManifestPath);
    
    private:
        std::string aumid;
        std::filesystem::path exePath;
    };
}