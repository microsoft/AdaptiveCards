using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using PropertyChanged;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;
using Xceed.Wpf.Toolkit.PropertyGrid.Editors;

namespace WpfVisualizer
{
    [ImplementPropertyChanged]
    public class HostOptionsEx : INotifyPropertyChanged
    {
        public HostOptionsEx() { }

        //  ------ AdaptiveCard -------
        [ExpandableObject]
        public AdaptiveCardOptions AdaptiveCard { get; set; } = new AdaptiveCardOptions();

        [ExpandableObject]
        public ColorOptions Colors { get; set; } = new ColorOptions();

        // ------ Basic ------
        [ExpandableObject]
        public TextBlockOptions TextBlock { get; set; } = new TextBlockOptions();

        [ExpandableObject]
        public ImageOptions Image { get; set; } = new ImageOptions();

        // ------ Containers ------
        [ExpandableObject]
        public ContainerOptions Container { get; set; } = new ContainerOptions();

        [ExpandableObject]
        public ColumnSetOptions ColumnSet { get; set; } = new ColumnSetOptions();

        [ExpandableObject]
        public ColumnOptions Column { get; set; } = new ColumnOptions();

        [ExpandableObject]
        public ImageSetOptions ImageSet { get; set; } = new ImageSetOptions();

        [ExpandableObject]
        public FactSetOptions FactSet { get; set; } = new FactSetOptions();

        [ExpandableObject]
        public ActionSetOptions ActionSet { get; set; } = new ActionSetOptions();

        // ------ Input ------
        [ExpandableObject]
        public InputOptions Input { get; set; } = new InputOptions();

        // ------ Actions------
        [ExpandableObject]
        public ActionOptions Actions { get; set; } = new ActionOptions();

        public event PropertyChangedEventHandler PropertyChanged;
    }

    [ImplementPropertyChanged]
    public class AdaptiveCardOptions
    {
        public AdaptiveCardOptions() { }

        /// <summary>
        ///  Padding for the card
        /// </summary>
        [ExpandableObject]
        public BoundaryOptions Padding { get; set; } = new BoundaryOptions(8);

        /// <summary>
        /// Background color for card
        /// </summary>
        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
        public string BackgroundColor { get; set; } = "#FFFFFFFF";

        /// <summary>
        /// Font family for the card
        /// </summary>
        //[Editor(typeof(FontComboBoxEditor), typeof(FontComboBoxEditor))]
        public string FontFamily { get; set; } = "Calibri";

        /// <summary>
        /// Toggles whether or not to render inputs and actions
        /// </summary>
        public bool SupportsInteractivity { get; set; } = true;

        /// <summary>
        /// Arrange actions horizontal or vertical
        /// </summary>
        public ActionsOrientation ActionsOrientation { get; set; } = ActionsOrientation.Horizontal;

        /// <summary>
        /// should they be aligned Left, Center or Right
        /// </summary>
        public AdaptiveCards.HorizontalAlignment ActionAlignment { get; set; } = AdaptiveCards.HorizontalAlignment.Center;


        /// <summary>
        /// The types of Actions that you support(null for no actions)
        /// </summary>
        public string[] SupportedActions { get; set; } = new string[]
        {
            AdaptiveCards.OpenUrlAction.TYPE,
            AdaptiveCards.SubmitAction.TYPE,
            AdaptiveCards.HttpAction.TYPE,
            AdaptiveCards.ShowCardAction.TYPE
        };

        /// <summary>
        /// Max number of actions to support on your Cards(e.g., 3)
        /// </summary>
        public int MaxActions { get; set; } = 5;
    }

    public class BoundaryOptions
    {
        public BoundaryOptions() { }

        public BoundaryOptions(int allMargin)
        {
            Left = Right = Top = Bottom = allMargin;
        }
        public BoundaryOptions(int left, int top, int right, int bottom)
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
    /// Shared properties for elements
    /// </summary>
    [ImplementPropertyChanged]
    public class CardElementOptions
    {
        public CardElementOptions()
        { }

        /// <summary>
        /// Separation settings 
        /// </summary>
        [ExpandableObject]
        public SeparationOptions Separation { get; set; } = new SeparationOptions();
    }

    /// <summary>
    /// Properties which control spacing and visual between elements
    /// </summary>
    [ImplementPropertyChanged]
    public class SeparationOptions
    {
        public SeparationOptions() { }

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

    [ImplementPropertyChanged]
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
        public string LineColor { get; set; }
    }

    /// <summary>
    /// Properties which control rendering of TextBlock 
    /// </summary>
    [ImplementPropertyChanged]
    public class TextBlockOptions : CardElementOptions
    {
        public TextBlockOptions() { }

        /// <summary>
        /// FontSize
        /// </summary>
        [ExpandableObject]
        public FontSizeOptions FontSize { get; set; } = new FontSizeOptions();
    }

    [ImplementPropertyChanged]
    public class FontSizeOptions
    {
        public FontSizeOptions() { }

        public int Small { get; set; } = 10;

        public int Normal { get; set; } = 12;

        public int Medium { get; set; } = 14;

        public int Large { get; set; } = 17;

        public int ExtraLarge { get; set; } = 20;

    }

    [ImplementPropertyChanged]
    public class ColorOptions
    {
        public ColorOptions() { }

        [ExpandableObject]
        public ColorOption Default { get; set; } = new ColorOption("#FF000000");

        [ExpandableObject]
        public ColorOption Accent { get; set; } = new ColorOption("#FF0000FF");

