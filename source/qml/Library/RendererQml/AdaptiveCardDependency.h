#pragma once

#include <string>
#include <functional>
#include <vector>

namespace RendererQml
{
    class AdaptiveCardDependency
    {
    public:
        // OnClick(const std::string& elementID, const std::string& elementType)
        using OnClickFunction = std::function<std::string(const std::string&, const std::string&)>;
    };
}
