#pragma once

#include "pch.h"
#include "BaseActionElement.h"
#include "Enums.h"
#include "ActionParserRegistration.h"

namespace AdaptiveSharedNamespace
{
    class SubmitAction : public BaseActionElement
    {
    public:
        SubmitAction();

        std::string GetDataJson() const;
        Json::Value GetDataJsonAsValue() const;
        void SetDataJson(const Json::Value& value);

        Json::Value SerializeToJsonValue() const override;

    private:
        void PopulateKnownPropertiesSet() override;

        Json::Value m_dataJson;
    };

    class SubmitActionParser : public ActionElementParser
    {
    public:
        SubmitActionParser() = default;
        SubmitActionParser(const SubmitActionParser&) = default;
        SubmitActionParser(SubmitActionParser&&) = default;
        SubmitActionParser& operator=(const SubmitActionParser&) = default;
        SubmitActionParser& operator=(SubmitActionParser&&) = default;
        ~SubmitActionParser() = default;

        std::shared_ptr<BaseActionElement> Deserialize(ParseContext& context, const Json::Value& value) override;
        std::shared_ptr<BaseActionElement> DeserializeFromString(ParseContext& context, const std::string& jsonString);
    };
}
