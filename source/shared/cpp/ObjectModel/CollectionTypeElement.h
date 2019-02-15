#pragma once

#include "pch.h"
#include "BaseCardElement.h"

namespace AdaptiveSharedNamespace
{
    class CollectionTypeElement
    {
    public:
        CollectionTypeElement(ContainerStyle style = ContainerStyle::None,
            VerticalContentAlignment alignment = VerticalContentAlignment::Top);

        ContainerStyle GetStyle() const;
        void SetStyle(const ContainerStyle value);

        VerticalContentAlignment GetVerticalContentAlignment() const;
        void SetVerticalContentAlignment(const VerticalContentAlignment value);

        bool GetPadding() const;
        void SetPadding(const bool value);
        void ConfigPadding(ParseContext& context);

        bool GetBleed() const;
        void SetBleed(const bool value);
        bool GetCanBleed() const;
        void SetCanBleed(const bool value);
        void ConfigBleed(ParseContext& context);

        void SetParentalId(std::string &id);
        std::string GetParentalId(void) const;

    private:
        ContainerStyle m_style;
        VerticalContentAlignment m_verticalContentAlignment;
        bool m_hasPadding;
        bool m_hasBleed;
        bool m_canBleed;
        // id refers to parent to where bleed property should target
        std::string m_parentalId;
    };
}
