// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "ParseUtil.h"
#include "BaseCardElement.h"
#include "TextBlock.h"

namespace AdaptiveSharedNamespace
{
    class BaseInputElement : public BaseCardElement
    {
    public:
        BaseInputElement();
        BaseInputElement(CardElementType elementType);
        BaseInputElement(CardElementType type, Spacing spacing, bool separator, HeightType height);

        template<typename T> static std::shared_ptr<T> Deserialize(ParseContext& context, const Json::Value& json);

        std::string GetLabel() const;
        void SetLabel(const std::string label);

        bool GetIsRequired() const;
        void SetIsRequired(const bool isRequired);

        std::string GetErrorMessage() const;
        void SetErrorMessage(const std::string errorMessage);

        static std::shared_ptr<BaseInputElement> DeserializeBasePropertiesFromString(ParseContext& context, const std::string& jsonString);
        static std::shared_ptr<BaseInputElement> DeserializeBaseProperties(ParseContext& context, const Json::Value& json);

        Json::Value SerializeToJsonValue() const override;

    private:
        void PopulateKnownPropertiesSet();
        static void DeserializeBaseProperties(ParseContext& context, const Json::Value& json, std::shared_ptr<BaseInputElement>& element);

        bool m_isRequired;
        std::string m_errorMessage;
        std::string m_label;
    };

    template<typename T>
    std::shared_ptr<T> BaseInputElement::Deserialize(ParseContext& context, const Json::Value& json)
    {
        std::shared_ptr<T> baseInputElement = BaseCardElement::Deserialize<T>(context, json);
        std::shared_ptr<BaseInputElement> inputElement = std::static_pointer_cast<BaseInputElement>(baseInputElement);

        DeserializeBaseProperties(context, json, inputElement);

        return baseInputElement;
    }
}
