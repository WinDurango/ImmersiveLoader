#include "ImmersiveLoaderCore.h"

namespace WinDurango {
    ImmersiveLoaderCore::ImmersiveLoaderCore(std::filesystem::path AppxManifestPath) {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(AppxManifestPath.c_str());
        if (!result) {
            // failed
        }
    }
}