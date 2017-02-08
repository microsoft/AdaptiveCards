#include "pch.h"
#include "AdaptiveTextBlock.h"
#include "XamlCardRendererComponent.h"
#include <windows.foundation.collections.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    AdaptiveTextBlock::AdaptiveTextBlock()
    {
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::get_Text(HSTRING* text)
    {
        return HStringReference(this->GetText().c_str()).CopyTo(text);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::put_Text(HSTRING text)
    {
        if (text == nullptr)
        {
            return E_INVALIDARG;
        }
        HString Wrapper;
        RETURN_IF_FAILED(Wrapper.Set(text));
        this->SetText(Wrapper.GetRawBuffer(nullptr));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::get_TextSize(ABI::AdaptiveCards::XamlCardRenderer::TextSize* textSize)
    {
        *textSize = static_cast<ABI::AdaptiveCards::XamlCardRenderer::TextSize>(this->GetTextSize());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::put_TextSize(ABI::AdaptiveCards::XamlCardRenderer::TextSize textSize)
    {
        this->SetTextSize(static_cast<AdaptiveCards::TextSize>(textSize));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::get_TextWeight(ABI::AdaptiveCards::XamlCardRenderer::TextWeight* textWeight)
    {
        *textWeight = static_cast<ABI::AdaptiveCards::XamlCardRenderer::TextWeight>(this->GetTextWeight());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::put_TextWeight(ABI::AdaptiveCards::XamlCardRenderer::TextWeight textWeight)
    {
        this->SetTextWeight(static_cast<AdaptiveCards::TextWeight>(textWeight));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::get_Wrap(boolean* Wrap)
    {
        *Wrap = this->GetWrap();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::put_Wrap(boolean Wrap)
    {
        this->SetWrap(Wrap);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::get_IsSubtle(boolean* IsSubtle)
    {
        *IsSubtle = this->GetIsSubtle();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::put_IsSubtle(boolean IsSubtle)
    {
        this->SetIsSubtle(IsSubtle);
        return S_OK;
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveTextBlock::get_ElementType(ElementType* /*elementType*/)
    {
        return S_OK;
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveTextBlock::put_ElementType(ElementType /*elementType*/)
    {
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::Render(IUIElement** TextBlock)
    {
        *TextBlock = nullptr;

        ComPtr<IInspectable> inspectableTextBlock;
        ComPtr<ITextBlock> textBlock;
        RETURN_IF_FAILED(RoActivateInstance(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock).Get(), inspectableTextBlock.ReleaseAndGetAddressOf()));
        RETURN_IF_FAILED(inspectableTextBlock.As(&textBlock));

        HSTRING text;
        RETURN_IF_FAILED(this->get_Text(&text));
        RETURN_IF_FAILED(textBlock->put_Text(text));

        boolean wrap;
        RETURN_IF_FAILED(this->get_Wrap(&wrap));
        RETURN_IF_FAILED(textBlock->put_TextWrapping(wrap ? TextWrapping::TextWrapping_WrapWholeWords : TextWrapping::TextWrapping_NoWrap));

        // Fill other properties.

        return textBlock->QueryInterface(TextBlock);
    }
}}
