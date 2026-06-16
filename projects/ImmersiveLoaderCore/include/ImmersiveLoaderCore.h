#pragma once
#include <filesystem>
#include <pugixml.hpp>
#include <spdlog/spdlog.h>
#include <openssl/sha.h>

#include <windows.h>

namespace WinDurango {
    struct PackageInfo {
        static std::string GetPublisherHash(std::string publisher);
        
        std::string pkgVer;
        std::string pkgName;
        std::string pkgFullName;
        std::string pkgFamilyName;
    };
    
    class ImmersiveLoaderCore {
    public:
        ImmersiveLoaderCore(std::filesystem::path AppxManifestPath);
    
    private:
        std::string GetPublisherHash(std::string publisher);

        PackageInfo pkgInfo;
        std::filesystem::path exePath;
        bool m_init = false;
    };
}