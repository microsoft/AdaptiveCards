// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using Xceed.Wpf.Toolkit;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class XceedChoiceSetInput 
    {
        public static FrameworkElement Render(AdaptiveChoiceSetInput input, AdaptiveRenderContext context)
        {
            // Use xceed's WatermarkComboBox to support placeholder
            var comboBox = new WatermarkComboBox
            {
                Watermark = input.Placeholder
            };

            return AdaptiveChoiceSetRenderer.RenderHelper(new Grid(), comboBox, new StackPanel(), input, context);
        }
    }
}
