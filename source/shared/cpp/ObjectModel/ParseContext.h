#pragma once

#include "pch.h"
#include "ElementParserRegistration.h"
#include "ActionParserRegistration.h"
#include "AdaptiveCardParseWarning.h"

namespace AdaptiveSharedNamespace
{
    class ParseContext
    {
    public:
        ParseContext();
        ParseContext(std::shared_ptr<ElementParserRegistration> elementRegistration,
            std::shared_ptr<ActionParserRegistration> actionRegistration,
            std::shared_ptr<std::unordered_set<std::string>> elementIds = nullptr);

        std::shared_ptr<ElementParserRegistration> elementParserRegistration;
        std::shared_ptr<ActionParserRegistration> actionParserRegistration;
        std::shared_ptr<std::unordered_set<std::string>> elementIds;
        std::vector<std::shared_ptr<AdaptiveCardParseWarning>> warnings;
    };
}
