// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    struct AdaptiveTextElement
    {
        property<hstring> Text;
        property_opt<WinUI3::TextSize> Size;
        property_opt<WinUI3::TextWeight> Weight;
        property_opt<WinUI3::ForegroundColor> Color;
        property_opt<bool> IsSubtle;
        property<hstring> Language;
        property_opt<WinUI3::FontType> FontType;

    protected:
        template<typename T> void InitializeTextElement(const std::shared_ptr<T>& sharedModel)
        {
            IsSubtle = sharedModel->GetIsSubtle();
            FontType = opt_cast<WinUI3::FontType>(sharedModel->GetFontType());
            Size = opt_cast<WinUI3::TextSize>(sharedModel->GetTextSize());
            Weight = opt_cast<WinUI3::TextWeight>(sharedModel->GetTextWeight());
            Color = opt_cast<WinUI3::ForegroundColor>(sharedModel->GetTextColor());
            Text = UTF8ToHString(sharedModel->GetText());
            Language = UTF8ToHString(sharedModel->GetLanguage());
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
