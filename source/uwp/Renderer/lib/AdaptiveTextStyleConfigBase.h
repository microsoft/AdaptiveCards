// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("DE80B551-C035-43AA-92C3-CE614ACDB8B5") AdaptiveTextStyleConfigBase : public IUnknown
    {
    public:
        IFACEMETHODIMP get_Weight(_Out_ ABI::AdaptiveNamespace::TextWeight* textWeight);
        IFACEMETHODIMP put_Weight(ABI::AdaptiveNamespace::TextWeight textWeight);

        IFACEMETHODIMP get_Size(_Out_ ABI::AdaptiveNamespace::TextSize* textSize);
        IFACEMETHODIMP put_Size(ABI::AdaptiveNamespace::TextSize textSize);

        IFACEMETHODIMP get_Color(_Out_ ABI::AdaptiveNamespace::ForegroundColor* textColor);
        IFACEMETHODIMP put_Color(ABI::AdaptiveNamespace::ForegroundColor textColor);

        IFACEMETHODIMP get_IsSubtle(_Out_ boolean* isSubtle);
        IFACEMETHODIMP put_IsSubtle(boolean isSubtle);

        IFACEMETHODIMP get_FontType(_Out_ ABI::AdaptiveNamespace::FontType* fontType);
        IFACEMETHODIMP put_FontType(ABI::AdaptiveNamespace::FontType fontType);

    protected:
        HRESULT InitializeTextStyleConfig(TextStyleConfig textStyleConfig);

    private:
        ABI::AdaptiveNamespace::TextWeight m_textWeight;
        ABI::AdaptiveNamespace::TextSize m_textSize;
        ABI::AdaptiveNamespace::ForegroundColor m_textColor;
        boolean m_isSubtle;
        ABI::AdaptiveNamespace::FontType m_fontType;
    };
}
