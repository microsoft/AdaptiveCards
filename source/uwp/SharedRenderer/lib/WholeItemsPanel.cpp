// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
//
//  Copyright (c) 2014  Microsoft Corporation
//
#include "pch.h"
#include "WholeItemsPanel.h"
#include "WholeItemsPanel.g.cpp"

#include "ElementTagContent.h"

static const float OutsidePanelY = -1000.0f;

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    uint32_t WholeItemsPanel::s_bleedMargin = 0;

    // IFrameworkElementOverrides
    winrt::Size WholeItemsPanel::MeasureOverride(winrt::Size const& availableSize)
    {
        unsigned int count{};
        float currentHeight{};
        float maxDesiredWidth{};
        bool visible{true};

        auto children = this->Children();
        count = children.Size();

        const winrt::Size noVerticalLimit{availableSize.Width, std::numeric_limits<float>::infinity()};
        auto measuredAvailableSize{availableSize};

        m_visibleCount = count;

        for (uint32_t i = 0; i < count; i++)
        {
            auto child = children.GetAt(i);
            child.Measure(noVerticalLimit);

            if (visible)
            {
                winrt::Size childSize = child.DesiredSize();

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

                    if (auto childAsPanel = child.try_as<winrt::Panel>())
                    {
                        m_isTruncated = true;

                        // There is a tricky scenario here: a subgroup might have asked for more size than available while
                        // Still being able to reduce its size, for example if it has a minSize which can be respected
                        if (!keepItem)
                        {
                            winrt::Size remainingSpace = {measuredAvailableSize.Width, static_cast<float>(availableHeightForItem)};

                            child.Measure(remainingSpace);

                            m_isTruncated = IsAnySubgroupTruncated(childAsPanel);
                        }
                    }
                    if (auto childAsTextBlock = child.try_as<winrt::TextBlock>())
                    {
                        winrt::TextWrapping currentWrap = winrt::TextWrapping::Wrap;
                        if (childAsTextBlock.TextWrapping() == winrt::TextWrapping::NoWrap)
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
                            winrt::Size noLimit{std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()};
                            childAsTextBlock.TextWrapping(winrt::TextWrapping::NoWrap);
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
                                    winrt::IFrameworkElementStatics frameworkElementStatics;
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
                    if (auto childAsImage = child.try_as<winrt::Image>())
                    {
                        if (!HasExplicitSize(childAsImage))
                        {
                            childAsImage.Stretch(winrt::Stretch::Uniform);
                            keepItem = true;
                            m_isTruncated = false;
                        }
                        else
                        {
                            m_isTruncated = true;
                        }
                    }
                    if (auto childAsShape = child.try_as<winrt::Shape>())
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
                        currentHeight = std::max((currentHeight + childSize.Height), measuredAvailableSize.Height);
                        maxDesiredWidth = std::max(childSize.Width, maxDesiredWidth);
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
                maxDesiredWidth = std::max(childSize.Width, maxDesiredWidth);
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
        if (measuredAvailableSize.Width == std::numeric_limits<float>::infinity())
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

    winrt::Size WholeItemsPanel::ArrangeOverride(winrt::Size const& finalSize)
    {
        float currentHeight{0.0f};
        float extraPaddingPerItem{0.0f};

        auto children = this->Children();
        m_measuredCount = children.Size();

        if (m_stretchableItemCount != 0)
        {
            extraPaddingPerItem = floor((finalSize.Height - m_calculatedSize) / m_stretchableItemCount);
        }
        else
        {
            if (m_verticalContentAlignment == winrt::VerticalContentAlignment::Center)
            {
                currentHeight = (finalSize.Height - m_calculatedSize) / 2;
            }
            else if (m_verticalContentAlignment == winrt::VerticalContentAlignment::Bottom)
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
                const winrt::Rect rc = {0.0f, currentHeight, finalSize.Width, childHeight}; // childSize.Width
                                                                                            // does not respect Text alignment

                child.Arrange(rc);

                currentHeight = newHeight;
            }
            else
            {
                // Arrange the child outside the panel
                const winrt::Rect rc = {0.0f, OutsidePanelY - childSize.Height, childSize.Width, childSize.Height};
                child.Arrange(rc);
            }
        }

        // Now set the clipping region to ensure that items moved away will never be rendered
        // But we allow the items to slightly expand above the panel because we explicitly set negative
        // margins for text on the first line of a tile. Additionally, leave at least as much space on all
        // sides as specified by s_bleedMargin.

        winrt::Thickness margin = this->Margin();
        winrt::RectangleGeometry clip;

        const double bleedMargin = static_cast<double>(s_bleedMargin);
        float x0 = static_cast<float>(-std::max(margin.Left, bleedMargin));
        float y0 = static_cast<float>(-std::max(margin.Top, bleedMargin));
        float x1 = static_cast<float>(std::max(margin.Left, bleedMargin) + finalSize.Width + std::max(margin.Right, bleedMargin));
        float y1 = static_cast<float>(std::max(margin.Top, bleedMargin) + finalSize.Height + std::max(margin.Bottom, bleedMargin));
        clip.Rect({x0, y0, x1, y1});

        this->Clip(clip);

        return {finalSize.Width, finalSize.Height};
    }

    void WholeItemsPanel::OnApplyTemplate(void)
    {
        // Nothing special to do here
    }

    // Method used inside the component to reduce the number of temporary allocations
    void WholeItemsPanel::AppendAltText(std::wstring& buffer)
    {
        uint32_t count = m_visibleCount;
        auto children = this->Children();
        if (m_adaptiveHeight)
        {
            // If we are rendering stuff in adaptive height mode, we don't
            // care which of them are visible or not.
            count = children.Size();
        }

        for (uint32_t i = 0; i < count; i++)
        {
            AppendAltTextToUIElement(children.GetAt(i), buffer);
        }
    }

    winrt::hstring WholeItemsPanel::GetAltText()
    {
        std::wstring buffer;
        AppendAltText(buffer);
        return {buffer.c_str()};
    }

    void WholeItemsPanel::SetAdaptiveHeight(bool value) { m_adaptiveHeight = value; }

    void WholeItemsPanel::SetBleedMargin(uint32_t bleedMargin)
    {
        // Bleed margin is the extent to which the content may "bleed" out of the panel on the left and right. It is
        // used to ensure that the clip rectangle doesn't clip off bleeding content.
        s_bleedMargin = bleedMargin;
    }

    void WholeItemsPanel::SetMainPanel(bool value) { m_isMainPanel = value; }

    // Not sure if I did everything right here..
    void WholeItemsPanel::AddElementToStretchablesList(winrt::UIElement const& element)
    {
        if (const auto elementAsFrameworkElement = element.try_as<winrt::FrameworkElement>())
        {
            if (const auto tag = elementAsFrameworkElement.Tag())
            {
                if (const auto tagAsElementTagContent = tag.try_as<winrt::ElementTagContent>())
                {
                    tagAsElementTagContent.IsStretchable(true);
                }
                else
                {
                    winrt::ElementTagContent tagContent{};
                    tagContent.IsStretchable(true);
                    elementAsFrameworkElement.Tag(tagContent);
                }
            }
        }
        ++m_stretchableItemCount;
    }

    bool WholeItemsPanel::IsUIElementInStretchableList(winrt::UIElement const& element)
    {
        if (const auto elementAsFrameworkElement = element.try_as<winrt::FrameworkElement>())
        {
            if (const auto tag = elementAsFrameworkElement.Tag())
            {
                if (const auto tagAsElementTagContent = tag.try_as<winrt::ElementTagContent>())
                {
                    return tagAsElementTagContent.IsStretchable();
                }
            }
        }
        return false;
    }

    bool WholeItemsPanel::IsAnySubgroupTruncated(winrt::Panel const& panel)
    {
        for (auto child : panel.Children())
        {
            // Subgroups (columns) are implemented with WholeItemsPanel
            if (auto childAsWholeItemPanel = child.as<winrt::WholeItemsPanel>())
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
    void WholeItemsPanel::LayoutCroppedImage(winrt::Shape const& shape, double availableWidth, double availableHeight)
    {
        winrt::Thickness margins = shape.Margin();
        const double effectiveAvailableWidth = availableWidth - margins.Left - margins.Right;
        const double effectiveAvailableHeight = availableHeight - margins.Top - margins.Bottom;
        shape.Width(effectiveAvailableWidth);
        shape.Height(effectiveAvailableHeight);
    }

    void WholeItemsPanel::AppendText(winrt::hstring const& text, std::wstring& buffer)
    {
        if (buffer.length() > 0)
        {
            buffer.push_back(L'\n');
        }
        buffer.append(text.c_str());
    }

    winrt::hstring WholeItemsPanel::GetAltAsString(winrt::UIElement const& element)
    {
        if (const auto dependencyObject = element.try_as<winrt::DependencyObject>())
        {
            return winrt::AutomationProperties::GetName(dependencyObject);
        }
        return L"";
    }

    // Creates the Alt Text
    void WholeItemsPanel::AppendAltTextToUIElement(winrt::UIElement const& element, std::wstring& buffer)
    {
        if (const auto textBlock = element.try_as<winrt::TextBlock>())
        {
            AppendText(textBlock.Text(), buffer);
        }
        else if (const auto wholeItemsPanel = element.try_as<winrt::implementation::WholeItemsPanel>())
        {
            wholeItemsPanel->AppendAltText(buffer);
        }
        else if (const auto image = element.try_as<winrt::Image>())
        {
            auto altText = GetAltAsString(element);
            if (!altText.empty())
            {
                AppendText(altText, buffer);
            }
        }
        else if (const auto shape = element.try_as<winrt::Shape>())
        {
            auto altText = GetAltAsString(element);
            if (!altText.empty())
            {
                AppendText(altText, buffer);
            }
        }
        else if (const auto panel = element.try_as<winrt::Panel>())
        {
            for (auto child : panel.Children())
            {
                AppendAltTextToUIElement(child, buffer);
            }
        }
        else if (const auto border = element.try_as<winrt::Border>())
        {
            if (const auto child = border.Child())
            {
                AppendAltTextToUIElement(child, buffer);
            }
        }
    }

    bool WholeItemsPanel::HasExplicitSize(winrt::FrameworkElement const& element)
    {
        return !isnan(element.Height()) || !isnan(element.Width());
    }
}
