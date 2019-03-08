#include "pch.h"
#include "AdaptiveParagraph.h"
#include "Util.h"
#include "Vector.h"
#include <windows.foundation.collections.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    AdaptiveParagraph::AdaptiveParagraph() { m_inlines = Microsoft::WRL::Make<Vector<IAdaptiveInline*>>(); }

    HRESULT AdaptiveParagraph::RuntimeClassInitialize() noexcept try
    {
        RuntimeClassInitialize(std::make_shared<Paragraph>());
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveParagraph::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::Paragraph>& sharedParagraph) noexcept try
    {
        if (sharedParagraph == nullptr)
        {
            return E_INVALIDARG;
        }

        GenerateInlinesProjection(sharedParagraph->GetInlines(), m_inlines.Get());

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveParagraph::get_Inlines(ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveInline*>** inlines)
    {
        return m_inlines.CopyTo(inlines);
    }

    HRESULT AdaptiveParagraph::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::Paragraph>& sharedModel) noexcept try
    {
        std::shared_ptr<AdaptiveSharedNamespace::Paragraph> paragraph = std::make_shared<AdaptiveSharedNamespace::Paragraph>();

        RETURN_IF_FAILED(GenerateSharedInlines(m_inlines.Get(), paragraph->GetInlines()));

        sharedModel = paragraph;
        return S_OK;
    }
    CATCH_RETURN;
}
