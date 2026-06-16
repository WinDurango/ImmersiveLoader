#include "ImmersiveLoaderCore.h"

namespace WinDurango {
    ImmersiveLoaderCore::ImmersiveLoaderCore(std::filesystem::path AppxManifestPath) {
        spdlog::set_pattern("[WinDurango::ImmersiveLoaderCore] [%H:%M:%S] [thread %t] - %^%l%$: %v");

        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(AppxManifestPath.c_str());
        if (!result) {
            spdlog::error("Failed to load and parse Appx Manifest : {}", result.description());
            return;
        }

        std::string xmlExe = doc.child("Package").child("Applications").child("Application").attribute("Executable").as_string();

        spdlog::info("Exe Name : {}", xmlExe);

        if (xmlExe == "") {
            spdlog::info("Failed to get Executable Name : {}", xmlExe);
            return;
        }

        exePath = AppxManifestPath.parent_path() / xmlExe;

        spdlog::info("Exe Path : {}", exePath.string());

        pugi::xml_node pkgIdentity = doc.child("Package").child("Identity");
        
        std::string pkgPublisher = pkgIdentity.attribute("Publisher").as_string();
        std::string pkgPublisherHash = pkgInfo.GetPublisherHash(pkgPublisher);

        pkgInfo.pkgName = pkgIdentity.attribute("Name").as_string();
        pkgInfo.pkgVer = pkgIdentity.attribute("Version").as_string();
        pkgInfo.pkgFullName = pkgInfo.pkgName + "_" + pkgPublisherHash;
        pkgInfo.pkgFamilyName = pkgInfo.pkgName + "_" + pkgPublisherHash;

        spdlog::info("Package: {} - {} - {} - {}", pkgInfo.pkgName, pkgInfo.pkgVer, pkgInfo.pkgFullName, pkgInfo.pkgFamilyName);

        m_init = true;
    }

    /*
     * Thanks to: https://github.com/russellbanks/package-family-name/tree/main
    */
    std::string PackageInfo::GetPublisherHash(std::string publisher) {
        const char b_alpha[33] = "0123456789ABCDEFGHJKMNPQRSTVWXYZ";

        uint8_t hash[32];

        std::wstring w_pub(publisher.begin(), publisher.end());

        SHA256((uint8_t*)w_pub.c_str(), w_pub.size() * sizeof(wchar_t), hash);

        std::string bits;
        for (int i = 0; i < 8; i++) {
            for (int b = 7; b >= 0; b--) {
                bits.push_back(((hash[i] >> b) & 1) ? '1' : '0');
            }
        }
        bits.push_back('0');

        std::string result;
        result.reserve(13);
        for (int i = 0; i < 65; i += 5) {
            int idx = 0;
            for (int b = 0; b < 5; b++) {
                idx = (idx << 1) | (bits[i + b] - '0');
            }
            result += (char)tolower(b_alpha[idx]);
        }

        return result;
    }
}