        [ExpandableObject]
        public ColorOption Dark { get; set; } = new ColorOption("#FF101010");

        [ExpandableObject]
        public ColorOption Light { get; set; } = new ColorOption("#FFFFFFFF");

        [ExpandableObject]
        public ColorOption Good { get; set; } = new ColorOption("#FF008000");

        [ExpandableObject]
        public ColorOption Warning { get; set; } = new ColorOption("#FFFFD700");

        [ExpandableObject]
        public ColorOption Attention { get; set; } = new ColorOption("#FF8B0000");
    }

    public class ColorOption
    {
        public ColorOption(string normal, string subtle = null)
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

    /// <summary>
    /// properties which control rendering of Images
    /// </summary>
    [ImplementPropertyChanged]
    public class ImageOptions : CardElementOptions
    {
        public ImageOptions() { }

        [ExpandableObject]
        public ImageSizeOptions Size { get; set; } = new ImageSizeOptions();
    }

    [ImplementPropertyChanged]
    public class ImageSizeOptions

    {
        public ImageSizeOptions() { }

        public int Small { get; set; } = 60;

        public int Medium { get; set; } = 120;

        public int Large { get; set; } = 180;
    }

    /// <summary>
    /// Properties which control rendering of actions
    /// </summary>
    [ImplementPropertyChanged]
    public class ActionOptions
    {
        public ActionOptions() { }

        [ExpandableObject]
        public ShowCardOptions ShowCard { get; set; } = new ShowCardOptions();

        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
        public string BackgroundColor { get; set; } = "#FF5098FF";

        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
        public string BorderColor { get; set; } = "#FF000000";

        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
        public string TextColor { get; set; } = "#FFFFFFFF";

        public int BorderThickness { get; set; } = 1;

        public int FontWeight { get; set; } = 400;

        public int FontSize { get; set; } = 12;

        /// <summary>
        /// Space between actions
        /// </summary>
        [ExpandableObject]
        public BoundaryOptions Margin { get; set; } = new BoundaryOptions(4, 10, 4, 0);

        /// <summary>
        /// space between title and button edge
        /// </summary>

        [ExpandableObject]
        public BoundaryOptions Padding { get; set; } = new BoundaryOptions(4);
    }

    [ImplementPropertyChanged]
    public class ShowCardOptions
    {
        public ShowCardOptions() { }

        public ShowCardActionMode ActionMode { get; set; } = ShowCardActionMode.Popup;

        /// <summary>
        /// Background color for showcard area
        /// </summary>
        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
        public string BackgroundColor { get; set; } = "#FFF8F8F8";

        /// <summary>
        /// If actionMode is inline and AutoPadding is on then the background will extend to the edges of the parent card.
        /// </summary>
        public bool AutoPadding { get; set; } = false;

        /// <summary>
        /// Padding for showcard when Popup or AutoMargin=false
        /// </summary>
        [ExpandableObject]
        public BoundaryOptions Padding { get; set; } = new BoundaryOptions(10);
    }

    [JsonConverter(typeof(StringEnumConverter), true)]
    public enum ShowCardActionMode
    {
        Inline,
        Popup
    }

    [ImplementPropertyChanged]
    public class ContainerOptions : CardElementOptions
    {
        public ContainerOptions() { }

        public int MaxActions { get; set; } = 5;

        /// <summary>
        /// The types of Actions that you support(null for no actions)
        /// </summary>
        public string[] SupportedActions { get; set; } = new string[]
        {
            AdaptiveCards.OpenUrlAction.TYPE,
            AdaptiveCards.SubmitAction.TYPE,
            AdaptiveCards.HttpAction.TYPE,
            AdaptiveCards.ShowCardAction.TYPE
        };

    }

    [ImplementPropertyChanged]
    public class ImageSetOptions : CardElementOptions
    {
        public ImageSetOptions() { }

        public bool Wrap { get; set; } = true;
    }

    [ImplementPropertyChanged]
    public class FactSetOptions : CardElementOptions
    {
        public FactSetOptions() { }

        /// <summary>
        /// TextBlock to use for Titles in factsets
        /// </summary>
        [ExpandableObject]
        public AdaptiveCards.TextBlock Title { get; set; } = new AdaptiveCards.TextBlock() { Weight = AdaptiveCards.TextWeight.Bolder };

        /// <summary>
        /// TextBlock to use for Values in fact sets
        /// </summary>
        [ExpandableObject]
        public AdaptiveCards.TextBlock Value { get; set; } = new AdaptiveCards.TextBlock() { };
    }

    [ImplementPropertyChanged]
    public class InputOptions : CardElementOptions
    {
        public InputOptions() { }
    }


    [ImplementPropertyChanged]
    public class ColumnSetOptions : CardElementOptions
    {
        public ColumnSetOptions() { }
    }

    [ImplementPropertyChanged]
    public class ColumnOptions : CardElementOptions
    {
        public ColumnOptions() { }
    }

    public class ActionSetOptions : CardElementOptions
    {
        public ActionSetOptions() { }

        public int MaxActions { get; set; } = 5;

        /// <summary>
        /// The types of Actions that you support(null for no actions)
        /// </summary>
        public string[] SupportedActions { get; set; } = new string[]
        {
            AdaptiveCards.OpenUrlAction.TYPE,
            AdaptiveCards.SubmitAction.TYPE,
            AdaptiveCards.HttpAction.TYPE,
            AdaptiveCards.ShowCardAction.TYPE
        };
    }
}
