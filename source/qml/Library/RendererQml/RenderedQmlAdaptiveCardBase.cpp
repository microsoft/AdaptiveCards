#include "pch.h"

#include "RenderedQmlAdaptiveCardBase.h"

namespace RendererQml
{

    RenderedQmlAdaptiveCardBase::RenderedQmlAdaptiveCardBase(std::shared_ptr<AdaptiveCards::AdaptiveCard> originatingCard, const std::vector<AdaptiveWarning>& warnings) :
        m_originatingCard(originatingCard), m_warnings(warnings)
    {
    }


    std::shared_ptr<AdaptiveCards::AdaptiveCard> RenderedQmlAdaptiveCardBase::GetOriginatingCard()
    {
        return m_originatingCard;
    }

    const std::vector<AdaptiveWarning>& RenderedQmlAdaptiveCardBase::GetWarnings()
    {
        return m_warnings;
    }

}
