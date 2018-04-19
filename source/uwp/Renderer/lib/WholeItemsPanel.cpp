//
//  Copyright (c) 2014  Microsoft Corporation
//
#include "pch.h"
#include "WholeItemsPanel.h"
#include "XamlHelpers.h"

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
AdaptiveNamespaceStart
    HRESULT WholeItemsPanel::RuntimeClassInitialize()
    {
        ComPtr<IPanelFactory> spFactory;
        ComPtr<IInspectable> spInnerInspectable;
        ComPtr<IPanel> spInnerPanel;
        RETURN_IF_FAILED(Windows::Foundation::GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Panel).Get(), &spFactory));
        RETURN_IF_FAILED(spFactory->CreateInstance(static_cast<IWholeItemsPanel*>(this), spInnerInspectable.GetAddressOf(), spInnerPanel.GetAddressOf()));
        RETURN_IF_FAILED(SetComposableBasePointers(spInnerInspectable.Get(), spFactory.Get()));

        return S_OK;
    }

    // IFrameworkElementOverrides
    HRESULT WholeItemsPanel::MeasureOverride(Size availableSize, __RPC__out Size *returnValue)
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

        const Size noVerticalLimit{ availableSize.Width, numeric_limits<float>::infinity() };

        unsigned int stretchableCount{};
        m_visibleCount = count;
        for (unsigned int i{}; i < count; ++i)
        {
            ComPtr<IUIElement> spChild;
            RETURN_IF_FAILED(spChildren->GetAt(i, spChild.GetAddressOf()));
            
            // If the child is a column it may have stretchable items, so return the column height to auto resize itself
            ComPtr<IGrid> spChildAsGrid;
            if (SUCCEEDED(spChild.As(&spChildAsGrid)))
            {
                if (GridIsAColumnSet(spChildAsGrid.Get()))
                {
                    ComPtr<IPanel> spChildAsPanel;
                    RETURN_IF_FAILED(spChildAsGrid.As(&spChildAsPanel));

                    ComPtr<IVector<UIElement*>> columns;
                    RETURN_IF_FAILED(spChildAsPanel->get_Children(columns.ReleaseAndGetAddressOf()));
                    double maxHeight{};

                    unsigned int columnCount{};
                    RETURN_IF_FAILED(columns->get_Size(&columnCount));
                    for (unsigned int j{}; j < columnCount; ++j)
                    {
                        ComPtr<IUIElement> column;
                        RETURN_IF_FAILED(columns->GetAt(j, column.GetAddressOf()));

                        ComPtr<IFrameworkElement> columnAsFrameworkElement;
                        RETURN_IF_FAILED(column.As(&columnAsFrameworkElement));

                        RETURN_IF_FAILED(columnAsFrameworkElement->put_Height(NAN));
                    }
                }
            }
            
            if (IsUIElementInStretchableList(spChild.Get()))
            {
                ++stretchableCount;
                ComPtr<IFrameworkElement> spChildAsFrameworkElement;
                if (SUCCEEDED(spChild.As(&spChildAsFrameworkElement)))
                {
                    RETURN_IF_FAILED(spChildAsFrameworkElement->put_Height(NAN));
                }
            }

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
                    //    2.2 If the child is a text block: only if it cannot meet its minlines constraint (default is 1)
                    //    2.3 If the child is a image or a shape (circular cropped image):
                    //            - stretched images might be resized
                    ComPtr<IPanel> spChildAsPanel;
                    if (SUCCEEDED(spChild.As(&spChildAsPanel)))
                    {
                        m_isTruncated = true;

                        // There is a tricky scenario here: a subgroup might have asked for more size than available while
                        // Still being able to reduce its size, for example if it has a minSize which can be respected
                        if (keepItem == false)
                        {
                            Size remainingSpace = { availableSize.Width, static_cast<float>(availableHeightForItem) };
                            RETURN_IF_FAILED(spChild->Measure(remainingSpace));
                            bool isChildTruncated = false;
                            RETURN_IF_FAILED(IsAnySubgroupTruncated(spChildAsPanel.Get(), &isChildTruncated));
                            keepItem = !isChildTruncated;
                            m_isTruncated = keepItem;
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
                            const Size noLimit{ numeric_limits<float>::infinity(), numeric_limits<float>::infinity() };
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
                                    RETURN_IF_FAILED(Windows::Foundation::GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_FrameworkElement).Get(), &spFrameworkElementStatics));
                                    RETURN_IF_FAILED(spFrameworkElementStatics->get_MinHeightProperty(spMinHeightProperty.GetAddressOf()));
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
                else
                {
                    currentHeight = newHeight;
                }
                currentHeight = newHeight;
                maxDesiredWidth = max(childSize.Width, maxDesiredWidth);
            }
        }

        // If the available size was giving infinite when building the card, then once all the elements are placed the available size is the size of all the elements placed
        if (availableSize.Height == numeric_limits<float>::infinity())
        {
            availableSize.Height = currentHeight;
        }

        // Second pass: Check if any of the elements is a Grid, we cant modify the Measure method for those as I dont know how the Grids work internally
        for (unsigned int i{}; i < count; ++i)
        {
            ComPtr<IUIElement> spChild;
            RETURN_IF_FAILED(spChildren->GetAt(i, spChild.GetAddressOf()));
        
            // check if the child is a Grid
            ComPtr<IGrid> childAsGrid;
            if (SUCCEEDED(spChild.As(&childAsGrid)))
            {
                if (GridIsAColumnSet(childAsGrid.Get()))
                {
                    ComPtr<IPanel> childAsPanel;
                    RETURN_IF_FAILED(childAsGrid.As(&childAsPanel));
                    ComPtr<IVector<UIElement*>> columns;
                    RETURN_IF_FAILED(childAsPanel->get_Children(columns.ReleaseAndGetAddressOf()));
                    double maxHeight{};

                    unsigned int columnCount{};
                    RETURN_IF_FAILED(columns->get_Size(&columnCount));
                    for (unsigned int j{}; j < columnCount; ++j)
                    {
                        ComPtr<IUIElement> column;
                        RETURN_IF_FAILED(columns->GetAt(j, column.GetAddressOf()));
                        Size columnSize;
                        RETURN_IF_FAILED(column->get_DesiredSize(&columnSize));
                        maxHeight = max(maxHeight, columnSize.Height);
                    }

                    for (unsigned int j{}; j < columnCount; ++j)
                    {
                        ComPtr<IUIElement> column;
                        RETURN_IF_FAILED(columns->GetAt(j, column.GetAddressOf()));

                        Size columnDesiredSize;
                        RETURN_IF_FAILED(column->get_DesiredSize(&columnDesiredSize));
                        columnDesiredSize.Height = static_cast<FLOAT>(maxHeight);

                        ComPtr<IFrameworkElement> columnAsFrameworkElement;
                        RETURN_IF_FAILED(column.As(&columnAsFrameworkElement));

                        RETURN_IF_FAILED(columnAsFrameworkElement->put_Height(columnDesiredSize.Height));
                        RETURN_IF_FAILED(column->Measure(columnDesiredSize));
                        RETURN_IF_FAILED(column->get_DesiredSize(&columnDesiredSize));
                    }
                }
            }
        }

        // Third pass: let the stretchable elements get the space they need
        // If all the elements were rendered, at least one item may be stretched and the height is defined
        if ((count == m_visibleCount) && (stretchableCount != 0) && (maxDesiredWidth != 0))
        {
            // availableSpace.height must be changed when a specific height can be defined for a card
            double emptyTrailingSpace = availableSize.Height - currentHeight;
            double extraPaddingPerItem = floor(emptyTrailingSpace / stretchableCount);
            // Stretching so increase the height to stretch the container
            currentHeight = availableSize.Height;

            for (unsigned int i{}; i < count; ++i)
            {
                ComPtr<IUIElement> spChild;
                RETURN_IF_FAILED(spChildren->GetAt(i, spChild.GetAddressOf()));
                if (visible && IsUIElementInStretchableList(spChild.Get()))
                {
                    Size childSize{ maxDesiredWidth, numeric_limits<float>::infinity() };
                    RETURN_IF_FAILED(spChild->Measure(childSize));

                    RETURN_IF_FAILED(spChild->get_DesiredSize(&childSize));
                    
                    childSize.Height = childSize.Height + extraPaddingPerItem;

                    ComPtr<IFrameworkElement> frameworkElement;
                    RETURN_IF_FAILED(spChild.As(&frameworkElement));
                    RETURN_IF_FAILED(frameworkElement->put_Height(childSize.Height));
                    RETURN_IF_FAILED(spChild->Measure(childSize));
                    RETURN_IF_FAILED(spChild->get_DesiredSize(&childSize));
                }
            }

        }

        // If inside an infinity/auto width container
        if (availableSize.Width == numeric_limits<float>::infinity())
        {
            // We use the calculated max desired width of children
            *returnValue = { maxDesiredWidth, currentHeight };
        }
        else
        {
            // Otherwise we match the fixed width of the container
            *returnValue = { availableSize.Width, currentHeight };
        }
        return S_OK;
    }

    HRESULT WholeItemsPanel::ArrangeOverride(Size finalSize, __RPC__out Size *returnValue)
    {
        float currentHeight{};
        ComPtr<IVector<UIElement*>> spChildren;

        ComPtr<IPanel> spThisAsPanel;
        RETURN_IF_FAILED(QueryInterface(__uuidof(IPanel), reinterpret_cast<void**>(spThisAsPanel.GetAddressOf())));
        RETURN_IF_FAILED(spThisAsPanel->get_Children(spChildren.GetAddressOf()));
        RETURN_IF_FAILED(spChildren->get_Size(&m_measuredCount));

        for (unsigned int i{}; i < m_measuredCount; ++i)
        {
            ComPtr<IUIElement> spChild;
            RETURN_IF_FAILED(spChildren->GetAt(i, spChild.GetAddressOf()));

            Size childSize;
            RETURN_IF_FAILED(spChild->get_DesiredSize(&childSize));

            if (i < m_visibleCount)
            {

                float childHeight = childSize.Height;
                float newHeight = currentHeight + childSize.Height;

                // If we have truncated the first item newHeight may be greater than finalSize
                if (newHeight > finalSize.Height)
                {
                    childHeight = finalSize.Height - currentHeight;
                    newHeight = finalSize.Height;
                }
                const Rect rc = { 0.0f, currentHeight, finalSize.Width, childHeight }; // childSize.Width does not respect Text alignment
                RETURN_IF_FAILED(spChild->Arrange(rc));

                currentHeight = newHeight;
            }
            else
            {
                // Arrange the child outside the panel
                const Rect rc = { 0.0f, OutsidePanelY - childSize.Height, childSize.Width, childSize.Height };
                RETURN_IF_FAILED(spChild->Arrange(rc));
            }
        }

        // Now set the clipping region to ensure that items moved away will never be rendered
        // But we allow the items to slightly expand above the panel because we explicitly set negative
        // margins for text on the first line of a tile
        ComPtr<IFrameworkElement> spThisAsIFrameworkElement;
        Thickness margin;
        RETURN_IF_FAILED(QueryInterface(IID_PPV_ARGS(&spThisAsIFrameworkElement)));
        RETURN_IF_FAILED(spThisAsIFrameworkElement->get_Margin(&margin));
        Microsoft::WRL::ComPtr<IRectangleGeometry> spClip;
        RETURN_IF_FAILED(Windows::Foundation::ActivateInstance(HStringReference(RuntimeClass_Windows_UI_Xaml_Media_RectangleGeometry).Get(), &spClip));
        ComPtr<IUIElement> spThisAsIUIElement;
        RETURN_IF_FAILED(QueryInterface(IID_PPV_ARGS(&spThisAsIUIElement)));
        RETURN_IF_FAILED(spThisAsIUIElement->put_Clip(spClip.Get()));

        float x0 = static_cast<float>(-margin.Left);
        float y0 = static_cast<float>(-margin.Top);
        float x1 = static_cast<float>(margin.Left + finalSize.Width + margin.Right);
        float y1 = static_cast<float>(margin.Top + finalSize.Height + margin.Bottom);
        RETURN_IF_FAILED(spClip->put_Rect( {x0, y0 ,x1, y1} ));

        *returnValue = { finalSize.Width, finalSize.Height };
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

    HRESULT WholeItemsPanel::GetAltText(__RPC__out HSTRING *pResult)
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

    void WholeItemsPanel::SetAdaptiveHeight(_In_ bool value)
    {
        m_adaptiveHeight = value;
    }

    void WholeItemsPanel::SetMainPanel(_In_ bool value)
    {
        m_isMainPanel = value;
    }

    void WholeItemsPanel::AddElementToStretchablesList(_In_ IUIElement* element)
    {
        ComPtr<IUIElement> localElement(element);
        ComPtr<IUIElement4> elementWithAccessKey;
        if (SUCCEEDED(localElement.As(&elementWithAccessKey)))
        {
            std::string elementAccessKey = std::to_string(m_accessKeyCount);
            ++m_accessKeyCount;

            HSTRING accessKey;
            if (SUCCEEDED(UTF8ToHString(elementAccessKey, &accessKey)))
            {
                elementWithAccessKey->put_AccessKey(accessKey);
                m_stretchableItems.insert(elementAccessKey);
            }
        }
    }

    bool WholeItemsPanel::IsUIElementInStretchableList(_In_ IUIElement* element)
    {
        ComPtr<IUIElement> localElement(element);
        ComPtr<IUIElement4> elementWithAccessKey;
        if (SUCCEEDED(localElement.As(&elementWithAccessKey)))
        {
            HSTRING elementAccessKey;
            if (SUCCEEDED(elementWithAccessKey->get_AccessKey(&elementAccessKey)))
            {
                std::string accessKey = HStringToUTF8(elementAccessKey);
                return (m_stretchableItems.find(accessKey) != m_stretchableItems.end());
            }
        }

        return false; // Couldn't get access key, weird, so it wasnt found
    }

    _Check_return_ HRESULT
    WholeItemsPanel::IsAnySubgroupTruncated(
        _In_ ABI::Windows::UI::Xaml::Controls::IPanel* pPanel,
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
    _Check_return_ HRESULT WholeItemsPanel::LayoutCroppedImage(
        _In_ IShape *pShape,
        _In_ double availableWidth,
        _In_ double availableHeight)
    {
        ComPtr<IFrameworkElement> spFrameworkElement;
        VerticalAlignment valign;
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

    _Check_return_ HRESULT WholeItemsPanel::GetAltAsString(_In_ IUIElement *pElement, _Out_ HSTRING *pResult)
    {
        *pResult = nullptr;
        ComPtr<IDependencyObject> spDependencyObject;
        if (SUCCEEDED(pElement->QueryInterface(spDependencyObject.GetAddressOf())))
        {
            ComPtr<Automation::IAutomationPropertiesStatics> automationStatics;
            RETURN_IF_FAILED(::GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Automation_AutomationProperties).Get(), &automationStatics));
            RETURN_IF_FAILED(automationStatics->GetName(spDependencyObject.Get(), pResult));
        }
        return S_OK;
    }

    // Creates the Alt Text
    _Check_return_ HRESULT WholeItemsPanel::AppendAltTextToUIElement(_In_ IUIElement *pUIElement, _Inout_ std::wstring& buffer)
    {
        ComPtr<ITextBlock> spTextBlock;

        HRESULT hr = pUIElement->QueryInterface(spTextBlock.GetAddressOf());
        if (SUCCEEDED(hr))
        {
            HString hText;
            RETURN_IF_FAILED(spTextBlock->get_Text(hText.GetAddressOf()));
            AppendText(hText.Get(), buffer);
            return S_OK;
        }

        ComPtr<IWholeItemsPanel> spWholeItemsPanel;
        hr = pUIElement->QueryInterface(spWholeItemsPanel.GetAddressOf());
        if (SUCCEEDED(hr))
        {
            // This cast is safe because WinRT only does aggregation
            WholeItemsPanel* pPanelNoRef = reinterpret_cast<WholeItemsPanel*>(spWholeItemsPanel.Get());
            RETURN_IF_FAILED(pPanelNoRef->AppendAltText(buffer));
            return S_OK;
        }

        ComPtr<IImage> spImage;
        hr = pUIElement->QueryInterface(spImage.GetAddressOf());
        if (SUCCEEDED(hr))
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
        hr = pUIElement->QueryInterface(spShape.GetAddressOf());
        if (SUCCEEDED(hr))
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

    bool WholeItemsPanel::HasExplicitSize(_In_ IFrameworkElement *element)
    {
        DOUBLE definedImageHeight;
        element->get_Height(&definedImageHeight);
        DOUBLE definedImageWidth;
        element->get_Height(&definedImageWidth);

        return !isnan(definedImageHeight) || !isnan(definedImageWidth);
    }

    bool WholeItemsPanel::GridIsAColumnSet(_In_ IGrid* grid)
    {
        bool gridIsColumnSet{true};

        ComPtr<IGrid> localGrid(grid);
        ComPtr<IVector<RowDefinition*>> rowDefinitions;
        THROW_IF_FAILED(localGrid->get_RowDefinitions(&rowDefinitions));
        unsigned int rowCount{};
        THROW_IF_FAILED(rowDefinitions->get_Size(&rowCount));

        if (rowCount <= 1)
        {
            ComPtr<IPanel> gridAsPanel;
            THROW_IF_FAILED(localGrid.As(&gridAsPanel));
            ComPtr<IVector<UIElement*>> columns;
            THROW_IF_FAILED(gridAsPanel->get_Children(columns.ReleaseAndGetAddressOf()));
            unsigned int columnCount{};
            THROW_IF_FAILED(columns->get_Size(&columnCount));

            for (unsigned int i{}; i < columnCount && gridIsColumnSet; ++i)
            {
                ComPtr<IUIElement> column;
                THROW_IF_FAILED(columns->GetAt(i, column.GetAddressOf()));

                // If the child is a WholeItemsPanel it's ok
                ComPtr<IWholeItemsPanel> columnAsWholeItemsPanel;
                if (FAILED(column.As(&columnAsWholeItemsPanel)))
                {
                    // If the child is not a WholeItemsPanel, it may be a separator
                    ComPtr<IGrid> columnAsGrid;
                    if (SUCCEEDED(column.As(&columnAsGrid)))
                    {
                        ComPtr<IPanel> separatorAsPanel;
                        THROW_IF_FAILED(columnAsGrid.As(&separatorAsPanel));
                        ComPtr<IVector<UIElement*>> separatorContents;
                        THROW_IF_FAILED(separatorAsPanel->get_Children(separatorContents.ReleaseAndGetAddressOf()));
                        unsigned int separatorContentsCount{};
                        THROW_IF_FAILED(separatorContents->get_Size(&separatorContentsCount));

                        if (separatorContentsCount != 0)
                        {
                            gridIsColumnSet = false;
                        }
                    }
                    else
                    {
                        gridIsColumnSet = false;
                    }
                }
            }
        }
        else
        {
            gridIsColumnSet = false;
        }

        return gridIsColumnSet;
    }

AdaptiveNamespaceEnd
