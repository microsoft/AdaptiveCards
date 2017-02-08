#include "pch.h"
#include "XamlCardRendererComponent.h"

#include <windows.foundation.collections.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Media;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    XamlCardRenderer::XamlCardRenderer()
    {
    }

    HRESULT XamlCardRenderer::RuntimeClassInitialize()
    {
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::SetRenderOptions(ABI::AdaptiveCards::XamlCardRenderer::RenderOptions /*options*/)
    {
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::SetOverrideStyles(ABI::Windows::UI::Xaml::IResourceDictionary* /*overrideDictionary*/)
    {
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::RenderCardAsXaml(
        IAdaptiveCard* /*adaptiveCard*/, 
        IUIElement** root)
    {
        *root = nullptr;

        // For now, just build a grid with a blue background so that something is visible for app verification
        ComPtr<IInspectable> inspectableGrid;
        ComPtr<IGrid> grid;
        ComPtr<IPanel> gridAsPanel;
        RETURN_IF_FAILED(RoActivateInstance(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), inspectableGrid.ReleaseAndGetAddressOf()));
        RETURN_IF_FAILED(inspectableGrid.As(&grid));
        RETURN_IF_FAILED(inspectableGrid.As(&gridAsPanel));

        ComPtr<IInspectable> inspectableBrush;
        RETURN_IF_FAILED(RoActivateInstance(HStringReference(RuntimeClass_Windows_UI_Xaml_Media_SolidColorBrush).Get(), inspectableBrush.ReleaseAndGetAddressOf()));
        ComPtr<ISolidColorBrush> solidColorBrush;
        RETURN_IF_FAILED(inspectableBrush.As(&solidColorBrush));

        ComPtr<IColorsStatics> colorsStatics;
        GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Colors).Get(), &colorsStatics);

        Color blue;
        colorsStatics->get_Blue(&blue);
        solidColorBrush->put_Color(blue);

        ComPtr<IBrush> blueBrush;
        RETURN_IF_FAILED(solidColorBrush.As(&blueBrush));
        gridAsPanel->put_Background(blueBrush.Get());

        return grid->QueryInterface(root);
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::RenderCardAsImage(
        IAdaptiveCard* /*adaptiveCard*/,
        IAsyncOperation<ImageRenderResult*>** result)
    {
        *result = nullptr;
        return S_OK;
    }
}}
