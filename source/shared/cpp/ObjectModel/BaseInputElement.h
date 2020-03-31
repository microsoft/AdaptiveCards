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
        BaseInputElement(CardElementType elementType);
        BaseInputElement(CardElementType type, Spacing spacing, bool separator, HeightType height);

        template<typename T> static std::shared_ptr<T> Deserialize(ParseContext& context, const Json::Value& json);

        std::string GetLabel() const;
        void SetLabel(const std::string label);

        std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement> GetLabelCardElement() const;
        void SetLabelCardElement(const std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement> label);

        bool GetIsRequired() const;
        void SetIsRequired(const bool isRequired);

        std::string GetErrorMessage() const;
        void SetErrorMessage(const std::string errorMessage);

        Json::Value SerializeToJsonValue() const override;

    protected:
        void PopulateKnownPropertiesSet();

    private:

        bool m_isRequired;
        std::string m_errorMessage;
        std::string m_label;
        std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement> m_labelCardElement;
    };

    template<typename T>
    std::shared_ptr<T> BaseInputElement::Deserialize(ParseContext& context, const Json::Value& json)
    {
        std::shared_ptr<T> baseInputElement = BaseCardElement::Deserialize<T>(context, json);

        ParseUtil::ThrowIfNotJsonObject(json);

        baseInputElement->SetId(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Id, true));
        baseInputElement->SetIsRequired(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::IsRequired, false));
        baseInputElement->SetErrorMessage(ParseUtil::GetString(json, AdaptiveCardSchemaKey::ErrorMessage));

        // Label may be of types string, TextBlock or RichTextBlock
        try
        {
            baseInputElement->SetLabel(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Label));
        }
        catch (std::exception /*e*/)
        {
            baseInputElement->SetLabelCardElement(ParseUtil::GetLabel(context, json, AdaptiveCardSchemaKey::Label));
        }


        return baseInputElement;
    }
}
