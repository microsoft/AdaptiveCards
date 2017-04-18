using AdaptiveCards;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Serialization;
using PropertyChanged;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;
using Xceed.Wpf.Toolkit.PropertyGrid.Editors;

namespace WpfVisualizer
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class HostOptionsEx
    {
        public HostOptionsEx() { }

        /// <summary>
        /// Font family for the card (can be comma delimited for fallback)
        /// </summary>
        public string FontFamily { get; set; } = "Calibri";

        /// <summary>
        /// FontSize
        /// </summary>
        [ExpandableObject]
        public FontSizeOptionsEx FontSize { get; set; } = new FontSizeOptionsEx();


        /// <summary>
        /// Toggles whether or not to render inputs and actions
        /// </summary>
        public bool SupportsInteractivity { get; set; } = true;

        /// <summary>
        /// The types of Actions that you support(null for no actions)
        /// </summary>
        public string[] SupportedActionTypes { get; set; } = new string[]
        {
            OpenUrlAction.TYPE,
            SubmitAction.TYPE,
            HttpAction.TYPE,
            ShowCardAction.TYPE
        };

        [ExpandableObject]
        public ImageSizeOptionsEx ImageSize { get; set; } = new ImageSizeOptionsEx();

        /// <summary>
        /// Max number of actions to support on your Cards(e.g., 3)
        /// </summary>
        public int MaxActions { get; set; } = 5;

        /// <summary>
        /// Separation settings between vertical elements
        /// </summary>
        [ExpandableObject]
        public SeparationOptionsEx VerticalSeparation { get; set; } = new SeparationOptionsEx();

        /// <summary>
        /// Separation settings between horizontal elements
        /// </summary>
        [ExpandableObject]
        public SeparationOptionsEx HorizontalSeparation { get; set; } = new SeparationOptionsEx();

        //  ------ AdaptiveCard -------
        [ExpandableObject]
        public AdaptiveCardOptionsEx AdaptiveCard { get; set; } = new AdaptiveCardOptionsEx();

        /// <summary>
        /// Color settings for the TextBlock
        /// </summary>
        [ExpandableObject]
        public ColorOptionsEx Colors { get; set; } = new ColorOptionsEx();

        // ------ Containers ------
        [ExpandableObject]
        public ImageSetOptionsEx ImageSet { get; set; } = new ImageSetOptionsEx();

        [ExpandableObject]
        public FactSetOptionsEx FactSet { get; set; } = new FactSetOptionsEx();

        // ------ Actions------
        [ExpandableObject]
        public ActionOptionsEx Actions { get; set; } = new ActionOptionsEx();
    }

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class BoundaryOptionsEx
    {
        public BoundaryOptionsEx() { }

        public BoundaryOptionsEx(int allMargin)
        {
            Left = Right = Top = Bottom = allMargin;
        }
        public BoundaryOptionsEx(int left, int top, int right, int bottom)
        {
            Left = left;
            Top = top;
            Right = right;
            Bottom = bottom;
        }


        public int Left { get; set; }
        public int Top { get; set; }
        public int Right { get; set; }
        public int Bottom { get; set; }
    }

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class AdaptiveCardOptionsEx
    {
        public AdaptiveCardOptionsEx() { }

        /// <summary>
        ///  Padding for the card
        /// </summary>
        public BoundaryOptionsEx Padding { get; set; } = new BoundaryOptionsEx(8);

        /// <summary>
        /// Background color for card 
        /// </summary>
        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
        public string BackgroundColor { get; set; } = "#FFFFFF";
    }

    [JsonConverter(typeof(StringEnumConverter), true)]
    public enum ActionsOrientation
    {
        /// <summary>
        /// actions should be laid out horizontally
        /// </summary>
        Horizontal,

        /// <summary>
        /// Actions should be laid out vertically
        /// </summary>
        Vertical
    }


    /// <summary>
    /// Properties which control spacing and visual between elements
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class SeparationOptionsEx
    {
        public SeparationOptionsEx() { }

        /// <summary>
        /// Separation settings when Separation:default
        /// </summary>
        [ExpandableObject]
        public SeparationOption Default { get; set; } = new SeparationOption() { Spacing = 10 };

        /// <summary>
        /// Separation settings when Separation:Strong
        /// </summary>
        [ExpandableObject]
        public SeparationOption Strong { get; set; } = new SeparationOption() { Spacing = 20, LineThickness = 1, LineColor = "#FF707070" };
    }

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class SeparationOption
    {
        public SeparationOption() { }

        /// <summary>
        /// How much space between this element and previous should be used
        /// </summary>
        public int Spacing { get; set; }

        /// <summary>
        /// If there is a visible line, how thick should the line be
        /// </summary>
        public int LineThickness { get; set; }

        /// <summary>
        /// If there is a visible color, what color to use
        /// </summary>
        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
        public string LineColor { get; set; }

    }

    /// <summary>
    /// Properties which control rendering of TextBlock 
    /// </summary>
    //public class TextBlockOptions : CardElementOptions
    //{
    //    public TextBlockOptions() { }

    //}

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class FontSizeOptionsEx
    {
        public FontSizeOptionsEx() { }

        public int Small { get; set; } = 10;

        public int Normal { get; set; } = 12;

        public int Medium { get; set; } = 14;

        public int Large { get; set; } = 17;

        public int ExtraLarge { get; set; } = 20;

    }

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ColorOptionsEx
    {
        public ColorOptionsEx() { }

        [ExpandableObject]
        public ColorOptionEx Default { get; set; } = new ColorOptionEx("#FF000000");

        [ExpandableObject]
        public ColorOptionEx Accent { get; set; } = new ColorOptionEx("#FF0000FF");

        [ExpandableObject]
        public ColorOptionEx Dark { get; set; } = new ColorOptionEx("#FF101010");

        [ExpandableObject]
        public ColorOptionEx Light { get; set; } = new ColorOptionEx("#FFFFFFFF");

        [ExpandableObject]
        public ColorOptionEx Good { get; set; } = new ColorOptionEx("#FF008000");

        [ExpandableObject]
        public ColorOptionEx Warning { get; set; } = new ColorOptionEx("#FFFFD700");

        [ExpandableObject]
        public ColorOptionEx Attention { get; set; } = new ColorOptionEx("#FF8B0000");
    }

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ColorOptionEx
    {
        public ColorOptionEx(string normal, string subtle = null)
        {
            this.Normal = normal;
            if (subtle == null)
            {
                var opacity = (byte)(Convert.ToByte(normal.Substring(1, 2), 16) * .7);
                this.Subtle = $"#{opacity.ToString("x")}{normal.Substring(3)}";
            }
            else
                this.Subtle = subtle;
        }

        /// <summary>
        /// Color in #RRGGBB format
        /// </summary>
        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
        public string Normal { get; set; }

        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
        public string Subtle { get; set; }
    }

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ImageSizeOptionsEx

    {
        public ImageSizeOptionsEx() { }

        public int Small { get; set; } = 60;

        public int Medium { get; set; } = 120;

        public int Large { get; set; } = 180;
    }

    /// <summary>
    /// Properties which control rendering of actions
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ActionOptionsEx
    {
        public ActionOptionsEx() { }

        [ExpandableObject]
        public ShowCardOptionsEx ShowCard { get; set; } = new ShowCardOptionsEx();

        /// <summary>
        /// Arrange actions horizontal or vertical
        /// </summary>
        public ActionsOrientation ActionsOrientation { get; set; } = ActionsOrientation.Horizontal;

        /// <summary>
        /// should they be aligned Left, Center or Right
        /// </summary>
        public HorizontalAlignment ActionAlignment { get; set; } = HorizontalAlignment.Center;


        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
        public string BackgroundColor { get; set; } = "#FF5098FF";

        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
        public string BorderColor { get; set; } = "#FF000000";

        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
        public string TextColor { get; set; } = "#FFFFFFFF";

        public int BorderThickness { get; set; } = 1;

        public int FontWeight { get; set; } = 400;

        public int FontSize { get; set; } = 12;

        public int Spacing { get; set; } = 8;

        /// <summary>
        /// space between title and button edge
        /// </summary>
        [ExpandableObject]
        public BoundaryOptionsEx Padding { get; set; } = new BoundaryOptionsEx(4);

    }

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ShowCardOptionsEx
    {
        public ShowCardOptionsEx() { }

        public ShowCardActionMode ActionMode { get; set; } = ShowCardActionMode.Popup;

        /// <summary>
        /// Background color for showcard area
        /// </summary>
        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
        public string BackgroundColor { get; set; } = "#FFF8F8F8";

        /// <summary>
        /// If actionMode is inline and AutoPAdding is on then the background will extend to the edges of the parent card.
        /// </summary>
        public bool AutoPadding { get; set; } = false;
    }

    [JsonConverter(typeof(StringEnumConverter), true)]
    public enum ShowCardActionMode
    {
        Inline,
        Popup
    }


    public class ImageSetOptionsEx
    {
        public ImageSetOptionsEx() { }

        public ImageSize ImageSize { get; set; } = ImageSize.Medium;
    }

    public class FactSetOptionsEx
    {
        public FactSetOptionsEx() { }

        /// <summary>
        /// TextBlock to use for Titles in factsets
        /// </summary>
        [ExpandableObject]
        public TextOptionsEx Title { get; set; } = new TextOptionsEx() { Size = TextSize.Normal, Color = TextColor.Default, IsSubtle = false, Weight = TextWeight.Bolder };

        /// <summary>
        /// TextBlock to use for Values in fact sets
        /// </summary>
        [ExpandableObject]
        public TextOptionsEx Value { get; set; } = new TextOptionsEx();

        /// <summary>
        /// Spacing between facts and values
        /// </summary>
        public int Spacing { get; set; } = 20;
    }

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class TextOptionsEx
    {
        public TextOptionsEx()
        { }

        /// <summary>
        ///     The size of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextSize Size { get; set; } = TextSize.Normal;

        /// <summary>
        ///     The weight of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextWeight Weight { get; set; } = TextWeight.Normal;

        /// <summary>
        ///     The color of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextColor Color { get; set; } = TextColor.Default;

        /// <summary>
        ///     Should it be subtle?
        /// </summary>
        public bool IsSubtle { get; set; } = false;

        public bool ShouldSerializeSize()
        {
            return Size != TextSize.Normal;
        }

        public bool ShouldSerializeColor()
        {
            return Color != TextColor.Default;
        }


        public bool ShouldSerializeWeight()
        {
            return Weight != TextWeight.Normal;
        }

        public bool ShouldSerializeIsSubtle()
        {
            return IsSubtle;
        }
    }

}
