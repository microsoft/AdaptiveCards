#pragma once

HRESULT AddHtmlInlines(
    ABI::AdaptiveNamespaceRef::IAdaptiveRenderContext* renderContext,
    ABI::Windows::Data::Xml::Dom::IXmlNode * node,
    ABI::Windows::Foundation::Collections::IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines);

HRESULT AddTextInlines(
    ABI::AdaptiveNamespaceRef::IAdaptiveRenderContext* renderContext,
    ABI::Windows::Data::Xml::Dom::IXmlNode* node,
    BOOL isBold,
    BOOL isItalic,
    ABI::Windows::Foundation::Collections::IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines);