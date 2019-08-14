// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseActionElement.h"
#include "ActionParserRegistration.h"

namespace AdaptiveSharedNamespace
{
    class SubmitAction : public BaseActionElement
    {
    public:
        SubmitAction();
        SubmitAction(const SubmitAction&) = default;
        SubmitAction(SubmitAction&&) = default;
        SubmitAction& operator=(const SubmitAction&) = default;
        SubmitAction& operator=(SubmitAction&&) = default;
        ~SubmitAction() = default;

        std::string GetDataJson() const;
        Json::Value GetDataJsonAsValue() const;
        void SetDataJson(const Json::Value& value);
        void SetDataJson(const std::string value);

        virtual bool GetIgnoreInputValidation() const;
        virtual void SetIgnoreInputValidation(const bool value);

        Json::Value SerializeToJsonValue() const override;

    private:
        void PopulateKnownPropertiesSet() override;

        Json::Value m_dataJson;
        bool m_ignoreInputValidation;
    };

    class SubmitActionParser : public ActionElementParser
    {
    public:
        SubmitActionParser() = default;
        SubmitActionParser(const SubmitActionParser&) = default;
        SubmitActionParser(SubmitActionParser&&) = default;
        SubmitActionParser& operator=(const SubmitActionParser&) = default;
        SubmitActionParser& operator=(SubmitActionParser&&) = default;
        virtual ~SubmitActionParser() = default;

        std::shared_ptr<BaseActionElement> Deserialize(ParseContext& context, const Json::Value& value) override;
        std::shared_ptr<BaseActionElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
    };
}
