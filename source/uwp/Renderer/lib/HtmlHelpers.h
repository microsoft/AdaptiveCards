#pragma once

HRESULT AddHtmlInlines(
    ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
    ABI::Windows::Data::Xml::Dom::IXmlNode * node,
    ABI::Windows::UI::Xaml::IXamlBasicObject * basicInlines);

HRESULT AddTextInlines(
    ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
    ABI::Windows::Data::Xml::Dom::IXmlNode* node,
    BOOL isBold,
    BOOL isItalic,
    ABI::Windows::UI::Xaml::IXamlBasicObject * basicInlines);

HRESULT AddSingleTextInline(
    ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
    HSTRING string,
    bool isBold,
    bool isItalic,
    ABI::Windows::UI::Xaml::IXamlBasicObject * basicInlines);