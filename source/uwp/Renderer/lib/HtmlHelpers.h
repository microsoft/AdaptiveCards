#pragma once

HRESULT AddHtmlInlines(ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                       ABI::Windows::Data::Xml::Dom::IXmlNode* node,
                       ABI::Windows::Foundation::Collections::IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines,
                       ABI::AdaptiveNamespace::FontStyle fontStyle);

HRESULT AddTextInlines(ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                       ABI::Windows::Data::Xml::Dom::IXmlNode* node,
                       ABI::AdaptiveNamespace::FontStyle fontStyle,
                       BOOL isBold,
                       BOOL isItalic,
                       ABI::Windows::Foundation::Collections::IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines);

HRESULT AddSingleTextInline(ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                            HSTRING string,
                            ABI::AdaptiveNamespace::FontStyle fontStyle,
                            bool isBold,
                            bool isItalic,
                            ABI::Windows::Foundation::Collections::IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines);
