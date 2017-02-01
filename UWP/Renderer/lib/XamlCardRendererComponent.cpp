#include "pch.h"
#include "XamlCardRendererComponent.h"

#include <windows.foundation.collections.h>

using namespace AdaptiveCards::XamlCardRenderer;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

XamlCardRenderer::XamlCardRenderer()
{
}

HRESULT XamlCardRenderer::RuntimeClassInitialize()
{
    return S_OK;
}

HRESULT XamlCardRenderer::RenderCardAsXaml(IUIElement** root)
{
    *root = nullptr;

    ComPtr<IInspectable> inspectableGrid;
    ComPtr<IGrid> grid;
    ComPtr<IPanel> gridAsPanel;
    ComPtr<IVector<UIElement*>> gridChildren;
    RETURN_IF_FAILED(RoActivateInstance(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), inspectableGrid.ReleaseAndGetAddressOf()));
    RETURN_IF_FAILED(inspectableGrid.As(&grid));
    RETURN_IF_FAILED(inspectableGrid.As(&gridAsPanel));
    RETURN_IF_FAILED(gridAsPanel->get_Children(gridChildren.GetAddressOf()));

    return grid->QueryInterface(root);
}

HRESULT XamlCardRenderer::RenderCardAsImage()
{
    return S_OK;
}

