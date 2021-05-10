// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseActionElement.h"
#include "ActionParserRegistration.h"

namespace AdaptiveCards
{
    class ExecuteAction : public BaseActionElement
    {
    public:
        ExecuteAction();
        ExecuteAction(const ExecuteAction&) = default;
        ExecuteAction(ExecuteAction&&) = default;
        ExecuteAction& operator=(const ExecuteAction&) = default;
        ExecuteAction& operator=(ExecuteAction&&) = default;
        ~ExecuteAction() = default;

        std::string GetDataJson() const;
        Json::Value GetDataJsonAsValue() const;
        void SetDataJson(const Json::Value& value);
        void SetDataJson(const std::string value);

        std::string GetVerb() const;
        void SetVerb(const std::string verb);

        virtual AssociatedInputs GetAssociatedInputs() const;
        virtual void SetAssociatedInputs(const AssociatedInputs value);

        Json::Value SerializeToJsonValue() const override;

    private:
        void PopulateKnownPropertiesSet();

        Json::Value m_dataJson;
        std::string m_verb;
        AssociatedInputs m_associatedInputs;
    };

    class ExecuteActionParser : public ActionElementParser
    {
    public:
        ExecuteActionParser() = default;
        ExecuteActionParser(const ExecuteActionParser&) = default;
        ExecuteActionParser(ExecuteActionParser&&) = default;
        ExecuteActionParser& operator=(const ExecuteActionParser&) = default;
        ExecuteActionParser& operator=(ExecuteActionParser&&) = default;
        virtual ~ExecuteActionParser() = default;

        std::shared_ptr<BaseActionElement> Deserialize(ParseContext& context, const Json::Value& value) override;
        std::shared_ptr<BaseActionElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
    };
}
