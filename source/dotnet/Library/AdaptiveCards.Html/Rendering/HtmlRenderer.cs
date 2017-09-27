using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Xml;
using HtmlTags;
using Microsoft.MarkedNet;
using AdaptiveCards.Html;
using AdaptiveCards.Rendering.Config;
using System.Xml.Linq;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    ///     Render as texthtml suitable for server side generation
    /// </summary>
    public class HtmlRenderer : AdaptiveRenderer<HtmlTag, RenderContext>
    {
        // ---------------- INTERNAL METHODS -----------------------------

        //        private static readonly Lazy<string> _stockCss = new Lazy<string>(() =>
        //        {
        //#if NET452
        //            var assembly = Assembly.GetExecutingAssembly();
        //            using (var stream = assembly.GetManifestResourceStream("AdaptiveCards.Rendering.AdaptiveCard.css"))
        //            using (var reader = new StreamReader(stream))
        //            {
        //                return reader.ReadToEnd();
        //            }
        //#else
        //            return null;
        //#endif
        //        });

        public HtmlRenderer(HostConfig config) : base(config)
        {
            SetObjectTypes();
        }

        ///// <summary>
        /////     Stock CSS you can use with the generated html
        ///// </summary>
        //public static string StockCss
        //{
        //    get { return _stockCss.Value; }
        //}

        public HtmlTag RenderAdaptiveCard(AdaptiveCard card)
        {
            var context = new RenderContext(this.DefaultConfig, this.ElementRenderers);
            return context.Render(card);
        }

        public HtmlTag RenderShowCard(ShowCardAction showCard)
        {
            return new RenderContext(this.DefaultConfig, this.ElementRenderers).Render(showCard.Card);
        }

        private void SetObjectTypes()
        {
            this.SetRenderer<AdaptiveCard>(AdaptiveCardRender);

            this.SetRenderer<TextBlock>(TextBlockRender);
            this.SetRenderer<Image>(ImageRender);

            this.SetRenderer<ActionSet>(ActionSetRender);
            this.SetRenderer<Container>(ContainerRender);
            this.SetRenderer<Column>(ColumnRender);
            this.SetRenderer<ColumnSet>(ColumnSetRender);
            this.SetRenderer<FactSet>(FactSetRender);
            this.SetRenderer<ImageSet>(ImageSetRender);

            this.SetRenderer<ChoiceSet>(ChoiceSetRender);
            this.SetRenderer<TextInput>(TextInputRender);
            this.SetRenderer<NumberInput>(NumberInputRender);
            this.SetRenderer<DateInput>(DateInputRender);
            this.SetRenderer<TimeInput>(TimeInputRender);
            this.SetRenderer<ToggleInput>(ToggleInputRender); ;

            this.SetRenderer<SubmitAction>(SubmitActionRender);
            this.SetRenderer<OpenUrlAction>(OpenUrlActionRender);
            this.SetRenderer<ShowCardAction>(ShowCardActionRender);
        }


        protected static HtmlTag OpenUrlActionRender(TypedElement actionElement, RenderContext context)
        {
            OpenUrlAction action = (OpenUrlAction)actionElement;

            if (!context.Config.SupportsInteractivity)
            {
                return null;
            }

            var buttonElement = new HtmlTag("button") { Text = action.Title }
                .Attr("type", "button")
                .Attr("url", action.Url)
                .Style("overflow", "hidden")
                .Style("white-space", "nowrap")
                .Style("text-overflow", "ellipsis")
                .Style("flex",
                    context.Config.Actions.ActionAlignment == HorizontalAlignment.Stretch ? "0 1 100%" : "0 1 auto")
                .AddClass("ac-pushButton")
                .AddClass("ac-openUrlAction");

            return buttonElement;
        }

        protected static HtmlTag ShowCardActionRender(TypedElement actionElement, RenderContext context)
        {
            ShowCardAction action = (ShowCardAction)actionElement;

            if (!context.Config.SupportsInteractivity)
            {
                return null;
            }

            var buttonElement = new HtmlTag("button") { Text = action.Title }
                .Attr("type", "button")
                .Style("overflow", "hidden")
                .Style("white-space", "nowrap")
                .Style("text-overflow", "ellipsis")
                .Style("flex",
                    context.Config.Actions.ActionAlignment == HorizontalAlignment.Stretch ? "0 1 100%" : "0 1 auto")
                .AddClass("ac-linkButton")
                .AddClass("ac-showCardAction");

            return buttonElement;
        }

        protected static HtmlTag SubmitActionRender(TypedElement actionElement, RenderContext context)
        {
            SubmitAction action = (SubmitAction)actionElement;

            if (!context.Config.SupportsInteractivity)
            {
                return null;
            }

            var buttonElement = new HtmlTag("button") { Text = action.Title }
                .Attr("type", "button")
                .Style("overflow", "hidden")
                .Style("white-space", "nowrap")
                .Style("text-overflow", "ellipsis")
                .Style("flex",
                    context.Config.Actions.ActionAlignment == HorizontalAlignment.Stretch ? "0 1 100%" : "0 1 auto")
                .AddClass("ac-pushButton")
                .AddClass("ac-submitAction");

            return buttonElement;
        }
        
        protected static HtmlTag AdaptiveCardRender(TypedElement element, RenderContext context)
        {
            AdaptiveCard card = (AdaptiveCard)element;
            var uiCard = new DivTag()
                .AddClass($"ac-{card.Type.ToLower()}")
                .Style("width", "100%")
                .Style("background-color", context.GetRGBColor(context.Config.AdaptiveCard.BackgroundColor))
                .Style("box-sizing", "border-box");

            if (card.BackgroundImage != null)
                uiCard = uiCard.Style("background-image", $"url('{card.BackgroundImage}')")
                    .Style("background-repeat", "no-repeat")
                    .Style("background-size", "cover");

            AddContainerElements(uiCard, card.Body, card.Actions, context);

            return uiCard;
        }

        protected static void AddContainerElements(HtmlTag uiContainer, List<CardElement> elements, List<ActionBase> actions, RenderContext context)
        {
            if (elements != null)
            {
                foreach (var cardElement in elements)
                {
                    // each element has a row
                    var uiElement = context.Render(cardElement);
                    if (uiElement != null)
                    {
                        if (uiContainer.Children.Any())
                        {
                            HtmlRenderer.AddSeparator(uiContainer, cardElement, context);
                        }

                        uiContainer.Children.Add(uiElement);
                    }
                }
            }

            if (context.Config.SupportsInteractivity && actions != null)
            {
                var uiButtonStrip = new DivTag()
                    .AddClass("ac-actionset")
                    .Style("display", "flex");

                // contains ShowCardAction.AdaptiveCard
                var uiShowCardStrip = new DivTag()
                    .Style("margin-top", context.Config.Actions.ShowCard.InlineTopMargin + "px");

                if (context.Config.Actions.ActionsOrientation == ActionsOrientation.Horizontal)
                {
                    uiButtonStrip.Style("flex-direction", "row");

                    switch (context.Config.Actions.ActionAlignment)
                    {
                        case HorizontalAlignment.Center:
                            uiButtonStrip.Style("justify-content", "center");
                            break;
                        case HorizontalAlignment.Right:
                            uiButtonStrip.Style("justify-content", "flex-end");
                            break;
                        default:
                            uiButtonStrip.Style("justify-content", "flex-start");
                            break;
                    }
                }
                else
                {
                    uiButtonStrip.Style("flex-direction", "column");
                    switch (context.Config.Actions.ActionAlignment)
                    {
                        case HorizontalAlignment.Center:
                            uiButtonStrip.Style("align-items", "center");
                            break;
                        case HorizontalAlignment.Right:
                            uiButtonStrip.Style("align-items", "flex-end");
                            break;
                        case HorizontalAlignment.Stretch:
                            uiButtonStrip.Style("align-items", "stretch");
                            break;
                        default:
                            uiButtonStrip.Style("align-items", "flex-start");
                            break;
                    }
                }

                var maxActions = Math.Min(context.Config.Actions.MaxActions, actions.Count);
                for (var i = 0; i < maxActions; i++)
                {
                    // add actions
                    var uiAction = context.Render(actions[i]);
                    if (uiAction != null)
                    {
                        if (actions[i].Type == ShowCardAction.TYPE)
                        {
                            // add button-card mapping for clients to implement showcard action
                            var cardId = "ac-showCard" + i;
                            uiAction.Attr("ac-cardId", cardId);

                            var uiCard = context.Render(((ShowCardAction)actions[i]).Card);
                            if (uiCard != null)
                            {
                                uiCard.Attr(cardId, string.Empty)
                                    .AddClass("ac-showCard")
                                    .Style("display", "none");
                                uiShowCardStrip.Children.Add(uiCard);
                            }
                        }
                        uiButtonStrip.Children.Add(uiAction);
                    }

                    // add spacer between buttons according to config
                    if (i < maxActions - 1 && context.Config.Actions.ButtonSpacing > 0)
                    {
                        var uiSpacer = new HtmlTag("div");

                        if (context.Config.Actions.ActionsOrientation == ActionsOrientation.Horizontal)
                        {
                            uiSpacer.Style("flex", "0 0 auto");
                            uiSpacer.Style("width", context.Config.Actions.ButtonSpacing + "px");
                        }
                        else
                        {
                            uiSpacer.Style("height", context.Config.Actions.ButtonSpacing + "px");
                        }
                        uiButtonStrip.Children.Add(uiSpacer);
                    }
                }

                if (uiButtonStrip.Children.Any())
                {
                    HtmlRenderer.AddSeparator(uiContainer, new ActionSet(), context);
                    uiContainer.Children.Add(uiButtonStrip);
                }

                if (uiShowCardStrip.Children.Any())
                {
                    uiContainer.Children.Add(uiShowCardStrip);
                }
            }
        }

        protected static void AddSeparator(HtmlTag uiContainer, CardElement cardElement, RenderContext context)
        {
            switch (cardElement.Separation)
            {
                case SeparationStyle.None:
                    return;
                case SeparationStyle.Default:
                    {
                        SeparationConfig sep = context.GetElementSeparation(cardElement);
                        var uiSep = new DivTag()
                            .AddClass("ac-separator")
                            .Style("height", $"{sep.Spacing}px");
                        uiContainer.Children.Add(uiSep);
                    }
                    return;
                case SeparationStyle.Strong:
                    {
                        SeparationConfig sep = context.Config.StrongSeparation;
                        var uiSep = new DivTag()
                                .AddClass("ac-separator")
                                .Style("padding-top", $"{sep.Spacing}px")
                                .Style("margin-top", $"{sep.Spacing}px")
                                .Style("border-top-color", $"{context.GetRGBColor(sep.LineColor)}")
                                .Style("border-top-width", $"{sep.LineThickness}px")
                                .Style("border-top-style", "solid")
                            ;
                        uiContainer.Children.Add(uiSep);
                    }
                    return;
            }
        }

        protected static HtmlTag ColumnRender(TypedElement element, RenderContext context)
        {
            Column column = (Column)element;
            var uiColumn = new DivTag()
                .AddClass($"ac-{element.Type.Replace(".", "").ToLower()}");

            AddContainerElements(uiColumn, column.Items, null, context);

            if (context.Config.SupportsInteractivity && column.SelectAction != null)
            {
                //var uiButton = (Button)RenderAction(container.SelectAction, new RenderContext(this.actionCallback, this.missingDataCallback));
                //if (uiButton != null)
                //{
                //    uiButton.Content = uiContainer;
                //    uiButton.Style = this.GetStyle("Adaptive.Action.Tap");
                //    return uiButton;
                //}
            }

            return uiColumn;
        }

        protected static HtmlTag ColumnSetRender(TypedElement element, RenderContext context)
        {
            ColumnSet columnSet = (ColumnSet)element;
            var uiColumnSet = new DivTag()
                .AddClass($"ac-{element.Type.Replace(".", "").ToLower()}")
                .Style("overflow", "hidden")
                .Style("display", "flex");

            var max = Math.Max(1.0, columnSet.Columns.Select(col =>
            {
                if (double.TryParse(col.Size ?? "0", out double val))
                    return val;
                return 0;
            }).Sum());

            foreach (var column in columnSet.Columns)
            {
                var uiColumn = context.Render(column);

                // Add horizontal Seperator
                if (uiColumnSet.Children.Any())
                {
                    SeparationConfig sep = null;
                    switch (column.Separation)
                    {
                        case SeparationStyle.None:
                            break;

                        case SeparationStyle.Default:
                            sep = context.Config.Column.Separation;
                            break;

                        case SeparationStyle.Strong:
                            sep = context.Config.StrongSeparation;
                            break;
                    }
                    if (sep != null)
                    {
                        uiColumnSet.Children.Add(new DivTag()
                            .AddClass($"ac-columnseparator")
                            .Style("flex", "0 0 auto")
                            .Style("padding-left", $"{sep.Spacing}px")
                            .Style("margin-left", $"{sep.Spacing}px")
                            .Style("border-left-color", $"{context.GetRGBColor(sep.LineColor)}")
                            .Style("border-left-width", $"{sep.LineThickness}px")
                            .Style("border-left-style", $"solid"));
                    }
                }

                // do some sizing magic 
                var size = column.Size?.ToLower();
                if (size == null || size == ColumnSize.Stretch.ToLower())
                {
                    uiColumn = uiColumn.Style("flex", "1 1 auto");
                }
                else if (size == ColumnSize.Auto.ToLower())
                {
                    uiColumn = uiColumn.Style("flex", "0 1 auto");
                }
                else
                {
                    double val;
                    if (double.TryParse(size, out val))
                    {
                        var percent = Convert.ToInt32(100 * (val / max));
                        uiColumn = uiColumn.Style("flex", $"1 1 {percent}%");
                    }
                    else
                    {
                        uiColumn = uiColumn.Style("flex", "0 0 auto");
                    }
                }

                uiColumnSet.Children.Add(uiColumn);
            }

            return uiColumnSet;
        }

        protected static HtmlTag ContainerRender(TypedElement element, RenderContext context)
        {
            Container container = (Container)element;
            var uiContainer = new DivTag()
                .AddClass($"ac-{element.Type.Replace(".", "").ToLower()}");

            AddContainerElements(uiContainer, container.Items, null, context);

            if (context.Config.SupportsInteractivity && container.SelectAction != null)
            {
                //var uiButton = (Button)RenderAction(container.SelectAction, new RenderContext(this.actionCallback, this.missingDataCallback));
                //if (uiButton != null)
                //{
                //    uiButton.Content = uiContainer;
                //    uiButton.Style = this.GetStyle("Adaptive.Action.Tap");
                //    return uiButton;
                //}
            }

            return uiContainer;
        }

        protected static HtmlTag ActionSetRender(TypedElement element, RenderContext context)
        {
            ActionSet actionSet = (ActionSet)element;
            var uiContainer = new DivTag()
                .AddClass($"ac-{element.Type.Replace(".", "").ToLower()}");
            AddContainerElements(uiContainer, null, actionSet.Actions, context);
            return uiContainer;
        }


        protected static HtmlTag FactSetRender(TypedElement element, RenderContext context)
        {
            FactSet factSet = (FactSet)element;
            var uiFactSet = (TableTag)new TableTag()
                .AddClass($"ac-{element.Type.Replace(".", "").ToLower()}")
                .Style("overflow", "hidden");

            foreach (var fact in factSet.Facts)
            {
                TextBlock factTitle = new TextBlock()
                {
                    Text = fact.Title,
                    Size = context.Config.FactSet.Title.Size,
                    Color = context.Config.FactSet.Title.Color,
                    Weight = context.Config.FactSet.Title.Weight,
                    IsSubtle = context.Config.FactSet.Title.IsSubtle,
                };
                var uiTitle = context.Render(factTitle)
                    .AddClass("ac-facttitle")
                    .Style("margin-right", $"{context.Config.FactSet.Spacing}px");

                TextBlock factValue = new TextBlock()
                {
                    Text = fact.Value,
                    Size = context.Config.FactSet.Value.Size,
                    Color = context.Config.FactSet.Value.Color,
                    Weight = context.Config.FactSet.Value.Weight,
                    IsSubtle = context.Config.FactSet.Value.IsSubtle,
                };
                var uiValue = context.Render(factValue)
                    .AddClass("ac-factvalue");

                // create row in factset 
                var uiRow = uiFactSet
                    .AddBodyRow();

                // add elements as cells
                uiRow.AddCell().AddClass("ac-factset-titlecell").Append(uiTitle);
                uiRow.AddCell().AddClass("ac-factset-valuecell").Append(uiValue);
            }
            return uiFactSet;
        }

        protected static HtmlTag TextBlockRender(TypedElement element, RenderContext context)
        {
            TextBlock textBlock = (TextBlock)element;

            int fontSize;
            switch (textBlock.Size)
            {
                case TextSize.Small:
                    fontSize = context.Config.FontSizes.Small;
                    break;
                case TextSize.Medium:
                    fontSize = context.Config.FontSizes.Medium;
                    break;
                case TextSize.Large:
                    fontSize = context.Config.FontSizes.Large;
                    break;
                case TextSize.ExtraLarge:
                    fontSize = context.Config.FontSizes.ExtraLarge;
                    break;
                case TextSize.Normal:
                default:
                    fontSize = context.Config.FontSizes.Normal;
                    break;
            }
            int weight = 400;
            switch (textBlock.Weight)
            {
                case TextWeight.Lighter:
                    weight = 200;
                    break;

                case TextWeight.Bolder:
                    weight = 600;
                    break;
            }
            var lineHeight = fontSize * 1.2;

            var uiTextBlock = new DivTag()
                .AddClass($"ac-{element.Type.Replace(".", "").ToLower()}")
                .Style("text-align", textBlock.HorizontalAlignment.ToString().ToLower())
                .Style("box-sizing", "border-box")
                .Style("color", context.GetColor(textBlock.Color, textBlock.IsSubtle))
                .Style("line-height", $"{lineHeight.ToString("F")}px")
                .Style("font-size", $"{fontSize}px")
                .Style("font-weight", $"{weight}");

            if (!String.IsNullOrEmpty(context.Config.FontFamily))
                uiTextBlock = uiTextBlock
                    .Style("font-family", context.Config.FontFamily);

            if (textBlock.MaxLines > 0)
                uiTextBlock = uiTextBlock
                    .Style("max-height", $"{lineHeight * textBlock.MaxLines}px")
                    .Style("overflow", "hidden");

            var setWrapStyleOnParagraph = false;
            if (textBlock.Wrap == false)
            {
                uiTextBlock = uiTextBlock
                    .Style("white-space", "nowrap");
                setWrapStyleOnParagraph = true;
            }
            else
            {
                uiTextBlock = uiTextBlock
                    .Style("word-wrap", "break-word");
            }

            var textTags = MarkdownToHtmlTagConverter.Convert(RendererUtilities.ApplyTextFunctions(textBlock.Text));
            uiTextBlock.Children.AddRange(textTags);

            Action<HtmlTag> setParagraphStyles = null;
            setParagraphStyles = (HtmlTag htmlTag) =>
            {
                if (htmlTag.Element?.ToLowerInvariant() == "p")
                {
                    htmlTag.Style("margin-top", "0px");
                    htmlTag.Style("margin-bottom", "0px");
                    htmlTag.Style("width", "100%");

                    if (setWrapStyleOnParagraph)
                    {
                        htmlTag.Style("text-overflow", "ellipsis");
                        htmlTag.Style("overflow", "hidden");
                    }
                }

                foreach (var child in htmlTag.Children)
                {
                    setParagraphStyles(child);
                }
            };

            setParagraphStyles(uiTextBlock);

            return uiTextBlock;
        }

        protected static HtmlTag ImageRender(TypedElement element, RenderContext context)
        {
            Image image = (Image)element;
            var uiDiv = new HtmlTag("div")
                .AddClass($"ac-{element.Type.Replace(".", "").ToLower()}")
                .Style("display", "block")
                .Style("box-sizing", "border-box");

            switch (image.Size)
            {
                case ImageSize.Auto:
                    uiDiv = uiDiv.Style("max-width", $"100%");
                    break;
                case ImageSize.Small:
                    uiDiv = uiDiv.Style("max-width", $"{context.Config.ImageSizes.Small}px");
                    break;
                case ImageSize.Medium:
                    uiDiv = uiDiv.Style("max-width", $"{context.Config.ImageSizes.Medium}px");
                    break;
                case ImageSize.Large:
                    uiDiv = uiDiv.Style("max-width", $"{context.Config.ImageSizes.Large}px");
                    break;
                case ImageSize.Stretch:
                    uiDiv = uiDiv.Style("width", $"100%");
                    break;
            }

            var uiImage = new HtmlTag("img")
                .Style("width", "100%")
                .Attr("src", image.Url);

            switch (image.Style)
            {
                case ImageStyle.Normal:
                    break;
                case ImageStyle.Person:
                    uiImage = uiImage.Style("background-position", "50% 50%")
                        .Style("border-radius", "50%")
                        .Style("background-repeat", "no-repeat");
                    break;
            }


            switch (image.HorizontalAlignment)
            {
                case HorizontalAlignment.Left:
                    uiDiv = uiDiv.Style("overflow", "hidden")
                        .Style("display", "block");
                    break;
                case HorizontalAlignment.Center:
                    uiDiv = uiDiv.Style("overflow", "hidden")
                        .Style("margin-right", "auto")
                        .Style("margin-left", "auto")
                        .Style("display", "block");
                    break;
                case HorizontalAlignment.Right:
                    uiDiv = uiDiv.Style("overflow", "hidden")
                        .Style("margin-left", "auto")
                        .Style("display", "block");
                    break;
            }
            uiDiv.Children.Add(uiImage);

            if (context.Config.SupportsInteractivity && image.SelectAction != null)
            {
                uiDiv.AddClass("ac-tap");
            }
            return uiDiv;
        }

        protected static HtmlTag ImageSetRender(TypedElement element, RenderContext context)
        {
            ImageSet imageSet = (ImageSet)element;
            var uiImageSet = new DivTag()
                .AddClass(imageSet.Type.ToLower());

            foreach (var image in imageSet.Images)
            {
                if (imageSet.ImageSize != ImageSize.Auto)
                    image.Size = imageSet.ImageSize;

                var uiImage = context.Render(image);
                uiImage = uiImage.Style("display", "inline-block");
                uiImageSet.Children.Add(uiImage);
            }
            return uiImageSet;
        }

        /// <summary>
        /// 1. IsMultiSelect == false && IsCompact == true => render as a drop down select element
        /// 2. IsMultiSelect == false && IsCompact == false => render as a list of radio buttons
        /// 3. IsMultiSelect == true => render as a list of toggle inputs
        /// </summary>
        protected static HtmlTag ChoiceSetRender(TypedElement element, RenderContext context)
        {
            ChoiceSet choiceSet = (ChoiceSet)element;
            if (!choiceSet.IsMultiSelect)
            {
                if (choiceSet.IsCompact)
                {
                    var uiSelectElement = new HtmlTag("select")
                        .Attr("name", choiceSet.Id)
                        .AddClass("ac-input")
                        .AddClass("ac-multichoiceInput")
                        .Style("width", "100%");

                    foreach (var choice in choiceSet.Choices)
                    {
                        var option = new HtmlTag("option") { Text = choice.Title }
                            .Attr("value", choice.Value);

                        if (choice.Value == choiceSet.Value)
                        {
                            option.Attr("selected", string.Empty);
                        }
                        uiSelectElement.Append(option);
                    }

                    return uiSelectElement;
                }
                else
                {
                    // render as a series of radio buttons
                    var uiElement = new HtmlTag("div")
                        .AddClass("ac-input")
                        .Style("width", "100%");

                    foreach (var choice in choiceSet.Choices)
                    {
                        var uiRadioInput = new HtmlTag("input")
                            .Attr("type", "radio")
                            .Attr("name", choiceSet.Id)
                            .Attr("value", choice.Value)
                            .Style("margin", "0px")
                            .Style("display", "inline-block")
                            .Style("vertical-align", "middle");

                        if (choice.Value == choiceSet.Value)
                        {
                            uiRadioInput.Attr("checked", string.Empty);
                        }

                        var uiLabel = context.Render(new TextBlock() { Text = choice.Title })
                            .Style("display", "inline-block")
                            .Style("margin-left", "6px")
                            .Style("vertical-align", "middle");

                        var compoundInputElement = new HtmlTag("div")
                            .Append(uiRadioInput)
                            .Append(uiLabel);

                        uiElement.Append(compoundInputElement);
                    }

                    return uiElement;
                }
            }
            else
            {
                // the default values are specified by a comma separated string input.value
                var defaultValues = choiceSet.Value?.Split(',').Select(p => p.Trim()).ToList() ?? new List<string>();

                // render as a list of toggle inputs
                var uiElement = new HtmlTag("div")
                    .AddClass("ac-input")
                    .Attr("width", "100%");

                foreach (var choice in choiceSet.Choices)
                {
                    var uiCheckboxInput = new HtmlTag("input")
                        .Attr("type", "checkbox")
                        .Attr("name", choiceSet.Id)
                        .Attr("value", choice.Value)
                        .Style("margin", "0px")
                        .Style("display", "inline-block")
                        .Style("vertical-align", "middle");

                    if (defaultValues.Contains(choice.Value))
                    {
                        uiCheckboxInput.Attr("checked", string.Empty);
                    }

                    var uiLabel = context.Render(new TextBlock() { Text = choice.Title })
                        .Style("display", "inline-block")
                        .Style("margin-left", "6px")
                        .Style("vertical-align", "middle");

                    var compoundInputElement = new HtmlTag("div")
                        .Append(uiCheckboxInput)
                        .Append(uiLabel);

                    uiElement.Append(compoundInputElement);
                }

                return uiElement;
            }
        }

        protected static HtmlTag DateInputRender(TypedElement element, RenderContext context)
        {
            DateInput input = (DateInput)element;

            var uiDateInput = new HtmlTag("input")
                .Attr("name", input.Id)
                .Attr("type", "date")
                .AddClass("ac-input")
                .AddClass("ac-dateInput")
                .Style("width", "100%");

            if (!string.IsNullOrEmpty(input.Value))
            {
                uiDateInput.Attr("value", input.Value);
            }

            if (!string.IsNullOrEmpty(input.Min))
            {
                uiDateInput.Attr("min", input.Min);
            }

            if (!string.IsNullOrEmpty(input.Max))
            {
                uiDateInput.Attr("max", input.Max);
            }

            return uiDateInput;
        }

        protected static HtmlTag NumberInputRender(TypedElement element, RenderContext context)
        {
            NumberInput input = (NumberInput)element;

            var uiNumberInput = new HtmlTag("input")
                .Attr("name", input.Id)
                .AddClass("ac-input")
                .AddClass("ac-numberInput")
                .Attr("type", "number")
                .Style("width", "100%");

            if (!double.IsNaN(input.Min))
            {
                uiNumberInput.Attr("min", input.Min.ToString());
            }

            if (!double.IsNaN(input.Max))
            {
                uiNumberInput.Attr("max", input.Max.ToString());
            }

            if (!double.IsNaN(input.Value))
            {
                uiNumberInput.Attr("value", input.Value.ToString());
            }

            return uiNumberInput;
        }

        protected static HtmlTag TextInputRender(TypedElement element, RenderContext context)
        {
            TextInput input = (TextInput)element;

            HtmlTag uiTextInput;
            if (input.IsMultiline)
            {
                uiTextInput = new HtmlTag("textarea");

                if (!string.IsNullOrEmpty(input.Value))
                {
                    uiTextInput.Text = input.Value;
                }
            }
            else
            {
                uiTextInput = new HtmlTag("input").Attr("type", "text");

                if (!string.IsNullOrEmpty(input.Value))
                {
                    uiTextInput.Attr("value", input.Value);
                }
            }

            uiTextInput
                .Attr("name", input.Id)
                .AddClass("ac-textinput")
                .AddClass("ac-input")
                .Style("width", "100%");

            if (!string.IsNullOrEmpty(input.Placeholder))
            {
                uiTextInput.Attr("placeholder", input.Placeholder);
            }

            if (input.MaxLength > 0)
            {
                uiTextInput.Attr("maxLength", input.MaxLength.ToString());
            }

            return uiTextInput;
        }

        protected static HtmlTag TimeInputRender(TypedElement element, RenderContext context)
        {
            TimeInput input = (TimeInput)element;
            var uiTimeInput = new HtmlTag("input")
                .Attr("type", "time")
                .Attr("name", input.Id)
                .AddClass("ac-input")
                .AddClass("ac-timeInput")
                .Style("width", "100%");

            if (!string.IsNullOrEmpty(input.Value))
            {
                uiTimeInput.Attr("value", input.Value);
            }

            if (!string.IsNullOrEmpty(input.Min))
            {
                uiTimeInput.Attr("min", input.Min);
            }

            if (!string.IsNullOrEmpty(input.Max))
            {
                uiTimeInput.Attr("max", input.Max);
            }

            return uiTimeInput;
        }

        protected static HtmlTag ToggleInputRender(TypedElement element, RenderContext context)
        {
            ToggleInput toggleInput = (ToggleInput)element;

            var uiElement = new HtmlTag("div")
                .AddClass("ac-input")
                .Style("width", "100%");

            var uiCheckboxInput = new HtmlTag("input")
                .Attr("type", "checkbox")
                .Attr("name", toggleInput.Id)
                .Style("display", "inline-block")
                .Style("vertical-align", "middle")
                .Style("margin", "0px");

            if (toggleInput.Value == toggleInput.ValueOn)
            {
                uiCheckboxInput.Attr("checked", string.Empty);
            }

            var uiLabel = context.Render(new TextBlock { Text = toggleInput.Title })
                .Style("display", "inline-block")
                .Style("margin-left", "6px")
                .Style("vertical-align", "middle");

            return uiElement.Append(uiCheckboxInput).Append(uiLabel);
        }

        protected static string GetFallbackText(CardElement cardElement)
        {
            if (!string.IsNullOrEmpty(cardElement.Speak))
            {
#if NET452
                // TODO: Fix xamarin fallback
                var doc = new XmlDocument();
                var xml = cardElement.Speak;
                if (!xml.Trim().StartsWith("<"))
                    xml = $"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Speak>{xml}</Speak>";
                else if (!xml.StartsWith("<?xml "))
                    xml = $"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n{xml}";
                doc.LoadXml(xml);
                return doc.InnerText;
#endif
            }
            return null;
        }
    }
}