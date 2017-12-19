using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net;
using Newtonsoft.Json;

namespace AdaptiveCards.Rendering.Html
{
    /// <summary>
    ///     Render a card as HTML suitable for server side generation
    /// </summary>
    public class AdaptiveCardRenderer : AdaptiveCardRendererBase<HtmlTag, AdaptiveRenderContext>
    {
        protected override AdaptiveSchemaVersion GetSupportedSchemaVersion()
        {
            return new AdaptiveSchemaVersion(1, 0);
        }

        /// <summary>
        /// Generate a ID, useful for joining two elements together, e.g., an input and label
        /// </summary>
        public static Func<string> GenerateRandomId => () => "ac-" + Guid.NewGuid().ToString().Substring(0, 8);

        /// <summary>
        /// Adds a CSS class to the action based on it's type name. Default is "ac-action-[actionName]
        /// </summary>
        public static Func<AdaptiveAction, string> GetActionCssClass = (action) =>
        {
            var lenFromDot = action.Type.IndexOf(".") + 1;
            var suffix = action.Type.Substring(lenFromDot, action.Type.Length - lenFromDot);
            return "ac-action-" + suffix.Replace(suffix[0], char.ToLower(suffix[0]));
        };

        /// <summary>
        /// A set of transforms that are applied to the HtmlTags for specific types
        /// </summary>
        public static AdaptiveRenderTransformers<HtmlTag, AdaptiveRenderContext> ActionTransformers { get; } = new AdaptiveRenderTransformers<HtmlTag, AdaptiveRenderContext>();

        public AdaptiveCardRenderer() : this(new AdaptiveHostConfig()) { }

        public AdaptiveCardRenderer(AdaptiveHostConfig config)
        {
            SetObjectTypes();
            HostConfig = config;
        }

        public RenderedAdaptiveCard RenderCard(AdaptiveCard card)
        {
            EnsureCanRender(card);

            try
            {
                var context = new AdaptiveRenderContext(HostConfig, ElementRenderers);
                var tag = context.Render(card);
                return new RenderedAdaptiveCard(tag, card, context.Warnings);
            }
            catch (Exception ex)
            {
                throw new AdaptiveRenderException("Failed to render card", ex)
                {
                    CardFallbackText = card.FallbackText
                };
            }
        }

        private void SetObjectTypes()
        {
            ElementRenderers.Set<AdaptiveCard>(AdaptiveCardRender);

            ElementRenderers.Set<AdaptiveTextBlock>(TextBlockRender);
            ElementRenderers.Set<AdaptiveImage>(ImageRender);

            ElementRenderers.Set<AdaptiveContainer>(ContainerRender);
            ElementRenderers.Set<AdaptiveColumn>(ColumnRender);
            ElementRenderers.Set<AdaptiveColumnSet>(ColumnSetRender);
            ElementRenderers.Set<AdaptiveFactSet>(FactSetRender);
            ElementRenderers.Set<AdaptiveImageSet>(ImageSetRender);

            ElementRenderers.Set<AdaptiveChoiceSetInput>(ChoiceSetRender);
            ElementRenderers.Set<AdaptiveTextInput>(TextInputRender);
            ElementRenderers.Set<AdaptiveNumberInput>(NumberInputRender);
            ElementRenderers.Set<AdaptiveDateInput>(DateInputRender);
            ElementRenderers.Set<AdaptiveTimeInput>(TimeInputRender);
            ElementRenderers.Set<AdaptiveToggleInput>(ToggleInputRender);

            ElementRenderers.Set<AdaptiveSubmitAction>(AdaptiveActionRender);
            ElementRenderers.Set<AdaptiveOpenUrlAction>(AdaptiveActionRender);
            ElementRenderers.Set<AdaptiveShowCardAction>(AdaptiveActionRender);

            ActionTransformers.Register<AdaptiveOpenUrlAction>((action, tag, context) => tag.Attr("data-ac-url", action.Url));
            ActionTransformers.Register<AdaptiveSubmitAction>((action, tag, context) => tag.Attr("data-ac-submitData", JsonConvert.SerializeObject(action.Data, Formatting.None)));
            ActionTransformers.Register<AdaptiveShowCardAction>((action, tag, context) => tag.Attr("data-ac-showCardId", GenerateRandomId()));
        }

