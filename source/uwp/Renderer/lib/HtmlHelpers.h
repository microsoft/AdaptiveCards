#pragma once

HRESULT AddHtmlInlines(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                       _In_ ABI::Windows::Data::Xml::Dom::IXmlNode* node,
                       _In_ ABI::Windows::Foundation::Collections::IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines,
                       ABI::AdaptiveNamespace::FontStyle fontStyle);

HRESULT AddTextInlines(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                       _In_ ABI::Windows::Data::Xml::Dom::IXmlNode* node,
                       ABI::AdaptiveNamespace::FontStyle fontStyle,
                       BOOL isBold,
                       BOOL isItalic,
                       _In_ ABI::Windows::Foundation::Collections::IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines);

HRESULT AddSingleTextInline(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                            _In_ HSTRING string,
                            ABI::AdaptiveNamespace::FontStyle fontStyle,
                            bool isBold,
                            bool isItalic,
                            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines);
