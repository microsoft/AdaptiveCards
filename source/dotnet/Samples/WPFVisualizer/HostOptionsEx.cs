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
        ///  Margin for the card
        /// </summary>
        public int[] Margin { get; set; } = new[] { 8, 8, 8, 8 };

        /// <summary>
        /// Background color for card
        /// </summary>
        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
        public string BackgroundColor { get; set; } = "#FFFFFFFF";

        /// <summary>
        /// Text color for card (shared by FactSet, TextBlock)
        /// </summary>
        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
        public string TextColor { get; set; } = "#FF000000";

        /// <summary>
        /// Font family for the card
        /// </summary>
        //[Editor(typeof(FontComboBoxEditor), typeof(FontComboBoxEditor))]
        public string FontFamily { get; set; } = "Calibri";

        /// <summary>
        /// Arrange actions horizontal or vertical
        /// </summary>
        public ActionsOrientation ActionsOrientation { get; set; } = ActionsOrientation.Horizontal;

        /// <summary>
        /// should they be aligned Left, Center or Right
        /// </summary>
        public AdaptiveCards.HorizontalAlignment ActionAlignment { get; set; } = AdaptiveCards.HorizontalAlignment.Center;

        /// <summary>
        /// Toggles whether or not to render inputs and actions
        /// </summary>
        public bool SupportsInteractivity { get; set; } = true;

        /// <summary>
        /// The types of Actions that you support(null for no actions)
        /// </summary>
        public string[] SupportedActions { get; set; } = new string[]
        {
            AdaptiveCards.ActionOpenUrl.TYPE,
            AdaptiveCards.ActionSubmit.TYPE,
            AdaptiveCards.ActionHttp.TYPE,
            AdaptiveCards.ActionShowCard.TYPE
        };

        /// <summary>
        /// Max number of actions to support on your Cards(e.g., 3)
        /// </summary>
        public int MaxActions { get; set; } = 5;
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
        /// Separation settings when Separation:none
        /// </summary>
        [ExpandableObject]
        public SeparationOption None { get; set; } = new SeparationOption() { Spacing = 0, Thickness = 0 };

        /// <summary>
        /// Separation settings when Separation:default
        /// </summary>
        [ExpandableObject]
        public SeparationOption Default { get; set; } = new SeparationOption() { Spacing = 10, Thickness = 0 };

        /// <summary>
        /// Separation settings when Separation:Strong
        /// </summary>
        [ExpandableObject]
        public SeparationOption Strong { get; set; } = new SeparationOption() { Spacing = 20, Thickness = 1, Color = "#FF707070" };
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
        public int Thickness { get; set; }

        /// <summary>
        /// If there is a visible color, what color to use
        /// </summary>
        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
        public string Color { get; set; }

    }

    /// <summary>
    /// Properties which control rendering of TextBlock 
    /// </summary>
    [ImplementPropertyChanged]
    public class TextBlockOptions : CardElementOptions
    {
        public TextBlockOptions() { }

        /// <summary>
        /// Color settings for the TextBlock
        /// </summary>
        [ExpandableObject]
        public TextColorOptions Color { get; set; } = new TextColorOptions();

        /// <summary>
        /// FontSize
        /// </summary>
        [ExpandableObject]
        public FontSizeOptions FontSize { get; set; } = new FontSizeOptions();


        public double IsSubtleOpacity { get; set; } = .5;
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
    public class TextColorOptions
    {
        public TextColorOptions() { }

        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
        public string Accent { get; set; } = "#FF0000FF";

        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
        public string Dark { get; set; } = "#FF101010";

        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
        public string Light { get; set; } = "#FFFFFFFF";

        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
        public string Good { get; set; } = "#FF008000";

        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
        public string Warning { get; set; } = "#FFFFD700";

        [Editor(typeof(ColorEditor), typeof(ColorEditor))]
        public string Attention { get; set; } = "#FF8B0000";
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
        public int[] Margin { get; set; } = new int[] { 4, 10, 4, 0 };

        /// <summary>
        /// space between title and button edge
        /// </summary>

        public int[] Padding { get; set; } = new int[] { 4 };
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
        /// margins for showcard when inline
        /// </summary>
        public int[] Margin { get; set; } = new int[] { -8, 10, -8, 10 };

        /// <summary>
        /// Padding for showcard when inline
        /// </summary>
        public int[] Padding { get; set; } = new int[] { 8, 10, 8, 0 };
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
            AdaptiveCards.ActionOpenUrl.TYPE,
            AdaptiveCards.ActionSubmit.TYPE,
            AdaptiveCards.ActionHttp.TYPE,
            AdaptiveCards.ActionShowCard.TYPE
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
}
