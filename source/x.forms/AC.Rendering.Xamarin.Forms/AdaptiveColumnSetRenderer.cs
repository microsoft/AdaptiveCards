using System;
using System.Collections.Generic;
using System.Text;
using Xamarin.Forms;

namespace AdaptiveCards.Rendering.Forms
{
    class AdaptiveColumnSetRenderer
    {

        public static View Render(AdaptiveColumnSet columnSet, AdaptiveRenderContext context)
        {
            Grid uiColumnSet = new Grid();

            foreach (var column in columnSet.Columns)
            {
                View uiColumn = context.Render(column);

                uiColumnSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
                Grid.SetColumn(uiColumn, uiColumnSet.ColumnDefinitions.Count - 1);
                uiColumnSet.Children.Add(uiColumn);
            }

            return uiColumnSet;
        }

    }
}
