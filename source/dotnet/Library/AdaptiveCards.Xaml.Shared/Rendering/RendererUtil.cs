// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
#if WPF
using System.Windows;
using System.Drawing.Text;
#elif XAMARIN
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
using Button = AdaptiveCards.Rendering.ContentButton;
#endif

namespace AdaptiveCards.Rendering.Wpf
{
    static class RendererUtil
    {
#if WPF
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
#endif

        public static void ApplyVerticalContentAlignment(FrameworkElement uiElement, AdaptiveCollectionElement element)
        {
#if WPF
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
#elif XAMARIN
        switch (element.VerticalContentAlignment)
            {
                case AdaptiveVerticalContentAlignment.Center:
                    uiElement.VerticalOptions = LayoutOptions.CenterAndExpand;
                    break;
                case AdaptiveVerticalContentAlignment.Bottom:
                    uiElement.VerticalOptions = LayoutOptions.EndAndExpand;
                    break;
                case AdaptiveVerticalContentAlignment.Top:
                default:
                    break;
            }
#endif
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

    }
}
