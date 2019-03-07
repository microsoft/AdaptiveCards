using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// This class contais all proterties that are used for rendering and need to be passed down between parent and child elements 
namespace AdaptiveCards.Rendering
{
    public enum ColumnPositionEnum { Begin, Intermediate, End, Only };

    public class AdaptiveRenderArgs
    {
        public AdaptiveRenderArgs() { }

        public AdaptiveContainerStyle ParentStyle { get; set; } = AdaptiveContainerStyle.Default;

        public ForegroundColorsConfig ForegroundColors { get; set; }
        
        public ColumnPositionEnum ColumnRelativePosition { get; set; }

        public bool HasParentWithPadding { get; set; } = true;

        public AdaptiveRenderArgs Clone()
        {
            return new AdaptiveRenderArgs {
                ParentStyle = ParentStyle,
                ForegroundColors = ForegroundColors,
                ColumnRelativePosition = ColumnRelativePosition,
                HasParentWithPadding = HasParentWithPadding
            };
        }

    }
}
