using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// This class contais all proterties that are used for rendering and need to be passed down between parent and child elements 
namespace AdaptiveCards.Rendering
{
    public enum BleedDirection { Left, Both, Right, None };

    public class AdaptiveRenderArgs
    {
        public AdaptiveRenderArgs() { }

        public AdaptiveRenderArgs(AdaptiveRenderArgs previousRenderArgs)
        {
            ParentStyle = previousRenderArgs.ParentStyle;
            ForegroundColors = previousRenderArgs.ForegroundColors;
            BleedDirection = previousRenderArgs.BleedDirection;
            HasParentWithPadding = previousRenderArgs.HasParentWithPadding;
        }

        // Default value for the container style of the first adaptiveCard
        public AdaptiveContainerStyle ParentStyle { get; set; } = AdaptiveContainerStyle.Default;

        public ForegroundColorsConfig ForegroundColors { get; set; }

        // Default value for the direction where the elements of the adaptive card can bleed to
        public BleedDirection BleedDirection { get; set; } = BleedDirection.Both;

        public bool HasParentWithPadding { get; set; } = true;

    }
}
