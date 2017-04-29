using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Serialization;
using System;
using System.Collections.Generic;
using System.Text;
using AdaptiveCards.Rendering;

namespace AdaptiveCards.Rendering.Options
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class HostOptions
    {
        public HostOptions() { }

        /// <summary>
        /// Font family for the card (can be comma delimited for fallback)
        /// </summary>
        public string FontFamily { get; set; } = "Calibri";

        /// <summary>
        /// FontSize
        /// </summary>
        public FontSizeOptions FontSizes { get; set; } = new FontSizeOptions();


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

        public ImageSizeOptions ImageSizes { get; set; } = new ImageSizeOptions();

        /// <summary>
        /// Separation settings 
        /// </summary>
        public SeparationOption StrongSeparation { get; set; } = new SeparationOption() { Spacing = 20, LineThickness = 1, LineColor = "#FF707070" };

        /// <summary>
        /// Color settings for the TextBlock
        /// </summary>
        public ColorOptions Colors { get; set; } = new ColorOptions();

        //  ------ AdaptiveCard -------
        public AdaptiveCardOptions AdaptiveCard { get; set; } = new AdaptiveCardOptions();

        // ------ Containers ------
        public ContainerOptions Container { get; set; } = new ContainerOptions();

        public ColumnOptions Column { get; set; } = new ColumnOptions();

        public ImageSetOptions ImageSet { get; set; } = new ImageSetOptions();

        public FactSetOptions FactSet { get; set; } = new FactSetOptions();

        public ActionSetOptions ActionSet { get; set; } = new ActionSetOptions();

        public ColumnSetOptions ColumnSet { get; set; } = new ColumnSetOptions();

        // ------- Elements -------
        public TextBlockOptions TextBlock { get; set; } = new TextBlockOptions();

        public ImageOptions Image { get; set; } = new ImageOptions();

        // ------- Inputs -------
        public DateInputOptions DateInput { get; set; } = new DateInputOptions();

        public TimeInputOptions TimeInput { get; set; } = new TimeInputOptions();

        public NumberInputOptions NumberInput { get; set; } = new NumberInputOptions();

        public ToggleInputOptions ToggleInput { get; set; } = new ToggleInputOptions();

        public TextInputOptions TextInput { get; set; } = new TextInputOptions();

        public ChoiceSetOptions ChoiceSet { get; set; } = new ChoiceSetOptions();

        // ------ Actions------
        public ActionOptions Actions { get; set; } = new ActionOptions();

        public SeparationOption GetSeparationForElement(TypedElement element, bool strong)
        {
            if (strong)
            {
                if (element.Type == AdaptiveCards.Column.TYPE)
                    return this.Column.Separations.Strong ?? this.StrongSeparation;
                return this.StrongSeparation;
            }

            switch (element.Type)
            {
                case AdaptiveCards.TextBlock.TYPE:
                    {
                        TextBlock tb = (TextBlock)element;
                        switch (tb.Size)
                        {
                            case TextSize.Small:
                                return this.TextBlock.Seperations.Small;
                            case TextSize.Normal:
                                return this.TextBlock.Seperations.Normal;
                            case TextSize.Medium:
                                return this.TextBlock.Seperations.Medium;
                            case TextSize.Large:
                                return this.TextBlock.Seperations.Large;
                            case TextSize.ExtraLarge:
                                return this.TextBlock.Seperations.ExtraLarge;
                        }
                    }
                    break;

                case AdaptiveCards.Image.TYPE:
                    return this.Image.Separation;

                case AdaptiveCards.Column.TYPE:
                    return this.Column.Separations.Default;

                case AdaptiveCards.ColumnSet.TYPE:
                    return this.ColumnSet.Separation;

                case AdaptiveCards.Container.TYPE:
                    return this.Container.Separation;

                case AdaptiveCards.FactSet.TYPE:
                    return this.FactSet.Separation;

                case AdaptiveCards.ImageSet.TYPE:
                    return this.ImageSet.Separation;

                case AdaptiveCards.ActionSet.TYPE:
                    return this.ActionSet.Separation;

                case AdaptiveCards.ChoiceSet.TYPE:
                    return this.ChoiceSet.Separation;

                case AdaptiveCards.TextInput.TYPE:
                    return this.TextInput.Separation;

                case AdaptiveCards.NumberInput.TYPE:
                    return this.NumberInput.Separation;

                case AdaptiveCards.TimeInput.TYPE:
                    return this.TimeInput.Separation;

                case AdaptiveCards.DateInput.TYPE:
                    return this.DateInput.Separation;

                case AdaptiveCards.ToggleInput.TYPE:
                    return this.ToggleInput.Separation;

                default:
                    break;
            }
            return new SeparationOption() { Spacing = 10 };
        }
    }

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
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







}

