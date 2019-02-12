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

    private:
        ContainerStyle m_style;
        VerticalContentAlignment m_verticalContentAlignment;
        bool m_hasPadding;
    };
}
