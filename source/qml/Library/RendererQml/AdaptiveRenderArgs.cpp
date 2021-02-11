#include "AdaptiveRenderArgs.h"

namespace RendererQml
{
    AdaptiveRenderArgs::AdaptiveRenderArgs() :
        m_parentStyle(AdaptiveCards::ContainerStyle::Default),
        m_bleedDirection(BleedDirection::Both),
        m_hasParentWithPadding(true)
    {
    }

    RendererQml::AdaptiveRenderArgs::AdaptiveRenderArgs(const AdaptiveRenderArgs& previousRenderArgs)
    {
        m_parentStyle = previousRenderArgs.m_parentStyle;
        m_foregroundColors = previousRenderArgs.m_foregroundColors;
        m_bleedDirection = previousRenderArgs.m_bleedDirection;
        m_hasParentWithPadding = previousRenderArgs.m_hasParentWithPadding;
    }

    AdaptiveCards::ContainerStyle AdaptiveRenderArgs::GetParentStyle() const
    {
        return m_parentStyle;
    }

    void AdaptiveRenderArgs::SetParentStyle(const AdaptiveCards::ContainerStyle parentStyle)
    {
        m_parentStyle = parentStyle;
    }

    const AdaptiveCards::ColorsConfig& AdaptiveRenderArgs::GetForegroundColors() const
    {
        return m_foregroundColors;
    }

    void AdaptiveRenderArgs::SetForegroundColors(const AdaptiveCards::ColorsConfig& foregroundColors)
    {
        m_foregroundColors = foregroundColors;
    }

    BleedDirection AdaptiveRenderArgs::GetBleedDirection() const
    {
        return m_bleedDirection;
    }

    void AdaptiveRenderArgs::SetBleedDirection(const BleedDirection bleedDirection)
    {
        m_bleedDirection = bleedDirection;
    }

    bool AdaptiveRenderArgs::GetHasParentWithPadding() const
    {
        return m_hasParentWithPadding;
    }

    void AdaptiveRenderArgs::SetHasParentWithPadding(const bool hasParentWithPadding)
    {
        m_hasParentWithPadding = hasParentWithPadding;
    }
}
