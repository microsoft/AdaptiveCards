// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Uwp
{
    class DECLSPEC_UUID("DE80B551-C035-43AA-92C3-CE614ACDB8B5") AdaptiveTextStyleConfigBase : public IUnknown
    {
    public:
        IFACEMETHODIMP get_Weight(_Out_ ABI::AdaptiveCards::Rendering::Uwp::TextWeight* textWeight);
        IFACEMETHODIMP put_Weight(ABI::AdaptiveCards::Rendering::Uwp::TextWeight textWeight);

        IFACEMETHODIMP get_Size(_Out_ ABI::AdaptiveCards::Rendering::Uwp::TextSize* textSize);
        IFACEMETHODIMP put_Size(ABI::AdaptiveCards::Rendering::Uwp::TextSize textSize);

        IFACEMETHODIMP get_Color(_Out_ ABI::AdaptiveCards::Rendering::Uwp::ForegroundColor* textColor);
        IFACEMETHODIMP put_Color(ABI::AdaptiveCards::Rendering::Uwp::ForegroundColor textColor);

        IFACEMETHODIMP get_IsSubtle(_Out_ boolean* isSubtle);
        IFACEMETHODIMP put_IsSubtle(boolean isSubtle);

        IFACEMETHODIMP get_FontType(_Out_ ABI::AdaptiveCards::Rendering::Uwp::FontType* fontType);
        IFACEMETHODIMP put_FontType(ABI::AdaptiveCards::Rendering::Uwp::FontType fontType);

    protected:
        HRESULT InitializeTextStyleConfig(TextStyleConfig textStyleConfig);

    private:
        ABI::AdaptiveCards::Rendering::Uwp::TextWeight m_textWeight;
        ABI::AdaptiveCards::Rendering::Uwp::TextSize m_textSize;
        ABI::AdaptiveCards::Rendering::Uwp::ForegroundColor m_textColor;
        boolean m_isSubtle;
        ABI::AdaptiveCards::Rendering::Uwp::FontType m_fontType;
    };
}
