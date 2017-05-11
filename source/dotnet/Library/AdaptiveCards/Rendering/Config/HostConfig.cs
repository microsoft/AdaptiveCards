using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Serialization;
using System;
using System.Collections.Generic;
using System.Text;
using AdaptiveCards.Rendering;

namespace AdaptiveCards.Rendering.Config
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class HostConfig
    {
        public HostConfig() { }

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ActionConfig Actions { get; set; } = new ActionConfig();


        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveCardConfig AdaptiveCard { get; set; } = new AdaptiveCardConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ChoiceSetConfig ChoiceSet { get; set; } = new ChoiceSetConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ColorsConfig Colors { get; set; } = new ColorsConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ColumnConfig Column { get; set; } = new ColumnConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ColumnSetConfig ColumnSet { get; set; } = new ColumnSetConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ContainerConfig Container { get; set; } = new ContainerConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public DateInputConfig DateInput { get; set; } = new DateInputConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ImageSizesConfig ImageSizes { get; set; } = new ImageSizesConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ImageConfig Image { get; set; } = new ImageConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ImageSetConfig ImageSet { get; set; } = new ImageSetConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FactSetConfig FactSet { get; set; } = new FactSetConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string FontFamily { get; set; } = "Calibri";

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FontSizesConfig FontSizes { get; set; } = new FontSizesConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public NumberInputConfig NumberInput { get; set; } = new NumberInputConfig();


        /// <summary>
        /// Separation settings 
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public SeparationConfig StrongSeparation { get; set; } = new SeparationConfig() { Spacing = 20, LineThickness = 1, LineColor = "#FF707070" };

        /// <summary>
        /// Toggles whether or not to render inputs and actions
        /// </summary>
        public bool SupportsInteractivity { get; set; } = true;
        
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextBlockConfig TextBlock { get; set; } = new TextBlockConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextInputConfig TextInput { get; set; } = new TextInputConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TimeInputConfig TimeInput { get; set; } = new TimeInputConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ToggleInputConfig ToggleInput { get; set; } = new ToggleInputConfig();

        public virtual SeparationConfig GetSeparationForElement(TypedElement element, bool strong)
        {
            if (strong)
            {
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
                                return this.TextBlock.Separations.Small;
                            case TextSize.Normal:
                                return this.TextBlock.Separations.Normal;
                            case TextSize.Medium:
                                return this.TextBlock.Separations.Medium;
                            case TextSize.Large:
                                return this.TextBlock.Separations.Large;
                            case TextSize.ExtraLarge:
                                return this.TextBlock.Separations.ExtraLarge;
                        }
                    }
                    break;

                case AdaptiveCards.Image.TYPE:
                    return this.Image.Separation;

                case AdaptiveCards.Column.TYPE:
                    return this.Column.Separation;

                case AdaptiveCards.ColumnSet.TYPE:
                    return this.ColumnSet.Separation;

                case AdaptiveCards.Container.TYPE:
                    return this.Container.Separation;

                case AdaptiveCards.FactSet.TYPE:
                    return this.FactSet.Separation;

                case AdaptiveCards.ImageSet.TYPE:
                    return this.ImageSet.Separation;

                case AdaptiveCards.ActionSet.TYPE:
                    return this.Actions.Separation;

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
            return new SeparationConfig() { Spacing = 10 };
        }
    }

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class SpacingDefinition
    {
        public SpacingDefinition() { }

        public SpacingDefinition(int allMargin)
        {
            Left = Right = Top = Bottom = allMargin;
        }
        public SpacingDefinition(int left, int top, int right, int bottom)
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

