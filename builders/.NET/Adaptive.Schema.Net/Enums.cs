using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Adaptive.Schema.Net
{
    /// <summary>
    /// Controls the horizontal size (width) of element.
    /// </summary>
    public enum Size
    {
        /// <summary>
        /// The width of the element is optimally chosen depending on the space available in the element's container
        /// </summary>
        Auto,

        /// <summary>
        /// The width of the element adjusts to match that of its container
        /// </summary>
        Stretch,

        /// <summary>
        /// Small width
        /// </summary>
        Small,

        /// <summary>
        /// Medium width
        /// </summary>
        Medium,

        /// <summary>
        /// Large width
        /// </summary>
        Large
    }

    /// <summary>
    /// Controls the relative size of TextBlock elements
    /// </summary>
    public enum TextSize
    {
        /// <summary>
        /// Smallest text size
        /// </summary>
        Small,

        /// <summary>
        /// Default text size
        /// </summary>
        Normal,

        /// <summary>
        /// Slightly larger than normal
        /// </summary>
        Medium,

        /// <summary>
        /// Slightly larger then medium
        /// </summary>
        Large,

        /// <summary>
        /// The largest text size
        /// </summary>
        ExtraLarge
    }

    /// <summary>
    /// Controls the weight of TextBock Elements
    /// </summary>
    public enum TextWeight
    {
        /// <summary>
        /// Lighter text (thinner stroke)
        /// </summary>
        Lighter,

        /// <summary>
        /// The default text weight
        /// </summary>
        Normal,

        /// <summary>
        /// Bolder text (wider stroke)
        /// </summary>
        Bolder
    }

    /// <summary>
    /// Controls the color style of TextBlock Elements
    /// </summary>
    public enum TextColor
    {
        /// <summary>
        /// The default color which guarentees appropriate contrast 
        /// </summary>
        Default,

        /// <summary>
        /// Forces the text to be rendered in a dark color which is suitable when displayed over a light background
        /// </summary>
        Dark,

        /// <summary>
        /// Forces the text to be rendered in a light color which is suitable when displayed over a dark background
        /// </summary>
        Light,

        /// <summary>
        /// Accent the text
        /// </summary>
        Accent,

        /// <summary>
        /// Good (such as green)
        /// </summary>
        Good,

        /// <summary>
        /// Warning (such as yellow)
        /// </summary>
        Warning,

        /// <summary>
        /// Highlight as needing attention (such as red)
        /// </summary>
        Attention
    }

    /// <summary>
    /// Controls how elements are horizontally positioned within their container.
    /// </summary>
    public enum HorizontalAlignment
    {
        /// <summary>
        /// The element is left aligned
        /// </summary>
        Left,

        /// <summary>
        /// The element is centered inside its container
        /// </summary>
        Center,

        /// <summary>
        /// The element is right aligned
        /// </summary>
        Right
    }

    /// <summary>
    /// Controls the way Image elements are displayed.
    /// </summary>
    public enum ImageStyle
    {
        /// <summary>
        /// The image is displayed within a rectangle.
        /// </summary>
        Normal,

        /// <summary>
        /// The image is cropped to a circle, a common way to represent people photos.
        /// </summary>
        Person
    }

}
