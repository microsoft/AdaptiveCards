using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Serialization;

namespace Adaptive.Schema.Net
{

    /// <summary>
    /// Controls the horizontal size (width) of Column.
    /// </summary>
    public class ColumnSize
    {
        /// <summary>
        /// The width of the Column is optimally chosen depending on the space available in the element's container
        /// </summary>
        public const string Auto = "Auto";

        /// <summary>
        /// The width of the Column adjusts to match that of its container
        /// </summary>
        public const string Stretch = "Stretch";
    }

    /// <summary>
    /// Controls the horizontal size (width) of element.
    /// </summary>
    [JsonConverter(typeof(StringEnumConverter), true)]
    public enum ImageSize
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
    [JsonConverter(typeof(StringEnumConverter), true)]
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
    [JsonConverter(typeof(StringEnumConverter), true)]
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
    [JsonConverter(typeof(StringEnumConverter), true)]
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
    [JsonConverter(typeof(StringEnumConverter), true)]
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
    [JsonConverter(typeof(StringEnumConverter), true)]
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

    /// <summary>
    /// Controls the separation style for the current container
    /// </summary>
    [JsonConverter(typeof(StringEnumConverter), true)]
    public enum SeparationStyle
    {
        /// <summary>
        /// separate the current container from the previous container
        /// </summary>
        Before,

        /// <summary>
        /// separate the current container from the following container
        /// </summary>
        After,

        /// <summary>
        /// separate the current container from the previous and following container
        /// </summary>
        Both
    }

    [JsonConverter(typeof(StringEnumConverter), true)]
    public enum TextInputStyle
    {
        /// <summary>
        /// Input is a telephone number and the client may use this information to provide optimized keyboard input for the user.
        /// </summary>
        Tel,

        /// <summary>
        /// Input is a url and the client may use this information to provide optimized keyboard input for the user.
        /// </summary>
        Url,

        /// <summary>
        /// Input is a email and the client may use this information to provide optimized keyboard input for the user.
        /// </summary>
        Email,

        /// <summary>
        /// Input is text but should be hidden to protect the typed information in the textbox.
        /// </summary>
        Password,

        /// <summary>
        /// Input is a number. min, max and step properties expressed as numbers may be used by client to help user input number into text box.
        /// </summary>
        Number,

        /// <summary>
        /// Input is a range. min, max and step properties expressed as numbersmay be used by client to help user input a number on a range into text box
        /// </summary>
        Range,

        /// <summary>
        /// Input is date. min, max properties expressed as Date may be used by client to help user to select a date via a text box
        /// </summary>
        Date,

        /// <summary>
        /// Input is date and time. min, max expressed as DateTime properties may be used by client to help user to select a date and a time via a text box
        /// </summary>
        Datetime,

        /// <summary>
        /// Input is time. min, max properties expressed as time may be used by client to help user to select a time via a text box
        /// </summary>
        Time,

        /// <summary>
        /// Input is month. min, max properties expressed as Date may be used by client to help user to select a month via a text box
        /// </summary>
        Month,

        /// <summary>
        /// Input is week. min, max properties expressed as Date may be used by client to help user to select a week via a text box
        /// </summary>
        Week
    }

    [JsonConverter(typeof(StringEnumConverter), true)]
    public enum ChoiceInputStyle
    {
        /// <summary>
        /// choices are preffered to be compactly displayed. Example: ComboBox 
        /// </summary>
        Compact,

        /// <summary>
        /// choices are preferred to be displayed for easy input. Example: Checkbox or Radio buttons
        /// </summary>
        Expanded
    }

}
