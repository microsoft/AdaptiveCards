#include "pch.h"
#include "AdaptiveParseContext.h"
#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveActionParserRegistration.h"
#include "AdaptiveFeatureRegistration.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveParseContext::RuntimeClassInitialize() noexcept try
    {
        return RuntimeClassInitialize(nullptr, nullptr, nullptr);
    }
    CATCH_RETURN;

    HRESULT AdaptiveParseContext::RuntimeClassInitialize(
        _In_opt_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementRegistration,
        _In_opt_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionRegistration,
        _In_opt_ ABI::AdaptiveNamespace::IAdaptiveFeatureRegistration* featureRegistration) noexcept try
    {
        if (!elementRegistration)
        {
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveElementParserRegistration>(&m_elementRegistration));
        }
        else
        {
            m_elementRegistration = elementRegistration;
        }

        if (!actionRegistration)
        {
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveActionParserRegistration>(&m_actionRegistration));
        }
        else
        {
            m_actionRegistration = actionRegistration;
        }

        if (!featureRegistration)
        {
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveFeatureRegistration>(&m_featureRegistration));
        }
        else
        {
            m_featureRegistration = featureRegistration;
        }

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveParseContext::get_ElementParsers(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration** value)
    {
        return m_elementRegistration.CopyTo(value);
    }

    HRESULT AdaptiveParseContext::get_ActionParsers(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration** value)
    {
        return m_actionRegistration.CopyTo(value);
    }

    HRESULT AdaptiveParseContext::get_Features(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveFeatureRegistration** value)
    {
        return m_featureRegistration.CopyTo(value);
    }
}
