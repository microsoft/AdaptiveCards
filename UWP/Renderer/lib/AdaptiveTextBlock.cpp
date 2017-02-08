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

namespace AdaptiveCards {
namespace XamlCardRenderer
{

AdaptiveTextBlock::AdaptiveTextBlock() : m_TextBlock(std::make_unique<TextBlock>()) {}

_Use_decl_annotations_
HRESULT AdaptiveTextBlock::get_Text(HSTRING* Text)
{
    return UTF8ToHString(m_TextBlock->GetText(), Text);
}

_Use_decl_annotations_
HRESULT AdaptiveTextBlock::put_Text(HSTRING Text)
{
    std::string out;
    RETURN_IF_FAILED(HStringToUTF8(Text, out));
    m_TextBlock->SetText(out);
    return S_OK;
}

_Use_decl_annotations_
HRESULT AdaptiveTextBlock::get_TextSize(ABI::AdaptiveCards::XamlCardRenderer::TextSize* TextSize)
{
    *TextSize = static_cast<ABI::AdaptiveCards::XamlCardRenderer::TextSize>(m_TextBlock->GetTextSize());
    return S_OK;
}

_Use_decl_annotations_
HRESULT AdaptiveTextBlock::put_TextSize(ABI::AdaptiveCards::XamlCardRenderer::TextSize TextSize)
{
    m_TextBlock->SetTextSize(static_cast<AdaptiveCards::TextSize>(TextSize));
    return S_OK;
}

_Use_decl_annotations_
HRESULT AdaptiveTextBlock::get_TextWeight(ABI::AdaptiveCards::XamlCardRenderer::TextWeight* TextWeight)
{
    *TextWeight = static_cast<ABI::AdaptiveCards::XamlCardRenderer::TextWeight>(m_TextBlock->GetTextWeight());
    return S_OK;
}

_Use_decl_annotations_
HRESULT AdaptiveTextBlock::put_TextWeight(ABI::AdaptiveCards::XamlCardRenderer::TextWeight TextWeight)
{
    m_TextBlock->SetTextWeight(static_cast<AdaptiveCards::TextWeight>(TextWeight));
    return S_OK;
}

_Use_decl_annotations_
HRESULT AdaptiveTextBlock::get_Wrap(boolean* Wrap)
{
    *Wrap = m_TextBlock->GetWrap();
    return S_OK;
}

_Use_decl_annotations_
HRESULT AdaptiveTextBlock::put_Wrap(boolean Wrap)
{
    m_TextBlock->SetWrap(Boolify(Wrap));
    return S_OK;
}

_Use_decl_annotations_
HRESULT AdaptiveTextBlock::get_IsSubtle(boolean* IsSubtle)
{
    *IsSubtle = m_TextBlock->GetIsSubtle();
    return S_OK;
}

_Use_decl_annotations_
HRESULT AdaptiveTextBlock::put_IsSubtle(boolean IsSubtle)
{
    m_TextBlock->SetIsSubtle(Boolify(IsSubtle));
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
}
}
