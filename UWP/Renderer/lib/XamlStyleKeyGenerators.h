#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class XamlStyleKeyGenerators
    {
    public:
        static std::wstring GenerateKeyForTextBlock(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextBlock* /*textBlock*/)
        {
            std::wstring styleKey(L"TextBlock");
            // TODO: MSFT:10826544 - Programmatic xaml style generation

            return styleKey;
        }

    };

}}