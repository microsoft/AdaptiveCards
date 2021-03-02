#include "pch.h"

#include "RenderedQmlAdaptiveCard.h"

namespace RendererQml
{
    RenderedQmlAdaptiveCard::RenderedQmlAdaptiveCard(std::shared_ptr<QmlTag> qmlTag, std::shared_ptr<AdaptiveCards::AdaptiveCard> originatingCard, const std::vector<AdaptiveWarning>& warnings) :
        RenderedQmlAdaptiveCardBase(originatingCard, warnings), m_qml(qmlTag)
    {
    }

    std::shared_ptr<QmlTag> RenderedQmlAdaptiveCard::GetResult()
    {
        return m_qml;
    }
}
