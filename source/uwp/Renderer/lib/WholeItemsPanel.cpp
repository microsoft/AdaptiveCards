// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
//
//  Copyright (c) 2014  Microsoft Corporation
//
#include "pch.h"
#include "WholeItemsPanel.h"
#include "XamlHelpers.h"
#include "ElementTagContent.h"

using namespace std;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Shapes;
using namespace ABI::Windows::UI::Xaml::Media;

static const float OutsidePanelY = -1000.0f;
namespace AdaptiveNamespace
{
    HRESULT WholeItemsPanel::RuntimeClassInitialize()
    {
        ComPtr<IPanelFactory> spFactory;
        ComPtr<IInspectable> spInnerInspectable;
        ComPtr<IPanel> spInnerPanel;
        RETURN_IF_FAILED(
            Windows::Foundation::GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Panel).Get(), &spFactory));
        RETURN_IF_FAILED(spFactory->CreateInstance(static_cast<IWholeItemsPanel*>(this),
                                                   spInnerInspectable.GetAddressOf(),
                                                   spInnerPanel.GetAddressOf()));
        RETURN_IF_FAILED(SetComposableBasePointers(spInnerInspectable.Get(), spFactory.Get()));

        return S_OK;
    }

    // IFrameworkElementOverrides
    HRESULT WholeItemsPanel::MeasureOverride(Size availableSize, __RPC__out Size* returnValue)
    {
        unsigned int count{};
        float currentHeight{};
        float maxDesiredWidth{};
        bool visible{true};

        ComPtr<IVector<UIElement*>> spChildren;
        ComPtr<IPanel> spThisAsPanel;
        RETURN_IF_FAILED(QueryInterface(__uuidof(IPanel), reinterpret_cast<void**>(spThisAsPanel.GetAddressOf())));
        RETURN_IF_FAILED(spThisAsPanel->get_Children(spChildren.GetAddressOf()));
        RETURN_IF_FAILED(spChildren->get_Size(&count));

        const Size noVerticalLimit{availableSize.Width, numeric_limits<float>::infinity()};

        m_visibleCount = count;
        for (unsigned int i{}; i < count; ++i)
        {
            ComPtr<IUIElement> spChild;
            RETURN_IF_FAILED(spChildren->GetAt(i, spChild.GetAddressOf()));

            RETURN_IF_FAILED(spChild->Measure(noVerticalLimit));

            if (visible)
            {
                Size childSize;
                RETURN_IF_FAILED(spChild->get_DesiredSize(&childSize));

                float newHeight = currentHeight + childSize.Height;

                if (newHeight > availableSize.Height)
                {
                    const double availableHeightForItem = availableSize.Height - currentHeight;
                    bool keepItem = m_isMainPanel && (i == 0); // by default, only keep the first item in the main panel.

                    // Item does not fit
                    // 1. We mark the current panel as truncated
                    //    2.1 If the child is a panel: always
                    //    2.2 If the child is a text block: only if it cannot meet its minlines constraint (default is
                    //    1) 2.3 If the child is a image or a shape (circular cropped image):
                    //            - stretched images might be resized
                    ComPtr<IPanel> spChildAsPanel;
                    if (SUCCEEDED(spChild.As(&spChildAsPanel)))
                    {
                        m_isTruncated = true;

                        // There is a tricky scenario here: a subgroup might have asked for more size than available while
                        // Still being able to reduce its size, for example if it has a minSize which can be respected
                        if (keepItem == false)
                        {
                            Size remainingSpace = {availableSize.Width, static_cast<float>(availableHeightForItem)};
                            RETURN_IF_FAILED(spChild->Measure(remainingSpace));
                            bool isChildTruncated = false;
                            RETURN_IF_FAILED(IsAnySubgroupTruncated(spChildAsPanel.Get(), &isChildTruncated));
                            keepItem = !isChildTruncated;
                            m_isTruncated = !keepItem;
                        }
                    }
                    ComPtr<ITextBlock> spTextBlock;
                    if (SUCCEEDED(spChild.As(&spTextBlock)))
                    {
                        TextWrapping currentWrap = TextWrapping::TextWrapping_Wrap;
                        RETURN_IF_FAILED(spTextBlock->get_TextWrapping(&currentWrap));
                        if (currentWrap == TextWrapping::TextWrapping_NoWrap)
                        {
                            // If the text already does not wrap, it should not be displayed
                            // Unless it is the first item of the group
                            m_isTruncated = true;
                        }
                        else
                        {
                            // For wrapping TextBlocks, we have to check if the minlines property could be respected
                            // In order to do this, we remove the wrapping:
                            //   1. if the textblock has a min lines constraint, this will remain as it is implemented with MinHeight
                            //   2. if the textblock has no min lines, constraint, this will measure a single line, which is the default minlines
                            const Size noLimit{numeric_limits<float>::infinity(), numeric_limits<float>::infinity()};
                            RETURN_IF_FAILED(spTextBlock->put_TextWrapping(TextWrapping::TextWrapping_NoWrap));
                            RETURN_IF_FAILED(spChild->Measure(noLimit));
                            RETURN_IF_FAILED(spChild->get_DesiredSize(&childSize));
                            RETURN_IF_FAILED(spTextBlock->put_TextWrapping(currentWrap));

                            // If the single line fits, let's keep the textblock
                            // In any case, we keep the first item of the first group
                            if (childSize.Height <= availableHeightForItem)
                            {
                                keepItem = true;
                            }
                            else
                            {
                                if (m_isMainPanel)
                                {
                                    keepItem = true;

                                    // Text did not reach its minHeight property and we have to clear it otherwise
                                    // ellipses won't be displayed correctly...
                                    ComPtr<IFrameworkElementStatics> spFrameworkElementStatics;
                                    ComPtr<IDependencyProperty> spMinHeightProperty;
                                    ComPtr<IDependencyObject> spChildAsDO;
                                    RETURN_IF_FAILED(Windows::Foundation::GetActivationFactory(
                                        HStringReference(RuntimeClass_Windows_UI_Xaml_FrameworkElement).Get(), &spFrameworkElementStatics));
                                    RETURN_IF_FAILED(spFrameworkElementStatics->get_MinHeightProperty(
                                        spMinHeightProperty.GetAddressOf()));
                                    RETURN_IF_FAILED(spChild.As(&spChildAsDO));
                                    RETURN_IF_FAILED(spChildAsDO->ClearValue(spMinHeightProperty.Get()));
                                }
                                else
                                {
                                    keepItem = false;
                                    // we must measure it a last time as we have changed its properties
                                    // if we keep it, it will be measured again with the exact remaining space
                                    RETURN_IF_FAILED(spChild->Measure(noVerticalLimit));
                                }
                            }
                            m_isTruncated = !keepItem;
                        }
                    }
                    ComPtr<IImage> spImage;
                    if (SUCCEEDED(spChild.As(&spImage)))
                    {
                        // it's an inline image
                        // If the image is stretched, it might be adapted to the available size
                        ComPtr<IFrameworkElement> spChildFE;
                        RETURN_IF_FAILED(spChild.As(&spChildFE));
                        if (!HasExplicitSize(spChildFE.Get()))
                        {
                            // Image has no explicit size: we will try to resize it uniformly
                            RETURN_IF_FAILED(spImage->put_Stretch(ABI::Windows::UI::Xaml::Media::Stretch::Stretch_Uniform));
                            keepItem = true;
                            m_isTruncated = false;
                        }
                        else
                        {
                            // Image has host specified desired size, cannot stretch. It is definitely truncated
                            m_isTruncated = true;
                        }
                    }
                    ComPtr<IShape> spShape;
                    if (SUCCEEDED(spChild.As(&spShape)))
                    {
                        ComPtr<IFrameworkElement> spChildFE;
                        RETURN_IF_FAILED(spChild.As(&spChildFE));
                        if (!HasExplicitSize(spChildFE.Get()))
                        {
                            RETURN_IF_FAILED(LayoutCroppedImage(spShape.Get(), availableSize.Width, availableSize.Height - currentHeight));
                            keepItem = true;
                            m_isTruncated = false;
                        }
                        else
                        {
                            m_isTruncated = true;
                        }
                    }

                    if (keepItem)
                    {
                        // Let's simply give the child the remaining space
                        availableSize.Height = availableSize.Height - currentHeight;

                        RETURN_IF_FAILED(spChild->Measure(availableSize));
                        RETURN_IF_FAILED(spChild->get_DesiredSize(&childSize));

                        m_visibleCount = i + 1;
                        currentHeight = max((currentHeight + childSize.Height), availableSize.Height);
                        maxDesiredWidth = max(childSize.Width, maxDesiredWidth);
                    }
                    else
                    {
                        // Only display previous items
                        m_visibleCount = i;
                    }
                    visible = false;
                    continue;
                }
                currentHeight = newHeight;
                maxDesiredWidth = max(childSize.Width, maxDesiredWidth);
            }
        }

        m_calculatedSize = currentHeight;
        if (m_visibleCount == count)
        {
            m_allElementsRendered = true;
        }
        else // In the first pass, all the contents will always fit
        {
            m_allElementsRendered = false;
        }

        // If inside an infinity/auto width container
        if (availableSize.Width == numeric_limits<float>::infinity())
        {
            // We use the calculated max desired width of children
            *returnValue = {maxDesiredWidth, currentHeight};
        }
        else
        {
            // Otherwise we match the fixed width of the container
            *returnValue = {availableSize.Width, currentHeight};
        }
        return S_OK;
    }

    HRESULT WholeItemsPanel::ArrangeOverride(Size finalSize, __RPC__out Size* returnValue)
    {
        float currentHeight{};
        ComPtr<IVector<UIElement*>> children;

        ComPtr<IPanel> spThisAsPanel;
        RETURN_IF_FAILED(QueryInterface(__uuidof(IPanel), reinterpret_cast<void**>(spThisAsPanel.GetAddressOf())));
        RETURN_IF_FAILED(spThisAsPanel->get_Children(children.GetAddressOf()));
        RETURN_IF_FAILED(children->get_Size(&m_measuredCount));

        float extraPaddingPerItem{};
        if (m_stretchableItemCount != 0)
        {
            extraPaddingPerItem = floor((finalSize.Height - m_calculatedSize) / m_stretchableItemCount);
        }
        else
        {
            if (m_verticalContentAlignment == ABI::AdaptiveNamespace::VerticalContentAlignment::Center)
            {
                currentHeight = (finalSize.Height - m_calculatedSize) / 2;
            }
            else if (m_verticalContentAlignment == ABI::AdaptiveNamespace::VerticalContentAlignment::Bottom)
            {
                currentHeight = finalSize.Height - m_calculatedSize;
            }
        }

        for (unsigned int i = 0; i < m_measuredCount; ++i)
        {
            ComPtr<IUIElement> child;
            RETURN_IF_FAILED(children->GetAt(i, child.GetAddressOf()));

            Size childSize;
            RETURN_IF_FAILED(child->get_DesiredSize(&childSize));

            if (i < m_visibleCount)
            {
                float childHeight = childSize.Height;
                float newHeight = currentHeight + childSize.Height;

                if (m_allElementsRendered && IsUIElementInStretchableList(child.Get()))
                {
                    childHeight += extraPaddingPerItem;
                    newHeight += extraPaddingPerItem;
                }
                else if (newHeight > finalSize.Height) // If we have truncated the first item newHeight may be greater than finalSize
                {
                    childHeight = finalSize.Height - currentHeight;
                    newHeight = finalSize.Height;
                }
                const Rect rc = {0.0f, currentHeight, finalSize.Width, childHeight}; // childSize.Width does not respect Text alignment
                RETURN_IF_FAILED(child->Arrange(rc));

                currentHeight = newHeight;
            }
            else
            {
                // Arrange the child outside the panel
                const Rect rc = {0.0f, OutsidePanelY - childSize.Height, childSize.Width, childSize.Height};
                RETURN_IF_FAILED(child->Arrange(rc));
            }
        }

        // Now set the clipping region to ensure that items moved away will never be rendered
        // But we allow the items to slightly expand above the panel because we explicitly set negative
        // margins for text on the first line of a tile. Additionally, leave at least as much space on all
        // sides as specified by s_bleedMargin.
        ComPtr<IFrameworkElement> spThisAsIFrameworkElement;
        Thickness margin;
        RETURN_IF_FAILED(QueryInterface(IID_PPV_ARGS(&spThisAsIFrameworkElement)));
        RETURN_IF_FAILED(spThisAsIFrameworkElement->get_Margin(&margin));
        Microsoft::WRL::ComPtr<IRectangleGeometry> spClip;
        RETURN_IF_FAILED(
            Windows::Foundation::ActivateInstance(HStringReference(RuntimeClass_Windows_UI_Xaml_Media_RectangleGeometry).Get(), &spClip));
        ComPtr<IUIElement> spThisAsIUIElement;
        RETURN_IF_FAILED(QueryInterface(IID_PPV_ARGS(&spThisAsIUIElement)));
        RETURN_IF_FAILED(spThisAsIUIElement->put_Clip(spClip.Get()));

        float x0 = static_cast<float>(-max(margin.Left, s_bleedMargin));
        float y0 = static_cast<float>(-max(margin.Top, s_bleedMargin));
        float x1 = static_cast<float>(max(margin.Left, s_bleedMargin) + finalSize.Width + max(margin.Right, s_bleedMargin));
        float y1 = static_cast<float>(max(margin.Top, s_bleedMargin) + finalSize.Height + max(margin.Bottom, s_bleedMargin));
        RETURN_IF_FAILED(spClip->put_Rect({x0, y0, x1, y1}));

        *returnValue = {finalSize.Width, finalSize.Height};
        return S_OK;
    }

    HRESULT WholeItemsPanel::OnApplyTemplate(void)
    {
        // Nothing special to do here
        return S_OK;
    }

    // Method used inside the component to reduce the number of temporary allocations
    _Check_return_ HRESULT WholeItemsPanel::AppendAltText(_Inout_ std::wstring& buffer)
    {
        ComPtr<IPanel> spThisAsPanel;
        ComPtr<IVector<UIElement*>> spChildren;
        RETURN_IF_FAILED(QueryInterface(__uuidof(IPanel), reinterpret_cast<void**>(spThisAsPanel.GetAddressOf())));
        RETURN_IF_FAILED(spThisAsPanel->get_Children(spChildren.GetAddressOf()));

        unsigned int count = m_visibleCount;
        if (m_adaptiveHeight)
        {
            // If we are rendering stuff in adaptive height mode, we don't
            // care which of them are visible or not.
            RETURN_IF_FAILED(spChildren->get_Size(&count));
        }

        for (unsigned int i = 0; i < count; i++)
        {
            ComPtr<IUIElement> spChild;
            RETURN_IF_FAILED(spChildren->GetAt(i, spChild.GetAddressOf()));
            RETURN_IF_FAILED(AppendAltTextToUIElement(spChild.Get(), buffer));
        }

        return S_OK;
    }

    HRESULT WholeItemsPanel::GetAltText(__RPC__out HSTRING* pResult) noexcept
    {
        try
        {
            wstring buffer;
            RETURN_IF_FAILED(AppendAltText(buffer));
            return WindowsCreateString(buffer.c_str(), static_cast<unsigned int>(buffer.length()), pResult);
        }
        CATCH_RETURN;
    }

    HRESULT WholeItemsPanel::IsAllContentClippedOut(__RPC__out boolean* pResult)
    {
        *pResult = ((m_measuredCount > 0) && (m_visibleCount == 0));
        return S_OK;
    }

    HRESULT WholeItemsPanel::IsTruncated(__RPC__out boolean* pResult)
    {
        *pResult = m_isTruncated;
        return S_OK;
    }

    void WholeItemsPanel::SetAdaptiveHeight(bool value) { m_adaptiveHeight = value; }

    UINT WholeItemsPanel::s_bleedMargin = 0;
    void WholeItemsPanel::SetBleedMargin(UINT bleedMargin)
    {
        // Bleed margin is the extent to which the content may "bleed" out of the panel on the left and right. It is
        // used to ensure that the clip rectangle doesn't clip off bleeding content.
        s_bleedMargin = bleedMargin;
    }

    void WholeItemsPanel::SetMainPanel(bool value) { m_isMainPanel = value; }

    void WholeItemsPanel::AddElementToStretchablesList(_In_ IUIElement* element)
    {
        ComPtr<IUIElement> localElement(element);
        ComPtr<IFrameworkElement> elementAsFrameworkElement;
        THROW_IF_FAILED(localElement.As(&elementAsFrameworkElement));

        ComPtr<IInspectable> tagAsInspectable;
        THROW_IF_FAILED(elementAsFrameworkElement->get_Tag(&tagAsInspectable));

        ComPtr<IElementTagContent> elementTagContent;
        if (tagAsInspectable != nullptr)
        {
            THROW_IF_FAILED(tagAsInspectable.As(&elementTagContent));
            THROW_IF_FAILED(elementTagContent->put_IsStretchable(true));
        }
        else
        {
            ComPtr<IElementTagContent> tagContent;
            THROW_IF_FAILED(MakeAndInitialize<ElementTagContent>(&tagContent));

            THROW_IF_FAILED(tagContent->put_IsStretchable(true));

            THROW_IF_FAILED(tagContent.As(&tagAsInspectable));
            THROW_IF_FAILED(elementAsFrameworkElement->put_Tag(tagAsInspectable.Get()));
        }

        ++m_stretchableItemCount;
    }

    bool WholeItemsPanel::IsUIElementInStretchableList(_In_ IUIElement* element)
    {
        ComPtr<IUIElement> localUIElement(element);
        ComPtr<IFrameworkElement> uiElementAsFrameworkElement;
        THROW_IF_FAILED(localUIElement.As(&uiElementAsFrameworkElement));

        ComPtr<IInspectable> tagAsInspectable;
        THROW_IF_FAILED(uiElementAsFrameworkElement->get_Tag(&tagAsInspectable));

        boolean isStretchable = false;
        if (tagAsInspectable != nullptr)
        {
            ComPtr<AdaptiveNamespace::IElementTagContent> tagContent;
            THROW_IF_FAILED(tagAsInspectable.As(&tagContent));
            THROW_IF_FAILED(tagContent->get_IsStretchable(&isStretchable));
        }

        return isStretchable;
    }

    void WholeItemsPanel::SetVerticalContentAlignment(_In_ ABI::AdaptiveNamespace::VerticalContentAlignment verticalContentAlignment)
    {
        m_verticalContentAlignment = verticalContentAlignment;
    }

    _Check_return_ HRESULT WholeItemsPanel::IsAnySubgroupTruncated(_In_ ABI::Windows::UI::Xaml::Controls::IPanel* pPanel,
                                                                   _Out_ bool* childTruncated)
    {
        *childTruncated = false;
        ComPtr<IVector<UIElement*>> spChildren;
        unsigned int size = 0;
        RETURN_IF_FAILED(pPanel->get_Children(spChildren.GetAddressOf()));
        RETURN_IF_FAILED(spChildren->get_Size(&size));
        for (unsigned int i = 0; i < size; ++i)
        {
            ComPtr<IUIElement> spChild;
            ComPtr<IWholeItemsPanel> spWholeItemPanel;
            boolean isChildTruncated = false;
            RETURN_IF_FAILED(spChildren->GetAt(i, spChild.GetAddressOf()));
            // Subgroups (columns) are implemented with WholeItemsPanel
            if (SUCCEEDED(spChild.As(&spWholeItemPanel)))
            {
                RETURN_IF_FAILED(spWholeItemPanel->IsTruncated(&isChildTruncated));
                if (isChildTruncated)
                {
                    // No need to continue the iteration
                    *childTruncated = true;
                    return S_OK;
                }
            }
        }
        return S_OK;
    }

    // As shapes (used for circular cropping) don't resize as a stretched image, we need do to more
    // things manually. Here, we'll resize the shape to fit the smallest dimension
    // (ideally, we should inherit from Ellipse but it is not possible)
    _Check_return_ HRESULT WholeItemsPanel::LayoutCroppedImage(_In_ IShape* pShape, _In_ double availableWidth, _In_ double availableHeight)
    {
        ComPtr<IFrameworkElement> spFrameworkElement;
        ABI::Windows::UI::Xaml::VerticalAlignment valign;
        ABI::Windows::UI::Xaml::HorizontalAlignment halign;
        Thickness margins;
        RETURN_IF_FAILED(pShape->QueryInterface(spFrameworkElement.GetAddressOf()));
        RETURN_IF_FAILED(spFrameworkElement->get_HorizontalAlignment(&halign));
        RETURN_IF_FAILED(spFrameworkElement->get_VerticalAlignment(&valign));
        RETURN_IF_FAILED(spFrameworkElement->get_Margin(&margins));
        const double effectiveAvailableWidth = availableWidth - margins.Left - margins.Right;
        const double effectiveAvailableHeight = availableHeight - margins.Top - margins.Bottom;
        const double minSize = min(effectiveAvailableWidth, effectiveAvailableHeight);
        RETURN_IF_FAILED(spFrameworkElement->put_Width(minSize));
        RETURN_IF_FAILED(spFrameworkElement->put_Height(minSize));

        return S_OK;
    }

    void WholeItemsPanel::AppendText(_In_ HSTRING hText, _Inout_ std::wstring& buffer)
    {
        if (buffer.length() > 0)
        {
            buffer.push_back(L'\n');
        }
        buffer.append(WindowsGetStringRawBuffer(hText, nullptr));
    }

    _Check_return_ HRESULT WholeItemsPanel::GetAltAsString(_In_ IUIElement* pElement, _Out_ HSTRING* pResult)
    {
        *pResult = nullptr;
        ComPtr<IDependencyObject> spDependencyObject;
        if (SUCCEEDED(pElement->QueryInterface(spDependencyObject.GetAddressOf())))
        {
            ComPtr<Automation::IAutomationPropertiesStatics> automationStatics;
            RETURN_IF_FAILED(
                ::GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Automation_AutomationProperties).Get(),
                                       &automationStatics));
            RETURN_IF_FAILED(automationStatics->GetName(spDependencyObject.Get(), pResult));
        }
        return S_OK;
    }

    // Creates the Alt Text
    _Check_return_ HRESULT WholeItemsPanel::AppendAltTextToUIElement(_In_ IUIElement* pUIElement, _Inout_ std::wstring& buffer)
    {
        ComPtr<ITextBlock> spTextBlock;

        if (SUCCEEDED(pUIElement->QueryInterface(spTextBlock.GetAddressOf())))
        {
            HString hText;
            RETURN_IF_FAILED(spTextBlock->get_Text(hText.GetAddressOf()));
            AppendText(hText.Get(), buffer);
            return S_OK;
        }

        ComPtr<IWholeItemsPanel> spWholeItemsPanel;
        if (SUCCEEDED(pUIElement->QueryInterface(spWholeItemsPanel.GetAddressOf())))
        {
            // This cast is safe because WinRT only does aggregation
            WholeItemsPanel* pPanelNoRef = reinterpret_cast<WholeItemsPanel*>(spWholeItemsPanel.Get());
            RETURN_IF_FAILED(pPanelNoRef->AppendAltText(buffer));
            return S_OK;
        }

        ComPtr<IImage> spImage;
        if (SUCCEEDED(pUIElement->QueryInterface(spImage.GetAddressOf())))
        {
            HString hAltText;
            RETURN_IF_FAILED(GetAltAsString(pUIElement, hAltText.GetAddressOf()));
            if (*hAltText.GetRawBuffer(nullptr))
            {
                AppendText(hAltText.Get(), buffer);
            }
            return S_OK;
        }

        ComPtr<IShape> spShape;
        if (SUCCEEDED(pUIElement->QueryInterface(spShape.GetAddressOf())))
        {
            HString hAltText;
            RETURN_IF_FAILED(GetAltAsString(pUIElement, hAltText.GetAddressOf()));
            if (*hAltText.GetRawBuffer(nullptr))
            {
                AppendText(hAltText.Get(), buffer);
            }
            return S_OK;
        }

        ComPtr<IPanel> spPanel;
        if (SUCCEEDED(pUIElement->QueryInterface(spPanel.GetAddressOf())))
        {
            ComPtr<IVector<UIElement*>> spChildren;
            RETURN_IF_FAILED(spPanel->get_Children(spChildren.GetAddressOf()));
            unsigned int count;
            RETURN_IF_FAILED(spChildren->get_Size(&count));
            for (unsigned int i = 0; i < count; i++)
            {
                ComPtr<IUIElement> spChild;
                RETURN_IF_FAILED(spChildren->GetAt(i, spChild.GetAddressOf()));
                RETURN_IF_FAILED(AppendAltTextToUIElement(spChild.Get(), buffer));
            }
            return S_OK;
        }

        ComPtr<IBorder> spBorder;
        if (SUCCEEDED(pUIElement->QueryInterface(spBorder.GetAddressOf())))
        {
            ComPtr<IUIElement> spChild;
            RETURN_IF_FAILED(spBorder->get_Child(spChild.GetAddressOf()));
            RETURN_IF_FAILED(AppendAltTextToUIElement(spChild.Get(), buffer));
            return S_OK;
        }

        return S_OK;
    }

    bool WholeItemsPanel::HasExplicitSize(_In_ IFrameworkElement* element)
    {
        DOUBLE definedImageHeight;
        element->get_Height(&definedImageHeight);
        DOUBLE definedImageWidth;
        element->get_Height(&definedImageWidth);

        return !isnan(definedImageHeight) || !isnan(definedImageWidth);
    }
}
