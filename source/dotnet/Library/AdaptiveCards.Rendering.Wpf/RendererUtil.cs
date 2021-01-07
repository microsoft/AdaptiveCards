// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Drawing.Text;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace AdaptiveCards.Rendering.Wpf
{
    static class RendererUtil
    {
        /// <summary>
        /// Checks if any of the fonts to be used for the TexBlock is installed, and if so, returns it
        /// </summary>
        /// <param name="fontList">Font list to check if any exist</param>
        /// <returns>First font in list that is installed, otherwise, default system font</returns>
        public static string GetFontFamilyFromList(string fontList)
        {
            var installedFonts = new InstalledFontCollection();
            string[] fontFamilies = fontList.Split(',');

            for (int i = 0; i < fontFamilies.Length; ++i)
            {
                string fontFamily = fontFamilies[i].Trim('\'');

                foreach (var installedFontFamily in installedFonts.Families)
                {
                    if (installedFontFamily.Name == fontFamily)
                    {
                        return fontFamily;
                    }
                }
            }

            // If no valid font was found in list, return the system default font
            return SystemFonts.MessageFontFamily.ToString();
        }

        public static void ApplyVerticalContentAlignment(FrameworkElement uiElement, AdaptiveCollectionElement element)
        {
            switch (element.VerticalContentAlignment)
            {
                case AdaptiveVerticalContentAlignment.Center:
                    uiElement.VerticalAlignment = VerticalAlignment.Center;
                    break;
                case AdaptiveVerticalContentAlignment.Bottom:
                    uiElement.VerticalAlignment = VerticalAlignment.Bottom;
                    break;
                case AdaptiveVerticalContentAlignment.Top:
                default:
                    break;
            }
        }

        public static FrameworkElement ApplySelectAction(FrameworkElement uiElement, AdaptiveElement element, AdaptiveRenderContext context)
        {
            AdaptiveAction selectAction = null;
            if (element is AdaptiveCollectionElement)
            {
                selectAction = (element as AdaptiveCollectionElement).SelectAction;

            }
            else if (element is AdaptiveImage)
            {
                selectAction = (element as AdaptiveImage).SelectAction;
            }

            if (selectAction != null)
            {
                return context.RenderSelectAction(selectAction, uiElement);
            }

            return uiElement;
        }


        /// <summary>
        /// Changes the visibility for the rendered element
        /// </summary>
        /// <param name="element">Rendered element to apply visibility</param>
        /// <param name="desiredVisibility">Visibility to be applied to the element</param>
        /// <param name="tagContent">Rendered element tag</param>
        public static void SetVisibility(FrameworkElement element, bool desiredVisibility, TagContent tagContent)
        {
            // TagContents are only assigned to card elements so actions mustn't have a TagContent object tied to it
            // TagContents are used to save information on the rendered object as the element separator
            if (tagContent == null)
            {
                return;
            }

            bool elementIsCurrentlyVisible = (element.Visibility == Visibility.Visible);

            element.Visibility = desiredVisibility ? Visibility.Visible : Visibility.Collapsed;

            // Hides the separator if any was rendered
            Grid separator = tagContent.Separator;
            if (separator != null)
            {
                separator.Visibility = desiredVisibility ? Visibility.Visible : Visibility.Collapsed;
            }

            // Elements (Rows) with RowDefinition having stars won't hide so we have to set the width to auto
            // Also, trying to set the same rowDefinition twice to the same element is not valid,
            // so we have to make a check first
            if ((tagContent.RowDefinition != null) && !(elementIsCurrentlyVisible && desiredVisibility))
            {
                RowDefinition rowDefinition = null;
                if (desiredVisibility)
                {
                    rowDefinition = tagContent.RowDefinition;
                }
                else
                {
                    // When the visibility is set to false, then set the row definition to auto
                    rowDefinition = new RowDefinition() { Height = GridLength.Auto };
                }

                tagContent.ParentContainerElement.RowDefinitions[tagContent.ViewIndex] = rowDefinition;
            }

            // Columns with ColumnDefinition having stars won't hide so we have to set the width to auto
            // Also, trying to set the same columnDefinition twice to the same element is not valid,
            // so we have to make a check first
            if ((tagContent.ColumnDefinition != null) && !(elementIsCurrentlyVisible && desiredVisibility))
            {
                ColumnDefinition columnDefinition = null;
                if (desiredVisibility)
                {
                    columnDefinition = tagContent.ColumnDefinition;
                }
                else
                {
                    columnDefinition = new ColumnDefinition() { Width = GridLength.Auto };
                }

                tagContent.ParentContainerElement.ColumnDefinitions[tagContent.ViewIndex] = columnDefinition;
            }
        }
    }
}
