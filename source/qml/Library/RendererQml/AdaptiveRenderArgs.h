#pragma once

#include "pch.h"

namespace RendererQml
{
    class AdaptiveRenderArgs
    {
    public:
        AdaptiveRenderArgs();
        AdaptiveRenderArgs(const AdaptiveRenderArgs& previousRenderArgs);

        AdaptiveCards::ContainerStyle GetParentStyle() const;
        void SetParentStyle(const AdaptiveCards::ContainerStyle parentStyle);

        const AdaptiveCards::ColorsConfig& GetForegroundColors() const;
        void SetForegroundColors(const AdaptiveCards::ColorsConfig& foregroundColors);

        BleedDirection GetBleedDirection() const;
        void SetBleedDirection(const BleedDirection bleedDirection);

        bool GetHasParentWithPadding() const;
        void SetHasParentWithPadding(const bool hasParentWithPadding);

    private:
        AdaptiveCards::ContainerStyle   m_parentStyle;
        AdaptiveCards::ColorsConfig     m_foregroundColors;
        BleedDirection                  m_bleedDirection;
        bool                            m_hasParentWithPadding;
    };
}
