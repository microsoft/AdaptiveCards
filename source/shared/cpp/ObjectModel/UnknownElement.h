#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "Enums.h"
#include <time.h>
#include "ElementParserRegistration.h"
#include "DateTimePreparser.h"

namespace AdaptiveSharedNamespace
{
    class UnknownElement : public BaseCardElement
    {
    public:
        UnknownElement();
    };

    class UnknownElementParser : public BaseCardElementParser
    {
    public:
        UnknownElementParser() = default;
        UnknownElementParser(const UnknownElementParser&) = default;
        UnknownElementParser(UnknownElementParser&&) = default;
        UnknownElementParser& operator=(const UnknownElementParser&) = default;
        UnknownElementParser& operator=(UnknownElementParser&&) = default;
        virtual ~UnknownElementParser() = default;

        std::shared_ptr<BaseCardElement> Deserialize(std::shared_ptr<ElementParserRegistration> elementParserRegistration,
                                                     std::shared_ptr<ActionParserRegistration> actionParserRegistration,
                                                     std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
                                                     const Json::Value& root) override;

        std::shared_ptr<BaseCardElement> DeserializeFromString(std::shared_ptr<ElementParserRegistration> elementParserRegistration,
                                                               std::shared_ptr<ActionParserRegistration> actionParserRegistration,
                                                               std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
                                                               const std::string& jsonString);
    };
}
