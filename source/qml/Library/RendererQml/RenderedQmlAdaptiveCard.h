#pragma once

#include "pch.h"

#include "AdaptiveWarning.h"
#include "RenderedQmlAdaptiveCardBase.h"

namespace RendererQml
{
    class RenderedQmlAdaptiveCard : public RenderedQmlAdaptiveCardBase
    {
    public:

        RenderedQmlAdaptiveCard(std::shared_ptr<QmlTag> qmlTag, std::shared_ptr<AdaptiveCards::AdaptiveCard> originatingCard, const std::vector<AdaptiveWarning>& warnings);

        std::shared_ptr<QmlTag> GetResult();

    private:
        std::shared_ptr<QmlTag> m_qml;
    };
}
