// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    struct AdaptiveTextElement
    {
        property<hstring> Text;
        property_opt<Xaml_OM::TextSize> Size;
        property_opt<Xaml_OM::TextWeight> Weight;
        property_opt<Xaml_OM::ForegroundColor> Color;
        property_opt<bool> IsSubtle;
        property<hstring> Language;
        property_opt<Xaml_OM::FontType> FontType;

    protected:
        template<typename T> void InitializeTextElement(const std::shared_ptr<T>& sharedModel)
        {
            Text = UTF8ToHString(sharedModel->GetText());
            Language = UTF8ToHString(sharedModel->GetLanguage());

            IsSubtle = sharedModel->GetIsSubtle();
            FontType = opt_cast<Xaml_OM::FontType>(sharedModel->GetFontType());
            Size = opt_cast<Xaml_OM::TextSize>(sharedModel->GetTextSize());
            Weight = opt_cast<Xaml_OM::TextWeight>(sharedModel->GetTextWeight());
            Color = opt_cast<Xaml_OM::ForegroundColor>(sharedModel->GetTextColor());
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