        protected static HtmlTag AddActionAttributes(AdaptiveAction action, HtmlTag tag, AdaptiveRenderContext context)
        {
            tag.AddClass(GetActionCssClass(action))
                .Attr("role", "button")
                .Attr("aria-label", action.Title ?? "");

            ActionTransformers.Apply(action, tag, context);

            return tag;
        }

        protected static HtmlTag AdaptiveActionRender(AdaptiveAction action, AdaptiveRenderContext context)
        {
            if (context.Config.SupportsInteractivity)
            {
                var buttonElement = new HtmlTag("button", false) { Text = action.Title }
                    .Attr("type", "button")
                    .Style("overflow", "hidden")
                    .Style("white-space", "nowrap")
                    .Style("text-overflow", "ellipsis")
                    .Style("flex",
                        context.Config.Actions.ActionAlignment == AdaptiveHorizontalAlignment.Stretch ? "0 1 100%" : "0 1 auto")
                    .AddClass("ac-pushButton");

                AddActionAttributes(action, buttonElement, context);
                return buttonElement;
            }

            return null;
        }

        protected static HtmlTag AdaptiveCardRender(AdaptiveCard card, AdaptiveRenderContext context)
        {
            var uiCard = new DivTag()
                .AddClass($"ac-{card.Type.ToLower()}")
                .Style("width", "100%")
                .Style("background-color", context.GetRGBColor(context.Config.ContainerStyles.Default.BackgroundColor))
                .Style("padding", $"{context.Config.Spacing.Padding}px")
                .Style("box-sizing", "border-box");

            if (!string.IsNullOrEmpty(context.Config.FontFamily))
                uiCard.Style("font-family", context.Config.FontFamily);

            if (card.BackgroundImage != null)
                uiCard.Style("background-image", $"url('{card.BackgroundImage}')")
                    .Style("background-repeat", "no-repeat")
                    .Style("background-size", "cover");

            AddContainerElements(uiCard, card.Body, card.Actions, context);

            return uiCard;
        }

        protected static void AddContainerElements(HtmlTag uiContainer, IList<AdaptiveElement> elements, IList<AdaptiveAction> actions, AdaptiveRenderContext context)
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
                            AddSeparator(uiContainer, cardElement, context);
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

                // TODO: This top marging is currently being double applied, will have to investigate later
                //.Style("margin-top", $"{context.Config.GetSpacing(context.Config.Actions.Spacing)}px");

                // contains ShowCardAction.AdaptiveCard
                var showCards = new List<HtmlTag>();

                if (context.Config.Actions.ActionsOrientation == ActionsOrientation.Horizontal)
                {
                    uiButtonStrip.Style("flex-direction", "row");

                    switch (context.Config.Actions.ActionAlignment)
                    {
                        case AdaptiveHorizontalAlignment.Center:
                            uiButtonStrip.Style("justify-content", "center");
                            break;
                        case AdaptiveHorizontalAlignment.Right:
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
                        case AdaptiveHorizontalAlignment.Center:
                            uiButtonStrip.Style("align-items", "center");
                            break;
                        case AdaptiveHorizontalAlignment.Right:
                            uiButtonStrip.Style("align-items", "flex-end");
                            break;
                        case AdaptiveHorizontalAlignment.Stretch:
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
                        if (actions[i] is AdaptiveShowCardAction showCardAction)
                        {
                            var cardId = uiAction.Attributes["data-ac-showCardId"];

                            var uiCard = context.Render(showCardAction.Card);
                            if (uiCard != null)
                            {
                                uiCard.Attr("id", cardId)
                                    .AddClass("ac-showCard")
                                    .Style("padding", "0")
                                    .Style("display", "none")
                                    .Style("margin-top", $"{context.Config.Actions.ShowCard.InlineTopMargin}px");

                                showCards.Add(uiCard);
                            }
                        }
                        uiButtonStrip.Children.Add(uiAction);
                    }

                    // add spacer between buttons according to config
                    if (i < maxActions - 1 && context.Config.Actions.ButtonSpacing > 0)
                    {
                        var uiSpacer = new DivTag();

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
                    AdaptiveCardRenderer.AddSeparator(uiContainer, new AdaptiveContainer(), context);
                    uiContainer.Children.Add(uiButtonStrip);
                }

                foreach (var showCard in showCards)
                {
                    uiContainer.Children.Add(showCard);
                }
            }
        }

