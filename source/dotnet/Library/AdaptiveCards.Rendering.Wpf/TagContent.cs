using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace AdaptiveCards.Rendering.Wpf
{
    /// <summary>
    /// Class to add to all rendered items so ToggleVisibility can hide the separators or deduct the spacing from the margin
    /// </summary>
    public class TagContent
    {

        public TagContent(Grid separator, Grid elementContainer)
        {
            Separator = separator;
            ElementContainer = elementContainer;
        }

        public TagContent(AdaptiveSpacing spacing, Grid elementContainer)
        {
            Spacing = spacing;
            ElementContainer = elementContainer;
        }

        public Grid Separator { get; set; } = null;

        public AdaptiveSpacing Spacing { get; set; } = AdaptiveSpacing.None;

        public Grid ElementContainer { get; set; }

        public bool SpacingHasBeenHidden { get; set; } = false;

        public ColumnDefinition NotAutoWidthColumnDefinition { get; set; } = null;

        public int ViewIndex { get; set; }
    }
}
