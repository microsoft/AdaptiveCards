using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using System;
using System.Collections.Generic;
using System.Text;

namespace AdaptiveCards.Rendering
{
    public class RendererOptions
    {
        public RendererOptions() { }

        //  ------ AdaptiveCard -------
        public AdaptiveCardOptions AdaptiveCard { get; set; } = new AdaptiveCardOptions();

        // ------ Basic ------
        public TextBlockOptions TextBlock { get; set; } = new TextBlockOptions();

        public ImageOptions Image { get; set; } = new ImageOptions();

        // ------ Containers ------
        public ContainerOptions Container { get; set; } = new ContainerOptions();

        public ColumnSetOptions ColumnSet { get; set; } = new ColumnSetOptions();

        public ColumnOptions Column { get; set; } = new ColumnOptions();

        public ImageSetOptions ImageSet { get; set; } = new ImageSetOptions();

        public FactSetOptions FactSet { get; set; } = new FactSetOptions();

        // ------ Input ------
        public InputOptions Input { get; set; } = new InputOptions();

        // ------ Actions------
        public ActionOptions Actions { get; set; } = new ActionOptions();

        public CardElementOptions GetElementStyling(object obj)
        {
            if (obj is TextBlock)
                return this.TextBlock;
            if (obj is Image)
                return this.Image;
            if (obj is Container)
                return this.Container;
            if (obj is ColumnSet)
                return this.ColumnSet;
            if (obj is Column)
                return this.Column;
            if (obj is ImageSet)
                return this.ImageSet;
            if (obj is ImageSet)
                return this.ImageSet;
            if (obj is FactSet)
                return this.FactSet;
            if (obj is InputText)
                return this.Input;
            if (obj is InputNumber)
                return this.Input;
            if (obj is InputDate)
                return this.Input;
            if (obj is InputTime)
                return this.Input;
            if (obj is InputChoiceSet)
                return this.Input;
            if (obj is InputToggle)
                return this.Input;
            throw new ArgumentException($"Unknown type {obj.GetType().Name}");
        }
    }

    public class AdaptiveCardOptions
    {
        public AdaptiveCardOptions() { }

        /// <summary>
        ///  Margin for the card
        /// </summary>
        public int[] Margin = new[] { 8, 8, 8, 8 };

        /// <summary>
        /// Background color for card
        /// </summary>
        public string BackgroundColor { get; set; } = "#FFFFFFFF";

        /// <summary>
        /// Text color for card (shared by FactSet, TextBlock)
        /// </summary>
        public string TextColor { get; set; } = "#FF000000";

        /// <summary>
        /// Font family for the card
        /// </summary>
        public string FontFamily = "Calibri";

        /// <summary>
        /// Arrange actions horizontal or vertical
        /// </summary>
        public ActionsOrientation ActionsOrientation { get; set; } = ActionsOrientation.Horizontal;

        /// <summary>
        /// should they be aligned Left, Center or Right
        /// </summary>
        public HorizontalAlignment ActionAlignment { get; set; } = HorizontalAlignment.Center;

        /// <summary>
        /// Toggles whether or not to render inputs and actions
        /// </summary>
        public bool SupportsInteractivity { get; set; } = true;

