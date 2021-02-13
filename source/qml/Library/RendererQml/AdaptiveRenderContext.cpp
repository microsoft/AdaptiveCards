#include "pch.h"

#include "AdaptiveRenderContext.h"
#include "AdaptiveFallbackException.h"

namespace RendererQml
{
    AdaptiveRenderContext::AdaptiveRenderContext(std::shared_ptr<AdaptiveCards::HostConfig> hostConfig, std::shared_ptr<AdaptiveElementRenderers<QmlTag, AdaptiveRenderContext>> elementRenderers) :
        m_ancestorHasFallback(false), m_hostConfig(hostConfig), m_elementRenderers(elementRenderers)
    {
        m_renderArgs.SetForegroundColors(m_hostConfig->GetContainerStyles().defaultPalette.foregroundColors);
    }

    std::shared_ptr<QmlTag> AdaptiveRenderContext::Render(std::shared_ptr<AdaptiveCards::AdaptiveCard> element, CardRendererFunction renderFunction)
    {
        std::shared_ptr<QmlTag> qmlTagOut;
        try
        {
            qmlTagOut = renderFunction(element, shared_from_this());
        }
        catch (const AdaptiveFallbackException & e)
        {
            AddWarning(AdaptiveWarning(Code::RenderException, e.what()));
        }
        return qmlTagOut;
    }

    const std::vector<AdaptiveWarning>& AdaptiveRenderContext::GetWarnings()
    {
        return m_warnings;
    }

    void AdaptiveRenderContext::AddWarning(const AdaptiveWarning& warning)
    {
        m_warnings.push_back(warning);
    }

    std::shared_ptr<AdaptiveCards::HostConfig> AdaptiveRenderContext::GetConfig()
    {
        return m_hostConfig;
    }

    std::string AdaptiveRenderContext::GetRGBColor(const std::string& color)
    {
        if (color.length() > 1 && color[0] == '#')
        {
            if (color.length() == 7)
            {
                return Formatter() << "'" << color << "'";
            }
            if (color.length() == 9)
            {
                try
                {
                    const float opacity = static_cast<float>(Utils::HexStrToInt(color.substr(1, 2))) / 255;
                    const int r = Utils::HexStrToInt(color.substr(3, 2));
                    const int g = Utils::HexStrToInt(color.substr(5, 2));
                    const int b = Utils::HexStrToInt(color.substr(7, 2));
                    return Formatter() << "Qt.rgba(" << r << ", " << g << ", " << b << ", " << std::fixed << std::setprecision(2) << opacity << ")";
                }
                catch (const std::exception&)
                {
                    return Formatter() << "'" << color << "'";
                }
            }
        }
        return Formatter() << "'" << color << "'";
    }

    std::string AdaptiveRenderContext::GetLang()
    {
        return m_lang;
    }

    void AdaptiveRenderContext::SetLang(const std::string& lang)
    {
        m_lang = lang;
    }

    void AdaptiveRenderContext::SetOnClickFunction(AdaptiveCardDependency::OnClickFunction onClickFunction)
    {
        m_onClickFunction = onClickFunction;
    }

    AdaptiveCardDependency::OnClickFunction& AdaptiveRenderContext::GetOnClickFunction()
    {
        return m_onClickFunction;
    }
}
