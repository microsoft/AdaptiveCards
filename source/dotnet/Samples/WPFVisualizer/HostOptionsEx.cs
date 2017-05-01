using AdaptiveCards;
using AdaptiveCards.Rendering.Config;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Serialization;
using PropertyChanged;
using System;
using System.Linq;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;
using Xceed.Wpf.Toolkit.PropertyGrid.Editors;

namespace WpfVisualizer
{
//    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
//    public class HostConfigEx
//    {
//        public HostConfigEx() { }

//        /// <summary>
//        /// Font family for the card (can be comma delimited for fallback)
//        /// </summary>
//        public string FontFamily { get; set; } = "Calibri";

//        /// <summary>
//        /// FontSize
//        /// </summary>
//        [ExpandableObject]
//        public FontSizeConfigEx FontSize { get; set; } = new FontSizeConfigEx();


//        /// <summary>
//        /// Toggles whether or not to render inputs and actions
//        /// </summary>
//        public bool SupportsInteractivity { get; set; } = true;

//        /// <summary>
//        /// The types of Actions that you support(null for no actions)
//        /// </summary>
//        public string[] SupportedActionTypes { get; set; } = new string[]
//        {
//            OpenUrlAction.TYPE,
//            SubmitAction.TYPE,
//            HttpAction.TYPE,
//            ShowCardAction.TYPE
//        };

//        [ExpandableObject]
//        public ImageSizeConfigEx ImageSize { get; set; } = new ImageSizeConfigEx();

//        /// <summary>
//        /// Max number of actions to support on your Cards(e.g., 3)
//        /// </summary>
//        public int MaxActions { get; set; } = 5;

//        /// <summary>
//        /// Separation settings between vertical elements
//        /// </summary>
//        [ExpandableObject]
//        public SeparationConfigEx VerticalSeparation { get; set; } = new SeparationConfigEx();

//        /// <summary>
//        /// Separation settings between horizontal elements
//        /// </summary>
//        [ExpandableObject]
//        public SeparationConfigEx HorizontalSeparation { get; set; } = new SeparationConfigEx();

//        //  ------ AdaptiveCard -------
//        [ExpandableObject]
//        public AdaptiveCardConfigEx AdaptiveCard { get; set; } = new AdaptiveCardConfigEx();

//        /// <summary>
//        /// Color settings for the TextBlock
//        /// </summary>
//        [ExpandableObject]
//        public ColorConfigEx Colors { get; set; } = new ColorConfigEx();

//        // ------ Containers ------
//        [ExpandableObject]
//        public ImageSetConfigEx ImageSet { get; set; } = new ImageSetConfigEx();

//        [ExpandableObject]
//        public FactSetConfigEx FactSet { get; set; } = new FactSetConfigEx();

//        // ------ Actions------
//        [ExpandableObject]
//        public ActionConfigEx Actions { get; set; } = new ActionConfigEx();
//    }

//    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
//    public class BoundaryConfigEx
//    {
//        public BoundaryConfigEx() { }

//        public BoundaryConfigEx(int allMargin)
//        {
//            Left = Right = Top = Bottom = allMargin;
//        }
//        public BoundaryConfigEx(int left, int top, int right, int bottom)
//        {
//            Left = left;
//            Top = top;
//            Right = right;
//            Bottom = bottom;
//        }


//        public int Left { get; set; }
//        public int Top { get; set; }
//        public int Right { get; set; }
//        public int Bottom { get; set; }
//    }

//    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
//    public class AdaptiveCardConfigEx
//    {
//        public AdaptiveCardConfigEx() { }

//        /// <summary>
//        ///  Padding for the card
//        /// </summary>
//        public BoundaryConfigEx Padding { get; set; } = new BoundaryConfigEx(8);

//        /// <summary>
//        /// Background color for card 
//        /// </summary>
//        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
//        public string BackgroundColor { get; set; } = "#FFFFFF";
//    }

//    [JsonConverter(typeof(StringEnumConverter), true)]
//    public enum ActionsOrientation
//    {
//        /// <summary>
//        /// actions should be laid out horizontally
//        /// </summary>
//        Horizontal,

//        /// <summary>
//        /// Actions should be laid out vertically
//        /// </summary>
//        Vertical
//    }


//    /// <summary>
//    /// Properties which control spacing and visual between elements
//    /// </summary>
//    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
//    public class SeparationConfigEx
//    {
//        public SeparationConfigEx() { }

//        /// <summary>
//        /// Separation settings when Separation:default
//        /// </summary>
//        [ExpandableObject]
//        public SeparationOption Default { get; set; } = new SeparationOption() { Spacing = 10 };

//        /// <summary>
//        /// Separation settings when Separation:Strong
//        /// </summary>
//        [ExpandableObject]
//        public SeparationOption Strong { get; set; } = new SeparationOption() { Spacing = 20, LineThickness = 1, LineColor = "#FF707070" };
//    }

//    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
//    public class SeparationOption
//    {
//        public SeparationOption() { }

//        /// <summary>
//        /// How much space between this element and previous should be used
//        /// </summary>
//        public int Spacing { get; set; }

//        /// <summary>
//        /// If there is a visible line, how thick should the line be
//        /// </summary>
//        public int LineThickness { get; set; }

//        /// <summary>
//        /// If there is a visible color, what color to use
//        /// </summary>
//        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
//        public string LineColor { get; set; }

//    }

//    /// <summary>
//    /// Properties which control rendering of TextBlock 
//    /// </summary>
//    //public class TextBlockConfig : CardElementConfig
//    //{
//    //    public TextBlockConfig() { }

//    //}

//    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
//    public class FontSizeConfigEx
//    {
//        public FontSizeConfigEx() { }

//        public int Small { get; set; } = 10;

//        public int Normal { get; set; } = 12;

//        public int Medium { get; set; } = 14;

//        public int Large { get; set; } = 17;

//        public int ExtraLarge { get; set; } = 20;

//    }

//    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
//    public class ColorConfigEx
//    {
//        public ColorConfigEx() { }

//        [ExpandableObject]
//        public ColorOptionEx Default { get; set; } = new ColorOptionEx("#FF000000");

//        [ExpandableObject]
//        public ColorOptionEx Accent { get; set; } = new ColorOptionEx("#FF0000FF");

//        [ExpandableObject]
//        public ColorOptionEx Dark { get; set; } = new ColorOptionEx("#FF101010");

//        [ExpandableObject]
//        public ColorOptionEx Light { get; set; } = new ColorOptionEx("#FFFFFFFF");

//        [ExpandableObject]
//        public ColorOptionEx Good { get; set; } = new ColorOptionEx("#FF008000");

//        [ExpandableObject]
//        public ColorOptionEx Warning { get; set; } = new ColorOptionEx("#FFFFD700");

//        [ExpandableObject]
//        public ColorOptionEx Attention { get; set; } = new ColorOptionEx("#FF8B0000");
//    }

//    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
//    public class ColorOptionEx
//    {
//        public ColorOptionEx(string normal, string subtle = null)
//        {
//            this.Normal = normal;
//            if (subtle == null)
//            {
//                var opacity = (byte)(Convert.ToByte(normal.Substring(1, 2), 16) * .7);
//                this.Subtle = $"#{opacity.ToString("x")}{normal.Substring(3)}";
//            }
//            else
//                this.Subtle = subtle;
//        }

//        /// <summary>
//        /// Color in #RRGGBB format
//        /// </summary>
//        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
//        public string Normal { get; set; }

//        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
//        public string Subtle { get; set; }
//    }

//    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
//    public class ImageSizeConfigEx

//    {
//        public ImageSizeConfigEx() { }

//        public int Small { get; set; } = 60;

//        public int Medium { get; set; } = 120;

//        public int Large { get; set; } = 180;
//    }

//    /// <summary>
//    /// Properties which control rendering of actions
//    /// </summary>
//    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
//    public class ActionConfigEx
//    {
//        public ActionConfigEx() { }

//        [ExpandableObject]
//        public ShowCardConfigEx ShowCard { get; set; } = new ShowCardConfigEx();

//        /// <summary>
//        /// Arrange actions horizontal or vertical
//        /// </summary>
//        public ActionsOrientation ActionsOrientation { get; set; } = ActionsOrientation.Horizontal;

//        /// <summary>
//        /// should they be aligned Left, Center or Right
//        /// </summary>
//        public HorizontalAlignment ActionAlignment { get; set; } = HorizontalAlignment.Center;


//        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
//        public string BackgroundColor { get; set; } = "#FF5098FF";

//        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
//        public string BorderColor { get; set; } = "#FF000000";

//        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
//        public string TextColor { get; set; } = "#FFFFFFFF";

//        public int BorderThickness { get; set; } = 1;

//        public int FontWeight { get; set; } = 400;

//        public int FontSize { get; set; } = 12;

//        public int Spacing { get; set; } = 8;

//        /// <summary>
//        /// space between title and button edge
//        /// </summary>
//        [ExpandableObject]
//        public BoundaryConfigEx Padding { get; set; } = new BoundaryConfigEx(4);

//    }

//    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
//    public class ShowCardConfigEx
//    {
//        public ShowCardConfigEx() { }

//        public ShowCardActionMode ActionMode { get; set; } = ShowCardActionMode.Popup;

//        /// <summary>
//        /// Background color for showcard area
//        /// </summary>
//        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
//        public string BackgroundColor { get; set; } = "#FFF8F8F8";

//        /// <summary>
//        /// If actionMode is inline and AutoPAdding is on then the background will extend to the edges of the parent card.
//        /// </summary>
//        public bool AutoPadding { get; set; } = false;
//    }

//    [JsonConverter(typeof(StringEnumConverter), true)]
//    public enum ShowCardActionMode
//    {
//        Inline,
//        Popup
//    }


//    public class ImageSetConfigEx
//    {
//        public ImageSetConfigEx() { }

//        public ImageSize ImageSize { get; set; } = ImageSize.Medium;
//    }

//    public class FactSetConfigEx
//    {
//        public FactSetConfigEx() { }

//        /// <summary>
//        /// TextBlock to use for Titles in factsets
//        /// </summary>
//        [ExpandableObject]
//        public TextConfigEx Title { get; set; } = new TextConfigEx() { Size = TextSize.Normal, Color = TextColor.Default, IsSubtle = false, Weight = TextWeight.Bolder };

//        /// <summary>
//        /// TextBlock to use for Values in fact sets
//        /// </summary>
//        [ExpandableObject]
//        public TextConfigEx Value { get; set; } = new TextConfigEx();

//        /// <summary>
//        /// Spacing between facts and values
//        /// </summary>
//        public int Spacing { get; set; } = 20;
//    }

//    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
//    public class TextConfigEx
//    {
//        public TextConfigEx()
//        { }

//        /// <summary>
//        ///     The size of the text
//        /// </summary>
//        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
//        public TextSize Size { get; set; } = TextSize.Normal;

//        /// <summary>
//        ///     The weight of the text
//        /// </summary>
//        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
//        public TextWeight Weight { get; set; } = TextWeight.Normal;

//        /// <summary>
//        ///     The color of the text
//        /// </summary>
//        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
//        public TextColor Color { get; set; } = TextColor.Default;

//        /// <summary>
//        ///     Should it be subtle?
//        /// </summary>
//        public bool IsSubtle { get; set; } = false;

//        public bool ShouldSerializeSize()
//        {
//            return Size != TextSize.Normal;
//        }

//        public bool ShouldSerializeColor()
//        {
//            return Color != TextColor.Default;
//        }


//        public bool ShouldSerializeWeight()
//        {
//            return Weight != TextWeight.Normal;
//        }

//        public bool ShouldSerializeIsSubtle()
//        {
//            return IsSubtle;
//        }
//    }

}
