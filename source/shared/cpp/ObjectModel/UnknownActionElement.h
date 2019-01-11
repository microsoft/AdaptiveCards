#pragma once

#include "pch.h"
#include "BaseActionElement.h"
#include "Enums.h"
#include "ActionParserRegistration.h"

namespace AdaptiveSharedNamespace
{
    class UnknownActionElement : public BaseActionElement
    {
    public:
        UnknownActionElement();
    };

    class UnknownActionElementParser : public ActionElementParser
    {
    public:
        UnknownActionElementParser() = default;
        UnknownActionElementParser(const UnknownActionElementParser&) = default;
        UnknownActionElementParser(UnknownActionElementParser&&) = default;
        UnknownActionElementParser& operator=(const UnknownActionElementParser&) = default;
        UnknownActionElementParser& operator=(UnknownActionElementParser&&) = default;
        ~UnknownActionElementParser() = default;

        std::shared_ptr<BaseActionElement> Deserialize(ParseContext& context, const Json::Value& root) override;
    };
}
