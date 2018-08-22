#pragma once
#include <string>
#include "Enums.h"

namespace AdaptiveSharedNamespace {

    struct RemoteResourceInformation
    {
        std::string url;
        AdaptiveCards::CardElementType resourceType = CardElementType::Image;
        std::string mimeType;
    };

}