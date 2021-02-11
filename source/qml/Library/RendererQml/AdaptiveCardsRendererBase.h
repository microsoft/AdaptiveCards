#pragma once

#include "pch.h"

#include "AdaptiveElementRenderers.h"

namespace RendererQml
{

    template <class TUIElement, class TContext> class AdaptiveCardsRendererBase
    {
    public:
        AdaptiveCardsRendererBase(const AdaptiveCards::SemanticVersion& supportedVersion) :
            m_hostConfig(std::make_shared<AdaptiveCards::HostConfig>()),
            m_elementRenderers(std::make_shared<AdaptiveElementRenderers<TUIElement, TContext>>()),
            m_supportedSchemaVersion(supportedVersion)
        {
        }

        const AdaptiveCards::SemanticVersion& SupportedSchemaVersion()
        {
            return m_supportedSchemaVersion;
        }


        virtual std::shared_ptr<AdaptiveCards::HostConfig> GetHostConfig()
        {
            return m_hostConfig;
        }

        virtual void SetHostConfig(std::shared_ptr<AdaptiveCards::HostConfig> hostConfig)
        {
            m_hostConfig = hostConfig;
        }

        virtual std::shared_ptr<AdaptiveElementRenderers<TUIElement, TContext>> GetElementRenderers()
        {
            return m_elementRenderers;
        }

        virtual ~AdaptiveCardsRendererBase() = default;

    private:
        AdaptiveCards::SemanticVersion m_supportedSchemaVersion;
        std::shared_ptr<AdaptiveCards::HostConfig> m_hostConfig;
        std::shared_ptr<AdaptiveElementRenderers<TUIElement, TContext>> m_elementRenderers;
    };

}
