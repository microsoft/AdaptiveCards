using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Text;

namespace AdaptiveCards.Rendering
{
    public class CardStyling
    {
        public CardStyling() { }

        /// <summary>
        ///  Margin for the card
        /// </summary>

        public int[] Margin = new[] { 8, 8, 8, 8 };

        /// <summary>
        /// Background color for card
        /// </summary>
        public string BackgroundColor { get; set; } = "#FFFFFFFF";

        /// <summary>
        /// Arrange actions horizontal or vertical
        /// </summary>
        public bool ActionsVertical { get; set; } = false;

        /// <summary>
        /// For actions, should they be aligned Left, Center or Right
        /// </summary>
        public HorizontalAlignment ActionAlignment { get; set; } = HorizontalAlignment.Center;

        // ------ Basic ------
        public TextBlockStyling TextBlock { get; set; } = new TextBlockStyling();

        public ImageStyling Image { get; set; } = new ImageStyling();

        // ------ Containers ------
        public CardElementStyling Container { get; set; } = new CardElementStyling();

        public CardElementStyling ColumnSet { get; set; } = new CardElementStyling();

        public CardElementStyling Column { get; set; } = new CardElementStyling();

        public CardElementStyling ImageSet { get; set; } = new CardElementStyling();

        public CardElementStyling FactSet { get; set; } = new CardElementStyling();

        // ------ Input ------
        public CardElementStyling InputText { get; set; } = new CardElementStyling();

        public CardElementStyling InputNumber { get; set; } = new CardElementStyling();

        public CardElementStyling InputDate { get; set; } = new CardElementStyling();

        public CardElementStyling InputTime { get; set; } = new CardElementStyling();

        public CardElementStyling InputChoiceSet { get; set; } = new CardElementStyling();

        public CardElementStyling InputToggle { get; set; } = new CardElementStyling();

        // ------ Actions------
        public ActionStyling ActionShowCard { get; set; } = new ActionStyling();

        public ActionStyling ActionSubmit { get; set; } = new ActionStyling();

        public ActionStyling ActionHttp { get; set; } = new ActionStyling();

        public ActionStyling ActionOpenUrl { get; set; } = new ActionStyling();

        public CardElementStyling GetElementStyling(object obj)
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
                return this.InputText;
            if (obj is InputNumber)
                return this.InputNumber;
            if (obj is InputDate)
                return this.InputDate;
            if (obj is InputTime)
                return this.InputTime;
            if (obj is InputChoiceSet)
                return this.InputChoiceSet;
            if (obj is InputToggle)
                return this.InputToggle;
            throw new ArgumentException($"Unknown type {obj.GetType().Name}");
        }

        public ActionStyling GetActionStyling(ActionBase action)
        {
            if (action is ActionOpenUrl)
                return this.ActionOpenUrl;
            if (action is ActionSubmit)
                return this.ActionSubmit;
            if (action is ActionHttp)
                return this.ActionHttp;
            if (action is ActionShowCard)
                return this.ActionShowCard;
            throw new ArgumentException($"Unknown action {action.GetType().Name}");
        }
    }


    /// <summary>
    /// Shared properties for elements
    /// </summary>
    public class CardElementStyling
    {
        public CardElementStyling()
        { }

        /// <summary>
        /// Separation settings when Separation:none
        /// </summary>
        public SeparationStyling SeparationNone { get; set; } = new SeparationStyling() { Spacing = 0, Thickness = 0 };

        /// <summary>
        /// Separation settings when Separation:default
        /// </summary>
        public SeparationStyling SeparationDefault { get; set; } = new SeparationStyling() { Spacing = 10, Thickness = 0 };

        /// <summary>
        /// Separation settings when Separation:Strong
        /// </summary>
        public SeparationStyling SeparationStrong { get; set; } = new SeparationStyling() { Spacing = 20, Thickness = 1, Color = "#FF707070" };
    }

    /// <summary>
    /// Properties which control spacing and visual between elements
    /// </summary>
    public class SeparationStyling
    {
        public SeparationStyling() { }

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
    public class TextBlockStyling : CardElementStyling
    {
        public TextBlockStyling() { }

        public string ColorDefault { get; set; } = "#FF000000";
        public string ColorAccent { get; set; } = "#FF0000FF";
        public string ColorDark { get; set; } = "#FF101010";
        public string ColorLight { get; set; } = "#FFFFFFFF";
        public string ColorGood { get; set; } = "#FF008000";
        public string ColorWarning { get; set; } = "#FFFFD700";
        public string ColorAttention { get; set; } = "#FF8B0000";

        public string FontFamily = "Calibri";

        public int FontSizeSmall { get; set; } = 10;
        public int FontSizeNormal { get; set; } = 12;
        public int FontSizeMedium { get; set; } = 14;
        public int FontSizeLarge { get; set; } = 17;
        public int FontSizeExtraLarge { get; set; } = 20;


        public int FontWeightLighter { get; set; } = 200;
        public int FontWeightNormal { get; set; } = 400;
        public int FontWeightBolder { get; set; } = 800;

        public double IsSubtleOpacity = .5;
    }

    /// <summary>
    /// properties which control rendering of Images
    /// </summary>
    public class ImageStyling : CardElementStyling
    {
        public ImageStyling() { }

        public int SizeSmall { get; set; } = 60;
        public int SizeMedium { get; set; } = 120;
        public int SizeLarge { get; set; } = 180;
    }

    /// <summary>
    /// Properties which control rendering of actions
    /// </summary>
    public class ActionStyling
    {
        public ActionStyling() { }

        public string BackgroundColor { get; set; } = "#FF5098FF";

        public string BorderColor { get; set; } = "#FF000000";

        public string TextColor { get; set; } = "#FFFFFFFF";

        public int BorderThickness { get; set; } = 1;

        public int FontWeight { get; set; } = 400;

        public int FontSize { get; set; } = 12;

        public int[] Margin { get; set; } = new int[] { 4 };

        public int[] TitleMargin { get; set; } = new int[] { 4 };
    }
}
