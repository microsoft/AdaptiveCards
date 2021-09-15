// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct AdaptiveTextElement
    {
        property<hstring> Text;
        property_opt<Uwp::TextSize> Size;
        property_opt<Uwp::TextWeight> Weight;
        property_opt<Uwp::ForegroundColor> Color;
        property_opt<bool> IsSubtle;
        property<hstring> Language;
        property_opt<Uwp::FontType> FontType;

    protected:
        template<typename T> void InitializeTextElement(const std::shared_ptr<T>& sharedModel)
        {
            Text = UTF8ToHString(sharedModel->GetText());
            Language = UTF8ToHString(sharedModel->GetLanguage());

            IsSubtle = sharedModel->GetIsSubtle();
            FontType = opt_cast<Uwp::FontType>(sharedModel->GetFontType());
            Size = opt_cast<Uwp::TextSize>(sharedModel->GetTextSize());
            Weight = opt_cast<Uwp::TextWeight>(sharedModel->GetTextWeight());
            Color = opt_cast<Uwp::ForegroundColor>(sharedModel->GetTextColor());
        }

        template<typename T> void CopyTextElementProperties(T& sharedCardElement)
        {
            sharedCardElement.SetIsSubtle(IsSubtle);
            sharedCardElement.SetFontType(FontType.get<::AdaptiveCards::FontType>());
            sharedCardElement.SetTextSize(Size.get<::AdaptiveCards::TextSize>());
            sharedCardElement.SetTextWeight(Weight.get<::AdaptiveCards::TextWeight>());
            sharedCardElement.SetTextColor(Color.get<::AdaptiveCards::ForegroundColor>());
            sharedCardElement.SetText(HStringToUTF8(Text));
            if (!Language->empty())
            {
                sharedCardElement.SetLanguage(HStringToUTF8(Language));
            }
        }
    };
}
