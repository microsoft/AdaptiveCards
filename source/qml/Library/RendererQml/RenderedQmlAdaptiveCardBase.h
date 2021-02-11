#pragma once

#include "pch.h"

#include "AdaptiveWarning.h"

namespace RendererQml
{

    class RenderedQmlAdaptiveCardBase
    {
    public:
        RenderedQmlAdaptiveCardBase(std::shared_ptr<AdaptiveCards::AdaptiveCard> originatingCard, const std::vector<AdaptiveWarning>& warnings);

        std::shared_ptr<AdaptiveCards::AdaptiveCard> GetOriginatingCard();
        const std::vector<AdaptiveWarning>& GetWarnings();

    private:
        std::shared_ptr<AdaptiveCards::AdaptiveCard> m_originatingCard;
        std::vector<AdaptiveWarning> m_warnings;
    };

}