        protected static void AddSeparator(HtmlTag uiContainer, AdaptiveElement adaptiveElement, AdaptiveRenderContext context)
        {
            if (!adaptiveElement.Separator && adaptiveElement.Spacing == AdaptiveSpacing.None)
            {
                return;
            }

            int spacing = context.Config.GetSpacing(adaptiveElement.Spacing);

            if (adaptiveElement.Separator)
            {
                SeparatorConfig sep = context.Config.Separator;
                var uiSep = new DivTag()
                        .AddClass("ac-separator")
                        .Style("padding-top", $"{spacing / 2}px")
                        .Style("margin-top", $"{spacing / 2}px")
                        .Style("border-top-color", $"{context.GetRGBColor(sep.LineColor)}")
                        .Style("border-top-width", $"{sep.LineThickness}px")
                        .Style("border-top-style", "solid");
                uiContainer.Children.Add(uiSep);
            }
            else
            {
                var uiSep = new DivTag()
                    .AddClass("ac-separator")
                    .Style("height", $"{spacing}px");
                uiContainer.Children.Add(uiSep);
            }
        }

        protected static HtmlTag ColumnRender(AdaptiveColumn column, AdaptiveRenderContext context)
        {
            var uiColumn = new DivTag()
                .AddClass($"ac-{column.Type.Replace(".", "").ToLower()}");

            AddContainerElements(uiColumn, column.Items, null, context);

            // selectAction
            if (context.Config.SupportsInteractivity && column.SelectAction != null)
            {
                uiColumn.AddClass("ac-selectable");
                AddActionAttributes(column.SelectAction, uiColumn, context);
            }

            return uiColumn;
        }

