#include "pch.h"
#include "AdaptiveTextBlock.h"
#include "XamlCardRendererComponent.h"
#include <windows.foundation.collections.h>

using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace AdaptiveCards::XamlCardRenderer;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

AdaptiveTextBlock::AdaptiveTextBlock()
{
}

HRESULT AdaptiveTextBlock::get_Text(HSTRING* Text)
{
    return StringToHSTRING(this->GetText(), Text);
}

HRESULT AdaptiveTextBlock::put_Text(HSTRING Text)
{
    std::string out;
    RETURN_IF_FAILED(HSTRINGToString(Text, out));
    this->SetText(out);
    return S_OK;
}

HRESULT AdaptiveTextBlock::get_TextSize(ObjectModel::TextSize* TextSize)
{
    *TextSize = (ObjectModel::TextSize)this->GetTextSize();
    return S_OK;
}

HRESULT AdaptiveTextBlock::put_TextSize(ObjectModel::TextSize TextSize)
{
    this->SetTextSize((AdaptiveCards::TextSize)TextSize);
    return S_OK;
}

HRESULT AdaptiveTextBlock::get_TextWeight(ObjectModel::TextWeight* TextWeight)
{
    *TextWeight = (ObjectModel::TextWeight)this->GetTextWeight();
    return S_OK;
}

HRESULT AdaptiveTextBlock::put_TextWeight(ObjectModel::TextWeight TextWeight)
{
    this->SetTextWeight((AdaptiveCards::TextWeight)TextWeight);
    return S_OK;
}

HRESULT AdaptiveTextBlock::get_Wrap(boolean* Wrap)
{
    *Wrap = this->GetWrap();
    return S_OK;
}

HRESULT AdaptiveTextBlock::put_Wrap(boolean Wrap)
{
    this->SetWrap(Boolify(Wrap));
    return S_OK;
}

HRESULT AdaptiveTextBlock::get_IsSubtle(boolean* IsSubtle)
{
    *IsSubtle = this->GetIsSubtle();
    return S_OK;
}

HRESULT AdaptiveTextBlock::put_IsSubtle(boolean IsSubtle)
{
    this->SetIsSubtle(Boolify(IsSubtle));
    return S_OK;
}

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


