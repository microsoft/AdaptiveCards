#include "pch.h"

#include "AdaptiveRenderContext.h"
#include "AdaptiveFallbackException.h"
#include "BaseInputElement.h"
#include "TextBlock.h"

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

	std::shared_ptr<QmlTag> AdaptiveRenderContext::Render(std::shared_ptr<AdaptiveCards::BaseElement> element)
	{
		std::shared_ptr<QmlTag> QmlTagOut;
        const bool oldAncestorHasFallback = m_ancestorHasFallback;
        const bool elementHasFallback = element != nullptr && element->GetFallbackContent() != nullptr && (element->GetFallbackType() != AdaptiveCards::FallbackType::None);
        m_ancestorHasFallback = m_ancestorHasFallback || elementHasFallback;

        try
        {
            if (m_ancestorHasFallback && !element->MeetsRequirements(m_featureRegistration))
            {
                throw AdaptiveFallbackException("Element requirements aren't met");
            }

            // If non-interactive, inputs should just render text
            if (!m_hostConfig->GetSupportsInteractivity() && Utils::IsInstanceOfSmart<AdaptiveCards::BaseInputElement>(element))
            {
                std::shared_ptr< AdaptiveCards::BaseInputElement> input = std::dynamic_pointer_cast<AdaptiveCards::BaseInputElement>(element);
                std::shared_ptr<AdaptiveCards::TextBlock> tb;
                //TODO: This is not supported in c++ shared model. 
                //tb->SetText(input->GetNonInteractiveValue());
                AddWarning(AdaptiveWarning(Code::RenderException, Formatter() << "Rendering non-interactive input element '" << element->GetElementTypeString() << "'"));
                QmlTagOut = Render(tb);
            }

            if (QmlTagOut == nullptr)
            {
                auto renderer = m_elementRenderers->Get(typeid(*element), Utils::IsInstanceOfSmart<AdaptiveCards::BaseElement>(element));
                if (renderer != nullptr)
                {
                    QmlTagOut = renderer(element, shared_from_this());
                }
            }
        }
        catch (const AdaptiveFallbackException&)
        {
            if (!elementHasFallback)
            {
                throw;
            }            
        }

        if (QmlTagOut == nullptr)
        {
            // Since no renderer exists for this element, add warning and render fallback (if available)
            if (element->GetFallbackContent() != nullptr && element->GetFallbackType() != AdaptiveCards::FallbackType::None)
            {
                if (element->GetFallbackType() == AdaptiveCards::FallbackType::Drop)
                {
                    AddWarning(AdaptiveWarning(Code::RenderException, Formatter() << "Dropping element for fallback '" << element->GetElementTypeString() << "'"));
                }
                else if (element->GetFallbackType() == AdaptiveCards::FallbackType::Content && element->GetFallbackContent() != nullptr)
                {
                    // Render fallback content
                    QmlTagOut = Render(element->GetFallbackContent());
                }
            }
            else if (m_ancestorHasFallback)
            {
                throw AdaptiveFallbackException("Fallback to ancestor");
            }
            else
            {
                AddWarning(AdaptiveWarning(Code::RenderException, Formatter() << "No renderer for element '" << element->GetElementTypeString() << "'"));
            }
        }

        m_ancestorHasFallback = oldAncestorHasFallback;
		return QmlTagOut;
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

	const std::shared_ptr<AdaptiveElementRenderers<QmlTag, AdaptiveRenderContext>> AdaptiveRenderContext::GetElementRenderers()
	{
		return m_elementRenderers;
	}

    std::string AdaptiveRenderContext::GetRGBColor(const std::string& color, bool isQml)
    {
        if (color.length() > 1 && color[0] == '#')
        {
            if (color.length() == 7)
            {
                return isQml ? Formatter() << "'" << color << "'" : color;
            }
            if (color.length() == 9)
            {
                try
                {
                    const float opacity = static_cast<float>(Utils::HexStrToInt(color.substr(1, 2))) / 255;
                    const int r = Utils::HexStrToInt(color.substr(3, 2));
                    const int g = Utils::HexStrToInt(color.substr(5, 2));
                    const int b = Utils::HexStrToInt(color.substr(7, 2));
                    return isQml ? Formatter() << "Qt.rgba(" << r << ", " << g << ", " << b << ", " << std::fixed << std::setprecision(2) << opacity << ")" : Formatter() << "rgba(" << r << ", " << g << ", " << b << ", " << std::fixed << std::setprecision(2) << opacity << ")";
                }
                catch (const std::exception&)
                {
                    return isQml ? Formatter() << "'" << color << "'" : color;
                }
            }
        }
        return isQml ? Formatter() << "'" << color << "'" : color;
    }

	std::string AdaptiveRenderContext::GetColor(const AdaptiveCards::ForegroundColor color, bool isSubtle, bool isHighlight, bool isQml)
	{

		AdaptiveCards::ColorConfig colorConfig;
		switch (color)
		{
		case AdaptiveCards::ForegroundColor::Accent:
			colorConfig = m_renderArgs.GetForegroundColors().accent;
			break;
		case AdaptiveCards::ForegroundColor::Good:
			colorConfig = m_renderArgs.GetForegroundColors().good;
			break;
		case AdaptiveCards::ForegroundColor::Warning:
			colorConfig = m_renderArgs.GetForegroundColors().warning;
			break;
		case AdaptiveCards::ForegroundColor::Attention:
			colorConfig = m_renderArgs.GetForegroundColors().attention;
			break;
		case AdaptiveCards::ForegroundColor::Dark:
			colorConfig = m_renderArgs.GetForegroundColors().dark;
			break;
		case AdaptiveCards::ForegroundColor::Light:
			colorConfig = m_renderArgs.GetForegroundColors().light;
			break;
		default:
			colorConfig = m_renderArgs.GetForegroundColors().defaultColor;
			break;
		}

        if (isHighlight)
        {
            return GetRGBColor(isSubtle ? colorConfig.highlightColors.subtleColor : colorConfig.highlightColors.defaultColor, isQml);
        }
        else
        {
            return GetRGBColor(isSubtle ? colorConfig.subtleColor : colorConfig.defaultColor, isQml);
        }
		
	}

    std::string AdaptiveRenderContext::GetLang()
    {
        return m_lang;
    }

    void AdaptiveRenderContext::SetLang(const std::string& lang)
    {
        m_lang = lang;
    }

    const int AdaptiveRenderContext::getContainerCounter()
    {
        return ++m_ContainerCounter;
    }

    const int AdaptiveRenderContext::getImageCounter()
    {
        return ++m_ImageCounter;
    }

	const int AdaptiveRenderContext::getColumnSetCounter()
	{
		return ++m_ColumnSetCounter;
	}

	const int AdaptiveRenderContext::getColumnCounter()
	{
		return ++m_ColumnCounter;
	}

    const int AdaptiveRenderContext::getButtonCounter()
    {
        return ++m_ButtonCounter;
    }

    const int AdaptiveRenderContext::getSelectActionCounter()
    {
        return ++m_SelectActionCounter;
    }

    void AdaptiveRenderContext::setCardRootId(const std::string& rootId)
    {
        m_CardRootId = rootId;
    }

    const std::string AdaptiveRenderContext::getCardRootId()
    {
        return m_CardRootId;
    }

	void AdaptiveRenderContext::addToInputElementList(const std::string& elementId, const std::string& value)
    {
        m_inputElementList[elementId] = value;
    }

    const std::map<std::string, std::string> AdaptiveRenderContext::getInputElementList()
    {
        return m_inputElementList;
    }

	void AdaptiveRenderContext::setCardRootElement(const std::shared_ptr<QmlTag>& rootElement)
	{
		m_CardRootElement = rootElement;
	}

	const std::shared_ptr<QmlTag> AdaptiveRenderContext::getCardRootElement()
	{
		return m_CardRootElement;
	}

	const int AdaptiveRenderContext::getCardWidth()
	{
		return 600;
	}

	void AdaptiveRenderContext::addToSubmitActionButtonList(const std::shared_ptr<QmlTag>& buttonElement, const std::shared_ptr<AdaptiveCards::SubmitAction>& action)
    {
        m_submitActionButtonList[buttonElement] = action;
    }

    const std::map<std::shared_ptr<QmlTag>, std::shared_ptr<AdaptiveCards::SubmitAction>> AdaptiveRenderContext::getSubmitActionButtonList()
    {
        return m_submitActionButtonList;
    }

    void AdaptiveRenderContext::addToShowCardButtonList(const std::shared_ptr<QmlTag>& buttonElement, const std::shared_ptr<AdaptiveCards::ShowCardAction>& action)
    {
        m_showCardButtonList[buttonElement] = action;
    }

    const std::map<std::shared_ptr<QmlTag>, std::shared_ptr<AdaptiveCards::ShowCardAction>> AdaptiveRenderContext::getShowCardButtonList()
    {
        return m_showCardButtonList;
    }

    void AdaptiveRenderContext::clearShowCardButtonList()
    {
        m_showCardButtonList.clear();
    }

    void AdaptiveRenderContext::addToShowCardLoaderComponentList(const std::string& componentId, const std::shared_ptr<AdaptiveCards::ShowCardAction>& action)
    {
        m_showCardLoaderComponentList[componentId] = action;
    }

    const std::map<std::string, std::shared_ptr<AdaptiveCards::ShowCardAction>> AdaptiveRenderContext::getShowCardLoaderComponentList()
    {
        return m_showCardLoaderComponentList;
    }

    void AdaptiveRenderContext::addToTextRunSelectActionList(const std::shared_ptr<QmlTag>& textRunElement, std::map<std::string, std::shared_ptr<AdaptiveCards::BaseActionElement>>& actionList)
    {
        m_textRunSelectActionList[textRunElement] = actionList;
    }

    const std::map<std::shared_ptr<QmlTag>, std::map<std::string, std::shared_ptr<AdaptiveCards::BaseActionElement>>> AdaptiveRenderContext::getTextRunSelectActionList()
    {
        return m_textRunSelectActionList;
    }

    const int AdaptiveRenderContext::getDefaultIdCounter()
    {
        return ++m_DefaultIdCounter;
    }

    void AdaptiveRenderContext::setDefaultIdName(const std::string& defaultId)
    {
        m_defaultId = defaultId;
    }

    const std::string AdaptiveRenderContext::getDefaultIdName()
    {
        return m_defaultId;
    }

    const std::string AdaptiveRenderContext::ConvertToValidId(const std::string& id)
    {
        std::string newId =id;
        newId = Utils::HandleKeywords(Utils::ToLower(newId));

        if (Utils::hasNonAlphaNumeric(newId))
        {
            newId = Formatter() << getDefaultIdName() << "_" << std::to_string(getDefaultIdCounter());
        }

        return newId;
    }
}
