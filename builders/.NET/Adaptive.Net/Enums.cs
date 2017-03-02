using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Serialization;

namespace Adaptive
{

    public class MyStringEnumConverter : StringEnumConverter
    {
        public MyStringEnumConverter() { }

        public MyStringEnumConverter(bool camelCaseText) : base(camelCaseText) { }

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            if (value?.ToString() == "Default")
                value = null;
            base.WriteJson(writer, value, serializer);
        }
    }

    /// <summary>
    /// Controls the horizontal size (width) of Column.
    /// </summary>
    public partial class ColumnSize
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
    [JsonConverter(typeof(MyStringEnumConverter), true)]
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
    /// Controls the emphasize of an element to the previous element
    /// </summary>
    [JsonConverter(typeof(MyStringEnumConverter), true)]
    public enum SeparationStyle
    {
        /// <summary>
        /// Default element spacing is applied from style
        /// </summary>
        Default,

        /// <summary>
        /// No spacing is applied between elements
        /// </summary>
        None,

        /// <summary>
        /// Strongly separate the element from the previous element
        /// </summary>
        Strong
    }

    /// <summary>
    /// Controls the relative size of TextBlock elements
    /// </summary>
    [JsonConverter(typeof(MyStringEnumConverter), true)]
    public enum TextSize
    {
        /// <summary>
        /// Default text size
        /// </summary>
        Normal,

        /// <summary>
        /// Smallest text size
        /// </summary>
        Small,

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
    [JsonConverter(typeof(MyStringEnumConverter), true)]
    public enum TextWeight
    {
        /// <summary>
        /// The default text weight
        /// </summary>
        Normal,

        /// <summary>
        /// Lighter text (thinner stroke)
        /// </summary>
        Lighter,

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

    [JsonConverter(typeof(StringEnumConverter), true)]
    public enum TextInputStyle
    {
        /// <summary>
        /// plain text
        /// </summary>
        Text, 

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
        Email
    }

    [JsonConverter(typeof(StringEnumConverter), true)]
    public enum ChoiceInputStyle
    {
        /// <summary>
        /// choices are preferred to be displayed for easy input. Example: Checkbox or Radio buttons
        /// </summary>
        Expanded,

        /// <summary>
        /// choices are preffered to be compactly displayed. Example: ComboBox 
        /// </summary>
        Compact
    }

}