        /// <summary>
        /// The types of Actions that you support(null for no actions)
        /// </summary>
        public string[] SupportedActions { get; set; } = new string[]
        {
            ActionOpenUrl.TYPE,
            ActionSubmit.TYPE,
            ActionHttp.TYPE,
            ActionShowCard.TYPE
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
    public class CardElementOptions
    {
        public CardElementOptions()
        { }

        /// <summary>
        /// Separation settings when Separation:none
        /// </summary>
        public SeparationOptions SeparationNone { get; set; } = new SeparationOptions() { Spacing = 0, Thickness = 0 };

        /// <summary>
        /// Separation settings when Separation:default
        /// </summary>
        public SeparationOptions SeparationDefault { get; set; } = new SeparationOptions() { Spacing = 10, Thickness = 0 };

        /// <summary>
        /// Separation settings when Separation:Strong
        /// </summary>
        public SeparationOptions SeparationStrong { get; set; } = new SeparationOptions() { Spacing = 20, Thickness = 1, Color = "#FF707070" };
    }

    /// <summary>
    /// Properties which control spacing and visual between elements
    /// </summary>
    public class SeparationOptions
    {
        public SeparationOptions() { }

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
        public string Color { get; set; }
    }

    /// <summary>
    /// Properties which control rendering of TextBlock 
    /// </summary>
    public class TextBlockOptions : CardElementOptions
    {
        public TextBlockOptions() { }

        /// <summary>
        /// Color settings for the TextBlock
        /// </summary>
        public TextColorOptions Color { get; set; } = new TextColorOptions();

        /// <summary>
        /// FontSize
        /// </summary>
        public FontSizeOptions FontSize { get; set; } = new FontSizeOptions();


        public double IsSubtleOpacity { get; set; } = .5;
    }

    public class FontSizeOptions
    {
        public FontSizeOptions() { }

        public int Small { get; set; } = 10;

        public int Normal { get; set; } = 12;

        public int Medium { get; set; } = 14;

        public int Large { get; set; } = 17;

        public int ExtraLarge { get; set; } = 20;

    }

    public class TextColorOptions
    {
        public TextColorOptions() { }

        /// <summary>
        /// Default color for TextBlock
        /// </summary>
        public string Default { get; set; } = "#FF000000";

        public string Accent { get; set; } = "#FF0000FF";

        public string Dark { get; set; } = "#FF101010";

        public string Light { get; set; } = "#FFFFFFFF";

        public string Good { get; set; } = "#FF008000";

        public string Warning { get; set; } = "#FFFFD700";

        public string Attention { get; set; } = "#FF8B0000";
    }

    /// <summary>
    /// properties which control rendering of Images
    /// </summary>
    public class ImageOptions : CardElementOptions
    {
        public ImageOptions() { }

        public ImageSizeOptions Size { get; set; } = new ImageSizeOptions();
    }

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
    public class ActionOptions
    {
        public ActionOptions() { }

        public ShowCardOptions ShowCard { get; set; } = new ShowCardOptions();

        public string BackgroundColor { get; set; } = "#FF5098FF";

        public string BorderColor { get; set; } = "#FF000000";

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

    public class ShowCardOptions
    {
        public ShowCardOptions() { }

        public ShowCardActionMode ActionMode { get; set; } = ShowCardActionMode.Popup;
    }

    [JsonConverter(typeof(StringEnumConverter), true)]
    public enum ShowCardActionMode
    {
        Inline,
        Popup
    }

    public class ContainerOptions : CardElementOptions
    {
        public ContainerOptions() { }

        public int MaxActions { get; set; } = 5;

        /// <summary>
        /// The types of Actions that you support(null for no actions)
        /// </summary>
        public string[] SupportedActions { get; set; } = new string[]
        {
            ActionOpenUrl.TYPE,
            ActionSubmit.TYPE,
            ActionHttp.TYPE,
            ActionShowCard.TYPE
        };

    }

    public class ImageSetOptions : CardElementOptions
    {
        public ImageSetOptions() { }

        public bool Wrap { get; set; } = true;
    }

    public class FactSetOptions : CardElementOptions
    {
        public FactSetOptions() { }

        /// <summary>
        /// TextBlock to use for Titles in factsets
        /// </summary>
        public TextBlock Title { get; set; } = new TextBlock() { Weight = TextWeight.Bolder };

        /// <summary>
        /// TextBlock to use for Values in fact sets
        /// </summary>
        public TextBlock Value { get; set; } = new TextBlock() { };
    }

    public class InputOptions : CardElementOptions
    {
        public InputOptions() { }
    }

    public class ColumnSetOptions : CardElementOptions
    {
        public ColumnSetOptions() { }
    }

    public class ColumnOptions : CardElementOptions
    {
        public ColumnOptions() { }
    }
}
