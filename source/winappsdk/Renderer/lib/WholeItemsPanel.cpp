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

using namespace ABI::AdaptiveCards::Rendering::WinUI3;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Shapes;
using namespace ABI::Windows::UI::Xaml::Media;

static const float OutsidePanelY = -1000.0f;
namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    // IFrameworkElementOverrides
    winrt::Windows::Foundation::Size WholeItemsPanel::MeasureOverride(winrt::Windows::Foundation::Size const& availableSize)
    {
        unsigned int count{};
        float currentHeight{};
        float maxDesiredWidth{};
        bool visible{true};

        auto children = this->Children();
        count = children.Size();

        const winrt::Windows::Foundation::Size noVerticalLimit{availableSize.Width, numeric_limits<float>::infinity()};
        auto measuredAvailableSize{availableSize};

        m_visibleCount = count;

        for (uint32_t i = 0; i < count; i++)
        {
            auto child = children.GetAt(i);
            child.Measure(noVerticalLimit);

            if (visible)
            {
                winrt::Windows::Foundation::Size childSize = child.DesiredSize();

                float newHeight = currentHeight + childSize.Height;

                if (newHeight > measuredAvailableSize.Height)
                {
                    const double availableHeightForItem = measuredAvailableSize.Height - currentHeight;
                    bool keepItem = m_isMainPanel && (i == 0); // by default, only keep the first item in the main panel.

                    // Item does not fit
                    // 1. We mark the current panel as truncated
                    //    2.1 If the child is a panel: always
                    //    2.2 If the child is a text block: only if it cannot meet its minlines constraint (default is
                    //    1) 2.3 If the child is a image or a shape (circular cropped image):
                    //            - stretched images might be resized

                    if (auto childAsPanel = child.try_as<rtxaml::Controls::Panel>())
                    {
                        m_isTruncated = true;

                        // There is a tricky scenario here: a subgroup might have asked for more size than available while
                        // Still being able to reduce its size, for example if it has a minSize which can be respected
                        if (!keepItem)
                        {
                            winrt::Windows::Foundation::Size remainingSpace = {measuredAvailableSize.Width, static_cast<float>(availableHeightForItem)};

                            child.Measure(remainingSpace);

                            m_isTruncated = IsAnySubgroupTruncated(childAsPanel);
                        }
                    }
                    if (auto childAsTextBlock = child.try_as<rtxaml::Controls::TextBlock>())
                    {
                        rtxaml::TextWrapping currentWrap = rtxaml::TextWrapping::Wrap;
                        if (childAsTextBlock.TextWrapping() == rtxaml::TextWrapping::NoWrap)
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
                            winrt::Windows::Foundation::Size noLimit{numeric_limits<float>::infinity(), numeric_limits<float>::infinity()};
                            childAsTextBlock.TextWrapping(rtxaml::TextWrapping::NoWrap);
                            childAsTextBlock.Measure(noLimit);
                            childSize = childAsTextBlock.DesiredSize();
                            currentWrap = childAsTextBlock.TextWrapping();

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
                                    rtxaml::IFrameworkElementStatics frameworkElementStatics;
                                    child.ClearValue(frameworkElementStatics.MinHeightProperty());
                                }
                                else
                                {
                                    keepItem = false;
                                    // we must measure it a last time as we have changed its properties
                                    // if we keep it, it will be measured again with the exact remaining space
                                   child.Measure(noVerticalLimit);

                                }
                            }
                            m_isTruncated = !keepItem;
                        }
                    }
                    if (auto childAsImage = child.try_as<rtxaml::Controls::Image>())
                    {
                        if (!HasExplicitSize(childAsImage))
                        {
                            childAsImage.Stretch(rtxaml::Media::Stretch::Uniform);
                            keepItem = true;
                            m_isTruncated = false;
                        }
                        else
                        {
                            m_isTruncated = true;
                        }
                    }
                    if (auto childAsShape = child.try_as<winrt::Windows::UI::Xaml::Shapes::Shape>())
                    {
                        if (!HasExplicitSize(childAsShape))
                        {
                            LayoutCroppedImage(childAsShape, measuredAvailableSize.Width, measuredAvailableSize.Height - currentHeight);
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
                        measuredAvailableSize.Height = measuredAvailableSize.Height - currentHeight;
                        child.Measure(measuredAvailableSize);
                        childSize = child.DesiredSize();

                        m_visibleCount = i + 1;
                        currentHeight = max((currentHeight + childSize.Height), measuredAvailableSize.Height);
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
        if (measuredAvailableSize.Width == numeric_limits<float>::infinity())
        {
            // We use the calculated max desired width of children
            return {maxDesiredWidth, currentHeight};
        }
        else
        {
            // Otherwise we match the fixed width of the container
            return {measuredAvailableSize.Width, currentHeight};
        }
    }

    winrt::Windows::Foundation::Size WholeItemsPanel::ArrangeOverride(winrt::Windows::Foundation::Size const& finalSize)
    {
        float currentHeight {0.0f};
        float extraPaddingPerItem {0.0f};

        auto children = this->Children();
        m_measuredCount = children.Size();

        if (m_stretchableItemCount != 0)
        {
            extraPaddingPerItem = floor((finalSize.Height - m_calculatedSize) / m_stretchableItemCount);
        }
        else
        {
            if (m_verticalContentAlignment == ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment::Center)
            {
                currentHeight = (finalSize.Height - m_calculatedSize) / 2;
            }
            else if (m_verticalContentAlignment == ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment::Bottom)
            {
                currentHeight = finalSize.Height - m_calculatedSize;
            }
        }

        for (uint32_t i = 0; i < m_measuredCount; ++i)
        {
            auto child = children.GetAt(i);
            auto childSize = child.DesiredSize();

            if (i < m_visibleCount)
            {
                float childHeight = childSize.Height;
                float newHeight = currentHeight + childSize.Height;

                if (m_allElementsRendered && IsUIElementInStretchableList(child))
                {
                    childHeight += extraPaddingPerItem;
                    newHeight += extraPaddingPerItem;
                }
                else if (newHeight > finalSize.Height) // If we have truncated the first item newHeight may be greater than finalSize
                {
                    childHeight = finalSize.Height - currentHeight;
                    newHeight = finalSize.Height;
                }
                const winrt::Windows::Foundation::Rect rc = {0.0f, currentHeight, finalSize.Width, childHeight}; // childSize.Width does not respect Text alignment

                child.Arrange(rc);

                currentHeight = newHeight;
            }
            else
            {
                // Arrange the child outside the panel
                const winrt::Windows::Foundation::Rect rc = {0.0f, OutsidePanelY - childSize.Height, childSize.Width, childSize.Height};
                child.Arrange(rc);
            }
        }

        // Now set the clipping region to ensure that items moved away will never be rendered
        // But we allow the items to slightly expand above the panel because we explicitly set negative
        // margins for text on the first line of a tile. Additionally, leave at least as much space on all
        // sides as specified by s_bleedMargin.
       /* ComPtr<IFrameworkElement> spThisAsIFrameworkElement;
        Thickness margin;
        RETURN_IF_FAILED(QueryInterface(IID_PPV_ARGS(&spThisAsIFrameworkElement)));
        RETURN_IF_FAILED(spThisAsIFrameworkElement->get_Margin(&margin));
        Microsoft::WRL::ComPtr<IRectangleGeometry> spClip;
        RETURN_IF_FAILED(
            Windows::Foundation::ActivateInstance(HStringReference(RuntimeClass_Windows_UI_Xaml_Media_RectangleGeometry).Get(), &spClip));
        ComPtr<IUIElement> spThisAsIUIElement;
        RETURN_IF_FAILED(QueryInterface(IID_PPV_ARGS(&spThisAsIUIElement)));
        RETURN_IF_FAILED(spThisAsIUIElement->put_Clip(spClip.Get()));*/

        rtxaml::Thickness margin = this->Margin();
        rtxaml::Media::RectangleGeometry clip;

        const double bleedMargin = static_cast<double>(s_bleedMargin);
        float x0 = static_cast<float>(-max(margin.Left, bleedMargin));
        float y0 = static_cast<float>(-max(margin.Top, bleedMargin));
        float x1 = static_cast<float>(max(margin.Left, bleedMargin) + finalSize.Width + max(margin.Right, bleedMargin));
        float y1 = static_cast<float>(max(margin.Top, bleedMargin) + finalSize.Height + max(margin.Bottom, bleedMargin));
        clip.Rect({x0, y0, x1, y1});

        this->Clip(clip);

        return {finalSize.Width, finalSize.Height};
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
        CATCH_RETURN();
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
            //THROW_IF_FAILED(elementAsFrameworkElement->put_Tag(tagAsInspectable.Get()));
        }

        ++m_stretchableItemCount;
    }

    bool WholeItemsPanel::IsUIElementInStretchableList(rtxaml::UIElement const& element)
    {
        /*ComPtr<IUIElement> localUIElement(element);
        ComPtr<IFrameworkElement> uiElementAsFrameworkElement;
        THROW_IF_FAILED(localUIElement.As(&uiElementAsFrameworkElement));

        ComPtr<IInspectable> tagAsInspectable;
        THROW_IF_FAILED(uiElementAsFrameworkElement->get_Tag(&tagAsInspectable));*/

        if (const auto elementAsFrameworkElement = element.try_as<rtxaml::FrameworkElement>())
        {
            if (const auto tag = elementAsFrameworkElement.Tag())
            {
                if (const auto tagAsElementTagContent = tag.try_as<rtrender::ElementTagContent>())
                {
                    return tagAsElementTagContent.IsStretchable();
                }
            }
        }

        return false;
    }

    void WholeItemsPanel::SetVerticalContentAlignment(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment verticalContentAlignment)
    {
        m_verticalContentAlignment = verticalContentAlignment;
    }

    bool WholeItemsPanel::IsAnySubgroupTruncated(rtxaml::Controls::Panel panel)
    {
        bool childTruncated = false;
        auto children = panel.Children();
        uint32_t size = children.Size();
       
        for (auto child: children)
        {
            // Subgroups (columns) are implemented with WholeItemsPanel
            if (auto childAsWholeItemPanel = child.as<rtrender::WholeItemsPanel>())
            {
                if (childAsWholeItemPanel.IsTruncated())
                {
                    return true;
                }
            }
        }
        return false;
    }

    // As shapes (used for circular cropping) don't resize as a stretched image, we need do to more
    // things manually. Here, we'll resize the shape to fit the smallest dimension
    // (ideally, we should inherit from Ellipse but it is not possible)
    void WholeItemsPanel::LayoutCroppedImage(rtxaml::Shapes::Shape const& shape, double availableWidth, double availableHeight)
    {
        rtxaml::Thickness margins = shape.Margin();
        const double effectiveAvailableWidth = availableWidth - margins.Left - margins.Right;
        const double effectiveAvailableHeight = availableHeight - margins.Top - margins.Bottom;
        const double minSize = min(effectiveAvailableWidth, effectiveAvailableHeight);
        shape.Width(effectiveAvailableWidth);
        shape.Height(effectiveAvailableHeight);
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

    bool WholeItemsPanel::HasExplicitSize(rtxaml::FrameworkElement const& element)
    {
        return !isnan(element.Height()) || !isnan(element.Width());
    }
}