        protected static HtmlTag ColumnSetRender(AdaptiveColumnSet columnSet, AdaptiveRenderContext context)
        {
            var uiColumnSet = new DivTag()
                .AddClass($"ac-{columnSet.Type.Replace(".", "").ToLower()}")
                .Style("overflow", "hidden")
                .Style("display", "flex");

            // selectAction
            if (context.Config.SupportsInteractivity && columnSet.SelectAction != null)
            {
                uiColumnSet.AddClass("ac-selectable");
                AddActionAttributes(columnSet.SelectAction, uiColumnSet, context);
            }

            var max = Math.Max(1.0, columnSet.Columns.Select(col =>
            {
                if (col.Width != null && double.TryParse(col.Width, out double widthVal))
                    return widthVal;
#pragma warning disable CS0618 // Type or member is obsolete
                if (double.TryParse(col.Size ?? "0", out double val))
#pragma warning restore CS0618 // Type or member is obsolete
                    return val;
                return 0;
            }).Sum());

            foreach (var column in columnSet.Columns)
            {
                var uiColumn = context.Render(column);

                // Add horizontal Seperator
                if (uiColumnSet.Children.Any() && (column.Separator || column.Spacing != AdaptiveSpacing.None))
                {
                    SeparatorConfig sep = context.Config.Separator;

                    int spacing = context.Config.GetSpacing(column.Spacing) / 2;
                    int lineThickness = column.Separator ? sep.LineThickness : 0;

                    if (sep != null)
                    {
                        uiColumnSet.Children.Add(new DivTag()
                            .AddClass($"ac-columnseparator")
                            .Style("flex", "0 0 auto")
                            .Style("padding-left", $"{spacing}px")
                            .Style("margin-left", $"{spacing}px")
                            .Style("border-left-color", $"{context.GetRGBColor(sep.LineColor)}")
                            .Style("border-left-width", $"{lineThickness}px")
                            .Style("border-left-style", $"solid"));
                    }
                }

                // do some sizing magic 
                var width = column.Width?.ToLower();
                if (string.IsNullOrEmpty(width))
#pragma warning disable CS0618 // Type or member is obsolete
                    width = column.Size?.ToLower();
#pragma warning restore CS0618 // Type or member is obsolete
                if (width == null || width == AdaptiveColumnWidth.Stretch.ToLower())
                {
                    uiColumn = uiColumn.Style("flex", "1 1 auto");
                }
                else if (width == AdaptiveColumnWidth.Auto.ToLower())
                {
                    uiColumn = uiColumn.Style("flex", "0 1 auto");
                }
                else
                {
                    double val;
                    if (double.TryParse(width, out val))
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

        protected static HtmlTag ContainerRender(AdaptiveContainer container, AdaptiveRenderContext context)
        {
            var uiContainer = new DivTag()
                .AddClass($"ac-{container.Type.Replace(".", "").ToLower()}");

            AddContainerElements(uiContainer, container.Items, null, context);

            if (context.Config.SupportsInteractivity && container.SelectAction != null)
            {
                uiContainer.AddClass("ac-selectable");
                AddActionAttributes(container.SelectAction, uiContainer, context);
            }

            return uiContainer;
        }

        protected static HtmlTag FactSetRender(AdaptiveFactSet factSet, AdaptiveRenderContext context)
        {
            var uiFactSet = (TableTag)new TableTag()
                .AddClass($"ac-{factSet.Type.Replace(".", "").ToLower()}")
                .Style("overflow", "hidden");

            foreach (var fact in factSet.Facts)
            {
                AdaptiveTextBlock factTitle = new AdaptiveTextBlock()
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

                AdaptiveTextBlock factValue = new AdaptiveTextBlock()
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

        protected static HtmlTag TextBlockRender(AdaptiveTextBlock textBlock, AdaptiveRenderContext context)
        {
            int fontSize;
            switch (textBlock.Size)
            {
                case AdaptiveTextSize.Small:
                    fontSize = context.Config.FontSizes.Small;
                    break;
                case AdaptiveTextSize.Medium:
                    fontSize = context.Config.FontSizes.Medium;
                    break;
                case AdaptiveTextSize.Large:
                    fontSize = context.Config.FontSizes.Large;
                    break;
                case AdaptiveTextSize.ExtraLarge:
                    fontSize = context.Config.FontSizes.ExtraLarge;
                    break;
                case AdaptiveTextSize.Default:
                default:
                    fontSize = context.Config.FontSizes.Default;
                    break;
            }
            int weight = 400;
            switch (textBlock.Weight)
            {
                case AdaptiveTextWeight.Lighter:
                    weight = 200;
                    break;

                case AdaptiveTextWeight.Bolder:
                    weight = 600;
                    break;
            }

            // Not sure where this magic value comes from?
            var lineHeight = fontSize * 1.33;

            var uiTextBlock = new HtmlTag("div", false)
                .AddClass($"ac-{textBlock.Type.Replace(".", "").ToLower()}")
                .Style("box-sizing", "border-box")
                .Style("text-align", textBlock.HorizontalAlignment.ToString().ToLower())
                .Style("color", context.GetColor(textBlock.Color, textBlock.IsSubtle))
                .Style("line-height", $"{lineHeight.ToString("F")}px")
                .Style("font-size", $"{fontSize}px")
                .Style("font-weight", $"{weight}");


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

        protected static HtmlTag ImageRender(AdaptiveImage image, AdaptiveRenderContext context)
        {
            var uiDiv = new DivTag()
                .AddClass($"ac-{image.Type.Replace(".", "").ToLower()}")
                .Style("display", "block")
                .Style("box-sizing", "border-box");

            switch (image.Size)
            {
                case AdaptiveImageSize.Auto:
                    uiDiv = uiDiv.Style("max-width", $"100%");
                    break;
                case AdaptiveImageSize.Small:
                    uiDiv = uiDiv.Style("max-width", $"{context.Config.ImageSizes.Small}px");
                    break;
                case AdaptiveImageSize.Medium:
                    uiDiv = uiDiv.Style("max-width", $"{context.Config.ImageSizes.Medium}px");
                    break;
                case AdaptiveImageSize.Large:
                    uiDiv = uiDiv.Style("max-width", $"{context.Config.ImageSizes.Large}px");
                    break;
                case AdaptiveImageSize.Stretch:
                    uiDiv = uiDiv.Style("width", $"100%");
                    break;
            }

            var uiImage = new HtmlTag("img")
                .Style("width", "100%")
                .Attr("alt", image.AltText ?? "card image")
                .Attr("src", image.Url.ToString());

            switch (image.Style)
            {
                case AdaptiveImageStyle.Default:
                    break;
                case AdaptiveImageStyle.Person:
                    uiImage = uiImage.Style("background-position", "50% 50%")
                        .Style("border-radius", "50%")
                        .Style("background-repeat", "no-repeat");
                    break;
            }


            switch (image.HorizontalAlignment)
            {
                case AdaptiveHorizontalAlignment.Left:
                    uiDiv = uiDiv.Style("overflow", "hidden")
                        .Style("display", "block");
                    break;
                case AdaptiveHorizontalAlignment.Center:
                    uiDiv = uiDiv.Style("overflow", "hidden")
                        .Style("margin-right", "auto")
                        .Style("margin-left", "auto")
                        .Style("display", "block");
                    break;
                case AdaptiveHorizontalAlignment.Right:
                    uiDiv = uiDiv.Style("overflow", "hidden")
                        .Style("margin-left", "auto")
                        .Style("display", "block");
                    break;
            }
            uiDiv.Children.Add(uiImage);

            if (context.Config.SupportsInteractivity && image.SelectAction != null)
            {
                uiDiv.AddClass("ac-selectable");
                AddActionAttributes(image.SelectAction, uiDiv, context);
            }
            return uiDiv;
        }

        protected static HtmlTag ImageSetRender(AdaptiveImageSet imageSet, AdaptiveRenderContext context)
        {
            var uiImageSet = new DivTag()
                .AddClass(imageSet.Type.ToLower());

            foreach (var image in imageSet.Images)
            {
                if (imageSet.ImageSize != AdaptiveImageSize.Auto)
                    image.Size = imageSet.ImageSize;

                var uiImage = context.Render(image)
                    .Style("display", "inline-block")
                    .Style("margin-right", "10px");

                uiImageSet.Children.Add(uiImage);
            }
            return uiImageSet;
        }

        /// <summary>
        /// 1. IsMultiSelect == false && IsCompact == true => render as a drop down select element
        /// 2. IsMultiSelect == false && IsCompact == false => render as a list of radio buttons
        /// 3. IsMultiSelect == true => render as a list of toggle inputs
        /// </summary>
        protected static HtmlTag ChoiceSetRender(AdaptiveChoiceSetInput adaptiveChoiceSetInput, AdaptiveRenderContext context)
        {
            if (!adaptiveChoiceSetInput.IsMultiSelect)
            {
                if (adaptiveChoiceSetInput.Style == AdaptiveChoiceInputStyle.Compact)
                {
                    var uiSelectElement = new HtmlTag("select")
                        .Attr("name", adaptiveChoiceSetInput.Id)
                        .AddClass("ac-input")
                        .AddClass("ac-multichoiceInput")
                        .Style("width", "100%");

                    foreach (var choice in adaptiveChoiceSetInput.Choices)
                    {
                        var option = new HtmlTag("option") { Text = choice.Title }
                            .Attr("value", choice.Value);

                        if (choice.Value == adaptiveChoiceSetInput.Value)
                        {
                            option.Attr("selected", string.Empty);
                        }
                        uiSelectElement.Append(option);
                    }

                    return uiSelectElement;
                }
                else
                {
                    return ChoiceSetRenderInternal(adaptiveChoiceSetInput, context, "radio");
                }
            }
            else
            {
                return ChoiceSetRenderInternal(adaptiveChoiceSetInput, context, "checkbox");
            }
        }

        private static HtmlTag ChoiceSetRenderInternal(AdaptiveChoiceSetInput adaptiveChoiceSetInput, AdaptiveRenderContext context, string htmlInputType)
        {
            // the default values are specified by a comma separated string input.value
            var defaultValues = adaptiveChoiceSetInput.Value?.Split(',').Select(p => p.Trim()).Where(s => !string.IsNullOrEmpty(s)).ToList() ?? new List<string>();

            // render as a series of radio buttons
            var uiElement = new DivTag()
                .AddClass("ac-input")
                .Style("width", "100%");

            foreach (var choice in adaptiveChoiceSetInput.Choices)
            {
                var htmlLabelId = GenerateRandomId();

                var uiInput = new HtmlTag("input")
                    .Attr("id", htmlLabelId)
                    .Attr("type", htmlInputType)
                    .Attr("name", adaptiveChoiceSetInput.Id)
                    .Attr("value", choice.Value)
                    .Style("margin", "0px")
                    .Style("display", "inline-block")
                    .Style("vertical-align", "middle");


                if (defaultValues.Contains(choice.Value))
                {
                    uiInput.Attr("checked", string.Empty);
                }

                var uiLabel = CreateLabel(htmlLabelId, choice.Title, context);

                var compoundInputElement = new DivTag()
                    .Append(uiInput)
                    .Append(uiLabel);

                uiElement.Append(compoundInputElement);
            }

            return uiElement;

        }

        private static HtmlTag CreateLabel(string forId, string innerText, AdaptiveRenderContext context)
        {
            var tag = new HtmlTag("label")
                .SetInnerText(innerText)
                .Attr("for", forId);
            ApplyDefaultTextAttributes(tag, context);
            return tag;
        }

        private static void ApplyDefaultTextAttributes(HtmlTag tag, AdaptiveRenderContext context)
        {
            tag.Style("color", context.GetColor(AdaptiveTextColor.Default, false))
                .Style("font-size", $"{context.Config.FontSizes.Default}px")
                .Style("display", "inline-block")
                .Style("margin-left", "6px")
                .Style("vertical-align", "middle");
        }

        protected static HtmlTag DateInputRender(AdaptiveDateInput input, AdaptiveRenderContext context)
        {
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

        protected static HtmlTag NumberInputRender(AdaptiveNumberInput input, AdaptiveRenderContext context)
        {
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

        protected static HtmlTag TextInputRender(AdaptiveTextInput input, AdaptiveRenderContext context)
        {
            HtmlTag uiTextInput;
            if (input.IsMultiline)
            {
                uiTextInput = new HtmlTag("textarea", false);

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

        protected static HtmlTag TimeInputRender(AdaptiveTimeInput input, AdaptiveRenderContext context)
        {
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

        protected static HtmlTag ToggleInputRender(AdaptiveToggleInput toggleInput, AdaptiveRenderContext context)
        {
            var htmlLabelId = GenerateRandomId();

            var uiElement = new DivTag()
                .AddClass("ac-input")
                .Style("width", "100%");

            var uiCheckboxInput = new HtmlTag("input")
                .Attr("id", htmlLabelId)
                .Attr("type", "checkbox")
                .Attr("name", toggleInput.Id)
                .Attr("data-ac-valueOn", toggleInput.ValueOn ?? bool.TrueString)
                .Attr("data-ac-valueOff", toggleInput.ValueOff ?? bool.FalseString)
                .Style("display", "inline-block")
                .Style("vertical-align", "middle")
                .Style("margin", "0px");

            if (toggleInput.Value == toggleInput.ValueOn)
            {
                uiCheckboxInput.Attr("checked", string.Empty);
            }

            var uiLabel = CreateLabel(htmlLabelId, toggleInput.Title, context);

            return uiElement.Append(uiCheckboxInput).Append(uiLabel);
        }

        protected static string GetFallbackText(AdaptiveElement adaptiveElement)
        {
#pragma warning disable CS0618 // Type or member is obsolete
            if (!string.IsNullOrEmpty(adaptiveElement.Speak))
            {
#if NET452
                var doc = new System.Xml.XmlDocument();
                var xml = adaptiveElement.Speak;
                if (!xml.Trim().StartsWith("<"))
                    xml = $"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Speak>{xml}</Speak>";
                else if (!xml.StartsWith("<?xml "))
                    xml = $"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n{xml}";
                doc.LoadXml(xml);
                return doc.InnerText;
#endif
            }
#pragma warning restore CS0618 // Type or member is obsolete
            return null;
        }
    }
}