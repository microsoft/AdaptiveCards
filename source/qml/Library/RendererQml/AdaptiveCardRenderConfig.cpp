#include "AdaptiveCardRenderConfig.h"

namespace RendererQml
{
   
    AdaptiveCardRenderConfig::AdaptiveCardRenderConfig(bool isDarkMode)
        : m_isDark(isDarkMode)
    {
    }

    bool AdaptiveCardRenderConfig::isDarkMode() const
    {
        return m_isDark;
    }

    InputTextConfig AdaptiveCardRenderConfig::getInputTextConfig() const
    {
        return m_textInputConfig;
    }

    void AdaptiveCardRenderConfig::setInputTextConfig(InputTextConfig config)
    {
        m_textInputConfig = config;
    }
}
