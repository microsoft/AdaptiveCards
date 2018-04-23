#pragma once

HRESULT AddHtmlInlines(
    ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
    ABI::Windows::Data::Xml::Dom::IXmlNode * node,
    ABI::Windows::UI::Xaml::IXamlBasicObject * basicTextBlock);

HRESULT AddTextInlines(
    ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
    ABI::Windows::Data::Xml::Dom::IXmlNode* node,
    BOOL isBold,
    BOOL isItalic,
    ABI::Windows::UI::Xaml::IXamlBasicObject * basicTextBlock);

HRESULT AddSingleTextInline(
    ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
    HSTRING string,
    bool isBold,
    bool isItalic,
    ABI::Windows::Foundation::Collections::IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines);