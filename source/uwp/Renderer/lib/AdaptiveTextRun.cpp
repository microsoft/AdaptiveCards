// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextRun.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveTextRun::RuntimeClassInitialize() noexcept
    try
    {
        RuntimeClassInitialize(std::make_shared<TextRun>());
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveTextRun::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::TextRun>& sharedTextRun) noexcept
    try
    {
        m_highlight = sharedTextRun->GetHighlight();
        m_italic = sharedTextRun->GetItalic();
        m_strikethrough = sharedTextRun->GetStrikethrough();
        m_underline = sharedTextRun->GetUnderline();

        RETURN_IF_FAILED(GenerateActionProjection(sharedTextRun->GetSelectAction(), &m_selectAction));
        RETURN_IF_FAILED(AdaptiveTextElement::InitializeTextElement(sharedTextRun));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveTextRun::get_Highlight(boolean* highlight)
    {
        *highlight = m_highlight;
        return S_OK;
    }

    HRESULT AdaptiveTextRun::put_Highlight(boolean highlight)
    {
        m_highlight = highlight;
        return S_OK;
    }

    HRESULT AdaptiveTextRun::get_SelectAction(_COM_Outptr_ IAdaptiveActionElement** action)
    {
        return m_selectAction.CopyTo(action);
    }

    HRESULT AdaptiveTextRun::put_SelectAction(_In_ IAdaptiveActionElement* action)
    {
        m_selectAction = action;
        return S_OK;
    }

    HRESULT AdaptiveTextRun::get_Italic(boolean* italic)
    {
        *italic = m_italic;
        return S_OK;
    }

    HRESULT AdaptiveTextRun::put_Italic(boolean italic)
    {
        m_italic = italic;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveTextRun::get_Strikethrough(boolean* strikethrough)
    {
        *strikethrough = m_strikethrough;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveTextRun::put_Strikethrough(boolean strikethrough)
    {
        m_strikethrough = strikethrough;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveTextRun::get_Underline(boolean* underline)
    {
        *underline = m_underline;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveTextRun::put_Underline(boolean underline)
    {
        m_underline = underline;
        return S_OK;
    }

    HRESULT AdaptiveTextRun::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::TextRun>& sharedModel) noexcept
    try
    {
        std::shared_ptr<AdaptiveSharedNamespace::TextRun> textRun = std::make_shared<AdaptiveSharedNamespace::TextRun>();
        RETURN_IF_FAILED(AdaptiveTextElement::CopyTextElementProperties(*textRun));

        textRun->SetItalic(m_italic);
        textRun->SetStrikethrough(m_strikethrough);
        textRun->SetHighlight(m_highlight);
        textRun->SetUnderline(m_underline);

        if (m_selectAction != nullptr)
        {
            std::shared_ptr<BaseActionElement> sharedAction;
            RETURN_IF_FAILED(GenerateSharedAction(m_selectAction.Get(), sharedAction));
            textRun->SetSelectAction(std::move(sharedAction));
        }

        sharedModel = std::move(textRun);
        return S_OK;
    }
    CATCH_RETURN;
}
