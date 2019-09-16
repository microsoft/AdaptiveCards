// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net;
using Newtonsoft.Json;
using AdaptiveCards;

namespace AdaptiveCards.Rendering.Html
{
    /// <summary>
    ///     Render a card as HTML suitable for server side generation
    /// </summary>
    public class AdaptiveCardRenderer : AdaptiveCardRendererBase<HtmlTag, AdaptiveRenderContext>
    {
        protected override AdaptiveSchemaVersion GetSupportedSchemaVersion()
        {
            return new AdaptiveSchemaVersion(1, 3);
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
        public static AdaptiveRenderTransformers<HtmlTag, AdaptiveRenderContext> ActionTransformers { get; } = InitActionTransformers();

        public AdaptiveCardRenderer() : this(new AdaptiveHostConfig()) { }

        public AdaptiveCardRenderer(AdaptiveHostConfig config)
        {
            SetObjectTypes();
            HostConfig = config;
        }

        public AdaptiveFeatureRegistration FeatureRegistration { get; } = new AdaptiveFeatureRegistration();

        public RenderedAdaptiveCard RenderCard(AdaptiveCard card)
        {
            try
            {
                var context = new AdaptiveRenderContext(HostConfig, ElementRenderers);
                context.FeatureRegistration = FeatureRegistration;
                context.Lang = card.Lang;
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
            ElementRenderers.Set<AdaptiveRichTextBlock>(RichTextBlockRender);

            ElementRenderers.Set<AdaptiveImage>(ImageRender);
            ElementRenderers.Set<AdaptiveMedia>(MediaRender);

            ElementRenderers.Set<AdaptiveContainer>(ContainerRender);
            ElementRenderers.Set<AdaptiveColumn>(ColumnRender);
            ElementRenderers.Set<AdaptiveColumnSet>(ColumnSetRender);
            ElementRenderers.Set<AdaptiveFactSet>(FactSetRender);
            ElementRenderers.Set<AdaptiveImageSet>(ImageSetRender);
            ElementRenderers.Set<AdaptiveActionSet>(ActionSetRender);

            ElementRenderers.Set<AdaptiveChoiceSetInput>(ChoiceSetRender);
            ElementRenderers.Set<AdaptiveTextInput>(TextInputRender);
            ElementRenderers.Set<AdaptiveNumberInput>(NumberInputRender);
            ElementRenderers.Set<AdaptiveDateInput>(DateInputRender);
            ElementRenderers.Set<AdaptiveTimeInput>(TimeInputRender);
            ElementRenderers.Set<AdaptiveToggleInput>(ToggleInputRender);

            ElementRenderers.Set<AdaptiveSubmitAction>(AdaptiveActionRender);
            ElementRenderers.Set<AdaptiveOpenUrlAction>(AdaptiveActionRender);
            ElementRenderers.Set<AdaptiveShowCardAction>(AdaptiveActionRender);
            ElementRenderers.Set<AdaptiveToggleVisibilityAction>(AdaptiveActionRender);
        }

        private static AdaptiveRenderTransformers<HtmlTag, AdaptiveRenderContext> InitActionTransformers()
        {
            var transformers = new AdaptiveRenderTransformers<HtmlTag, AdaptiveRenderContext>();
            transformers.Register<AdaptiveOpenUrlAction>((action, tag, context) => tag.Attr("data-ac-url", action.Url));
            transformers.Register<AdaptiveSubmitAction>((action, tag, context) => tag.Attr("data-ac-submitData", JsonConvert.SerializeObject(action.Data, Formatting.None)));
            transformers.Register<AdaptiveShowCardAction>((action, tag, context) =>
            {
                var showCardId = GenerateRandomId();
                tag.Attr("data-ac-showCardId", showCardId);
                tag.Attr("aria-controls", showCardId);
                tag.Attr("aria-expanded", bool.FalseString);
            });

            return transformers;
        }

        protected static HtmlTag AddActionAttributes(AdaptiveAction action, HtmlTag tag, AdaptiveRenderContext context)
        {
            tag.AddClass(GetActionCssClass(action))
                .Attr("role", "button")
                .Attr("aria-label", action.Title ?? "")
                .Attr("tabindex", "0");


            AdaptiveToggleVisibilityAction toggleVisibilityAction = null;
            if ((toggleVisibilityAction = action as AdaptiveToggleVisibilityAction) != null)
            {
                string targetElements = string.Empty;

                foreach (var targetElement in toggleVisibilityAction.TargetElements)
                {
                    // If the string is not empty, append a comma in preparation to add the new target element
                    if (!String.IsNullOrWhiteSpace(targetElements))
                    {
                        targetElements += ",";
                    }

                    string targetElementId = null;
                    string targetElementToggleAction = "Toggle";

                    if (targetElement != null)
                    {
                        targetElementId = targetElement.ElementId;

                        if (targetElement.IsVisible.HasValue)
                        {
                            targetElementToggleAction = targetElement.IsVisible.Value.ToString();
                        }
                    }

                    targetElements += (targetElementId + ":" + targetElementToggleAction);
                }

                tag.Attr("data-ac-targetelements", targetElements);
            }

            ActionTransformers.Apply(action, tag, context);

            return tag;
        }

        protected static HtmlTag AddInlineActionAttributes(AdaptiveAction action, HtmlTag tag, AdaptiveRenderContext context)
        {
            tag.AddClass(GetActionCssClass(action) + "-inline")
                .Attr("role", "button")
                .Attr("aria-label", action.Title ?? "");

            ActionTransformers.Apply(action, tag, context);

            return tag;
        }

        protected static HtmlTag AdaptiveActionRender(AdaptiveAction action, AdaptiveRenderContext context)
        {
            if (context.Config.SupportsInteractivity)
            {
                var actionsConfig = context.Config.Actions;
                var buttonElement = new HtmlTag("button", false)
                    .Attr("type", "button")
                    .Style("overflow", "hidden")
                    .Style("white-space", "nowrap")
                    .Style("text-overflow", "ellipsis")
                    .Style("flex",
                        actionsConfig.ActionAlignment == AdaptiveHorizontalAlignment.Stretch ? "0 1 100%" : "0 1 auto")
                    .Style("display", "flex")
                    .Style("align-items", "center")
                    .Style("justify-content", "center")
                    .AddClass("ac-pushButton");


                if (!String.IsNullOrWhiteSpace(action.Style) && !String.Equals(action.Style, "default", StringComparison.OrdinalIgnoreCase))
                {
                    if (String.Equals(action.Style, "positive", StringComparison.OrdinalIgnoreCase))
                    {
                        string accentColor = context.Config.ContainerStyles.Default.ForegroundColors.Accent.Default;
                        string lighterAccentColor = ColorUtil.GenerateLighterColor(accentColor);
                        buttonElement.Style("background-color", context.GetRGBColor(accentColor));
                        buttonElement.Attr("onMouseOver", "this.style.backgroundColor='" + context.GetRGBColor(lighterAccentColor) + "'");
                        buttonElement.Attr("onMouseOut", "this.style.backgroundColor='" + context.GetRGBColor(accentColor) + "'");
                        buttonElement.Style("color", "#FFFFFF");
                        buttonElement.AddClass("ac-action-positive");
                    }
                    else if (String.Equals(action.Style, "destructive", StringComparison.OrdinalIgnoreCase))
                    {
                        string attentionColor = context.Config.ContainerStyles.Default.ForegroundColors.Attention.Default;
                        string lighterAttentionColor = ColorUtil.GenerateLighterColor(attentionColor);
                        buttonElement.Style("color", context.GetRGBColor(attentionColor));
                        buttonElement.Attr("onMouseOver", "this.style.color='" + context.GetRGBColor(lighterAttentionColor) + "'");
                        buttonElement.Attr("onMouseOut", "this.style.color='" + context.GetRGBColor(attentionColor) + "'");
                        buttonElement.AddClass("ac-action-destructive");
                    }
                    else
                    {
                        buttonElement.AddClass("ac-action-" + action.Style);
                    }
                }

                var hasTitle = !string.IsNullOrEmpty(action.Title);

                if (action.IconUrl != null)
                {
                    // Append the icon to the button
                    // NOTE: always using icon size since it's difficult
                    // to match icon's height with text's height
                    var iconElement = new HtmlTag("image", false)
                        .Attr("src", action.IconUrl)
                        .Style("max-height", $"{actionsConfig.IconSize}px");

                    if (actionsConfig.IconPlacement == IconPlacement.LeftOfTitle)
                    {
                        buttonElement.Style("flex-direction", "row");

                        if (hasTitle)
                        {
                            iconElement.Style("margin-right", "4px");
                        }
                    }
                    else
                    {
                        buttonElement.Style("flex-direction", "column");

                        if (hasTitle)
                        {
                            iconElement.Style("margin-bottom", "4px");
                        }
                    }

                    buttonElement.Append(iconElement);
                }

                var titleElement = new HtmlTag("div", false) { Text = action.Title };
                buttonElement.Append(titleElement);

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

            if (card.BackgroundImage != null)
            {
                ApplyBackgroundImage(card.BackgroundImage, uiCard, context);
            }

            if (card.PixelMinHeight > 0)
            {
                uiCard.Style("min-height", card.PixelMinHeight + "px");
            }

            // Reset the parent style
            context.RenderArgs.ParentStyle = AdaptiveContainerStyle.Default;

            switch (card.VerticalContentAlignment)
            {
                case AdaptiveVerticalContentAlignment.Center:
                    uiCard.Style("justify-content", "center");
                    break;
                case AdaptiveVerticalContentAlignment.Bottom:
                    uiCard.Style("justify-content", "flex-end");
                    break;
                case AdaptiveVerticalContentAlignment.Top:
                default:
                    uiCard.Style("justify-content", "flex-start");
                    break;
            }

            AddContainerElements(uiCard, card.Body, context);
            AddActions(uiCard, card.Actions, context);

            AddSelectAction(uiCard, card.SelectAction, context);

            // Add all accumulated selectAction show cards
            foreach (var showCard in context.ShowCardTags)
            {
                uiCard.Children.Add(showCard);
            }

            return uiCard;
        }

        protected static void AddSelectAction(HtmlTag tag, AdaptiveAction selectAction, AdaptiveRenderContext context)
        {
            if (context.Config.SupportsInteractivity && selectAction != null)
            {
                // SelectAction doesn't allow showCard actions
                if (selectAction is AdaptiveShowCardAction)
                {
                    context.Warnings.Add(new AdaptiveWarning(-1, "Inline ShowCard not supported for SelectAction"));
                    return;
                }

                tag.AddClass("ac-selectable");
                AddActionAttributes(selectAction, tag, context);
            }
        }

        protected static void AddActions(HtmlTag uiContainer, IList<AdaptiveAction> actions, AdaptiveRenderContext context)
        {
            if (context.Config.SupportsInteractivity && actions != null)
            {
                var uiButtonStrip = new DivTag()
                    .AddClass("ac-actionset")
                    .Style("display", "flex");
                var actionsConfig = context.Config.Actions;

                // TODO: This top marging is currently being double applied, will have to investigate later
                //.Style("margin-top", $"{context.Config.GetSpacing(context.Config.Actions.Spacing)}px");

                // contains ShowCardAction.AdaptiveCard
                var showCards = new List<HtmlTag>();

                if (actionsConfig.ActionsOrientation == ActionsOrientation.Horizontal)
                {
                    uiButtonStrip.Style("flex-direction", "row");

                    switch (actionsConfig.ActionAlignment)
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
                    switch (actionsConfig.ActionAlignment)
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

                // If the number of actions is bigger than maxActions, then log warning for it
                if (actions.Count > actionsConfig.MaxActions)
                {
                    context.Warnings.Add(new AdaptiveWarning((int)AdaptiveWarning.WarningStatusCode.MaxActionsExceeded,
                        "Some actions were not rendered due to exceeding the maximum number of actions allowed"));
                }

                var maxActions = Math.Min(actionsConfig.MaxActions, actions.Count);
                // See if all actions have icons, otherwise force the icon placement to the left
                var oldConfigIconPlacement = actionsConfig.IconPlacement;
                bool allActionsHaveIcons = true;
                for (var i = 0; i < maxActions; i++)
                {
                    if (string.IsNullOrEmpty(actions[i].IconUrl))
                    {
                        allActionsHaveIcons = false;
                        break;
                    }
                }

                if (!allActionsHaveIcons)
                {
                    actionsConfig.IconPlacement = IconPlacement.LeftOfTitle;
                }

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
                                    .Style("margin-top", $"{actionsConfig.ShowCard.InlineTopMargin}px");

                                showCards.Add(uiCard);
                            }
                        }
                        uiButtonStrip.Children.Add(uiAction);
                    }

                    // add spacer between buttons according to config
                    if (i < maxActions - 1 && actionsConfig.ButtonSpacing > 0)
                    {
                        var uiSpacer = new DivTag();

                        if (actionsConfig.ActionsOrientation == ActionsOrientation.Horizontal)
                        {
                            uiSpacer.Style("flex", "0 0 auto");
                            uiSpacer.Style("width", actionsConfig.ButtonSpacing + "px");
                        }
                        else
                        {
                            uiSpacer.Style("height", actionsConfig.ButtonSpacing + "px");
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

                // Restore the iconPlacement for the context.
                actionsConfig.IconPlacement = oldConfigIconPlacement;
            }
        }

        protected static void AddContainerElements(HtmlTag uiContainer, IList<AdaptiveElement> elements, AdaptiveRenderContext context)
        {
            if (elements != null)
            {
                bool isFirstVisibleElement = true;
                int index = 0;

                foreach (var cardElement in elements)
                {
                    if (index != 0)
                    {
                        // Only the first element can bleed to the top
                        context.RenderArgs.BleedDirection &= ~BleedDirection.BleedUp;
                    }

                    if (index != (elements.Count - 1))
                    {
                        // Only the last element can bleed to the bottom
                        context.RenderArgs.BleedDirection &= ~BleedDirection.BleedDown;
                    }

                    index++;

                    // each element has a row
                    var uiElement = context.Render(cardElement);
                    if (uiElement != null)
                    {
                        HtmlTag uiSeparator = null;

                        if (uiContainer.Children.Any())
                        {
                            uiSeparator = AddSeparator(uiContainer, cardElement, context);
                        }

                        if (cardElement is AdaptiveCollectionElement collectionElement)
                        {
                            if (collectionElement.PixelMinHeight > 0)
                            {
                                uiElement.Style("min-height", collectionElement.PixelMinHeight + "px");
                            }
                        }

                        if (!cardElement.IsVisible)
                        {
                            uiElement.Style("display", "none");

                            if (uiSeparator != null)
                            {
                                uiSeparator.Style("display", "none");
                            }
                        }
                        else
                        {
                            // if it's visible and it's the first element, hide the separator
                            if (isFirstVisibleElement)
                            {
                                if (uiSeparator != null)
                                {
                                    uiSeparator.Style("display", "none");
                                }
                                
                                isFirstVisibleElement = false;
                            }
                        }

                        if (!String.IsNullOrWhiteSpace(cardElement.Id))
                        {
                            uiElement.Attr("name", cardElement.Id);
                        }

                        if (uiSeparator != null)
                        {
                            string separatorId = GenerateRandomId();
                            uiSeparator.Attr("id", separatorId);
                            uiElement.Attr("data-ac-separatorId", separatorId);
                        }

                        uiContainer.Children.Add(uiElement);
                    }
                }
            }
        }

        protected static HtmlTag AddSeparator(HtmlTag uiContainer, AdaptiveElement adaptiveElement, AdaptiveRenderContext context)
        {
            if (!adaptiveElement.Separator && adaptiveElement.Spacing == AdaptiveSpacing.None)
            {
                return null;
            }

            int spacing = context.Config.GetSpacing(adaptiveElement.Spacing);
            var uiSep = new DivTag().AddClass("ac-separator");

            if (adaptiveElement.Separator)
            {
                SeparatorConfig sep = context.Config.Separator;

                uiSep.Style("padding-top", $"{spacing / 2}px")
                     .Style("margin-top", $"{spacing / 2}px")
                     .Style("border-top-color", $"{context.GetRGBColor(sep.LineColor)}")
                     .Style("border-top-width", $"{sep.LineThickness}px")
                     .Style("border-top-style", "solid");
            }
            else
            {
                uiSep.Style("height", $"{spacing}px");
            }

            uiContainer.Children.Add(uiSep);
            return uiSep;
        }

        protected static HtmlTag ColumnRender(AdaptiveColumn column, AdaptiveRenderContext context)
        {
            var uiColumn = new DivTag()
                .AddClass($"ac-{column.Type.Replace(".", "").ToLower()}")
                .Style("display", "flex")
                .Style("flex-direction", "column")
                .Style("min-width", "0px");

            var parentRenderArgs = context.RenderArgs;
            var childRenderArgs = new AdaptiveRenderArgs(parentRenderArgs);

            if (column.PixelMinHeight > 0)
            {
                uiColumn.Style("min-height", column.PixelMinHeight + "px");
            }

            if (!column.IsVisible)
            {
                uiColumn.Style("display", "none");
            }

            if (column.BackgroundImage != null)
            {
                ApplyBackgroundImage(column.BackgroundImage, uiColumn, context);
            }

            bool inheritsStyleFromParent = !column.Style.HasValue;
            bool hasPadding = false;
            if (!inheritsStyleFromParent)
            {
                hasPadding = ApplyPadding(uiColumn, column, parentRenderArgs, context);

                // Apply background color
                ContainerStyleConfig containerStyle = context.Config.ContainerStyles.GetContainerStyleConfig(column.Style);
                uiColumn.Style("background-color", context.GetRGBColor(containerStyle.BackgroundColor));

                childRenderArgs.ForegroundColors = containerStyle.ForegroundColors;
            }

            switch (column.VerticalContentAlignment)
            {
                case AdaptiveVerticalContentAlignment.Center:
                    uiColumn.Style("justify-content", "center");
                    break;
                case AdaptiveVerticalContentAlignment.Bottom:
                    uiColumn.Style("justify-content", "flex-end");
                    break;
                case AdaptiveVerticalContentAlignment.Top:
                default:
                    uiColumn.Style("justify-content", "flex-start");
                    break;
            }

            // Modify context outer parent style so padding necessity can be determined
            childRenderArgs.ParentStyle = (inheritsStyleFromParent) ? parentRenderArgs.ParentStyle : column.Style.Value;

            // If the column has no padding or has padding and doesn't bleed, then the children can bleed
            // to the side the column would have bled
            if (hasPadding)
            {
                childRenderArgs.BleedDirection = BleedDirection.BleedAll;
            }

            childRenderArgs.HasParentWithPadding = hasPadding;
            context.RenderArgs = childRenderArgs;

            AddContainerElements(uiColumn, column.Items, context);

            AddSelectAction(uiColumn, column.SelectAction, context);

            context.RenderArgs = parentRenderArgs;

            return uiColumn;
        }

        protected static HtmlTag ColumnSetRender(AdaptiveColumnSet columnSet, AdaptiveRenderContext context)
        {
            var uiColumnSet = new DivTag()
                .AddClass($"ac-{columnSet.Type.Replace(".", "").ToLower()}")
                .Style("display", "flex");

            AddSelectAction(uiColumnSet, columnSet.SelectAction, context);

            var parentRenderArgs = context.RenderArgs;
            var childrenRenderArgs = new AdaptiveRenderArgs(parentRenderArgs);

            bool inheritsStyleFromParent = !columnSet.Style.HasValue;
            bool hasPadding = false;
            if (!inheritsStyleFromParent)
            {
                hasPadding = ApplyPadding(uiColumnSet, columnSet, parentRenderArgs, context);
                // Apply background color
                var columnSetStyle = context.Config.ContainerStyles.GetContainerStyleConfig(columnSet.Style);
                uiColumnSet.Style("background-color", context.GetRGBColor(columnSetStyle.BackgroundColor));
                childrenRenderArgs.ForegroundColors = columnSetStyle.ForegroundColors;
            }

            // Modify context outer parent style so padding necessity can be determined
            childrenRenderArgs.ParentStyle = (inheritsStyleFromParent) ? parentRenderArgs.ParentStyle : columnSet.Style.Value;

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

            bool isFirstVisibleColumn = true;
            for (int i = 0; i < columnSet.Columns.Count; ++i)
            {
                var column = columnSet.Columns[i];

                var childRenderArgs = new AdaptiveRenderArgs(childrenRenderArgs);
                // Reset up and down bleed for columns as that behaviour shouldn't be changed
                childRenderArgs.BleedDirection |= (BleedDirection.BleedUp | BleedDirection.BleedDown);

                if (i != 0)
                {
                    // Only the first column can bleed to the left
                    childRenderArgs.BleedDirection &= ~BleedDirection.BleedLeft;
                }

                if (i != columnSet.Columns.Count - 1)
                {
                    // Only the last column can bleed to the right
                    childRenderArgs.BleedDirection &= ~BleedDirection.BleedRight;
                }
                context.RenderArgs = childRenderArgs;

                var uiColumn = context.Render(column);

                HtmlTag separator = null;
                // Add horizontal Seperator
                if (uiColumnSet.Children.Any() && (column.Separator || column.Spacing != AdaptiveSpacing.None))
                {
                    SeparatorConfig sep = context.Config.Separator;

                    int spacing = context.Config.GetSpacing(column.Spacing) / 2;
                    int lineThickness = column.Separator ? sep.LineThickness : 0;

                    separator = new DivTag()
                        .AddClass($"ac-columnseparator")
                        .Style("flex", "0 0 auto")
                        .Style("padding-left", $"{spacing}px")
                        .Style("margin-left", $"{spacing}px")
                        .Style("border-left-style", $"solid");

                    // This are the only two properties for separator
                    if (sep != null)
                    {
                        separator.Style("border-left-color", $"{context.GetRGBColor(sep.LineColor)}")
                                 .Style("border-left-width", $"{lineThickness}px");
                    }

                    uiColumnSet.Children.Add(separator);
                }

                if (column.IsVisible && isFirstVisibleColumn)
                {
                    if (separator != null)
                    {
                        separator.Style("display", "none");
                    }
                    isFirstVisibleColumn = false;
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
                    if (double.TryParse(width, out double val) && val >= 0)
                    {
                        var percent = Convert.ToInt32(100 * (val / max));
                        uiColumn = uiColumn.Style("flex", $"1 1 {percent}%");
                    }
                    else if (width.EndsWith("px") && double.TryParse(width.Substring(0, width.Length - 2), out double pxVal) && pxVal >= 0)
                    {
                        uiColumn = uiColumn.Style("flex", $"0 0 {(int)pxVal}px");
                    }
                    else
                    {
                        uiColumn = uiColumn.Style("flex", "0 0 auto");
                    }
                }

                if (!column.IsVisible)
                {
                    uiColumn.Style("display", "none");

                    if (separator != null)
                    {
                        separator.Style("display", "none");
                    }
                }

                if (!String.IsNullOrEmpty(column.Id))
                {
                    uiColumn.Attr("name", column.Id);
                }

                if (separator != null)
                {
                    string separatorId = GenerateRandomId();
                    separator.Attr("id", separatorId);
                    uiColumn.Attr("data-ac-separatorId", separatorId);
                }

                uiColumnSet.Children.Add(uiColumn);
            }

            context.RenderArgs = parentRenderArgs;

            return uiColumnSet;
        }

        protected static HtmlTag ContainerRender(AdaptiveContainer container, AdaptiveRenderContext context)
        {
            var uiContainer = new DivTag()
                .AddClass($"ac-{container.Type.Replace(".", "").ToLower()}");

            if (container.BackgroundImage != null)
            {
                ApplyBackgroundImage(container.BackgroundImage, uiContainer, context);
            }

            if (container.Height == AdaptiveHeight.Stretch)
            {
                uiContainer.Style("display", "flex")
                .Style("flex-direction", "column")
                .Style("flex", "1 1 100%");
            }

            // Keep track of ContainerStyle.ForegroundColors before Container is rendered
            var parentRenderArgs = context.RenderArgs;
            var childRenderArgs = new AdaptiveRenderArgs(parentRenderArgs);

            bool inheritsStyleFromParent = !container.Style.HasValue;
            bool hasPadding = false;
            if (!inheritsStyleFromParent)
            {
                hasPadding = ApplyPadding(uiContainer, container, parentRenderArgs, context);
                // Apply background color
                ContainerStyleConfig containerStyle = context.Config.ContainerStyles.GetContainerStyleConfig(container.Style);
                uiContainer.Style("background-color", context.GetRGBColor(containerStyle.BackgroundColor));

                childRenderArgs.ForegroundColors = containerStyle.ForegroundColors;
            }

            if (hasPadding)
            {
                childRenderArgs.BleedDirection = BleedDirection.BleedAll;
            }

            childRenderArgs.HasParentWithPadding = (hasPadding || parentRenderArgs.HasParentWithPadding);

            switch (container.VerticalContentAlignment)
            {
                case AdaptiveVerticalContentAlignment.Center:
                    uiContainer.Style("justify-content", "center");
                    break;
                case AdaptiveVerticalContentAlignment.Bottom:
                    uiContainer.Style("justify-content", "flex-end");
                    break;
                case AdaptiveVerticalContentAlignment.Top:
                default:
                    uiContainer.Style("justify-content", "flex-start");
                    break;
            }

            // Modify context outer parent style so padding necessity can be determined
            childRenderArgs.ParentStyle = (inheritsStyleFromParent) ? parentRenderArgs.ParentStyle : container.Style.Value;
            context.RenderArgs = childRenderArgs;

            AddContainerElements(uiContainer, container.Items, context);

            AddSelectAction(uiContainer, container.SelectAction, context);

            // Revert context's value to that of outside the Container
            context.RenderArgs = parentRenderArgs;

            return uiContainer;
        }

        protected static HtmlTag FactSetRender(AdaptiveFactSet factSet, AdaptiveRenderContext context)
        {
            var uiFactSet = (TableTag)new TableTag()
                .AddClass($"ac-{factSet.Type.Replace(".", "").ToLower()}")
                .Attr("name", factSet.Id)
                .Style("overflow", "hidden");

            if (factSet.Height == AdaptiveHeight.Stretch)
            {
                uiFactSet.Style("display", "block")
                    .Style("flex", "1 1 100%");
            }

            foreach (var fact in factSet.Facts)
            {
                AdaptiveTextBlock factTitle = new AdaptiveTextBlock()
                {
                    Text = fact.Title,
                    Size = context.Config.FactSet.Title.Size,
                    Color = context.Config.FactSet.Title.Color,
                    Weight = context.Config.FactSet.Title.Weight,
                    IsSubtle = context.Config.FactSet.Title.IsSubtle,
                    Wrap = context.Config.FactSet.Title.Wrap,
                    MaxWidth = context.Config.FactSet.Title.MaxWidth
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
                    Wrap = context.Config.FactSet.Value.Wrap,
                    // MaxWidth is not supported on the Value of FactSet. Do not set it.
                };
                var uiValue = context.Render(factValue)
                    .AddClass("ac-factvalue");

                // create row in factset
                var uiRow = uiFactSet
                    .AddBodyRow();
                uiRow.Style("height", "1px");

                // add elements as cells
                uiRow.AddCell().AddClass("ac-factset-titlecell").Style("height", "inherit")
                    .Style("max-width", $"{context.Config.FactSet.Title.MaxWidth}px")
                    .Append(uiTitle);
                uiRow.AddCell().AddClass("ac-factset-valuecell").Style("height", "inherit").Append(uiValue);
            }
            return uiFactSet;
        }

        protected static HtmlTag TextBlockRender(AdaptiveTextBlock textBlock, AdaptiveRenderContext context)
        {
            string fontFamily = context.Config.GetFontFamily(textBlock.FontType);
            int fontSize = context.Config.GetFontSize(textBlock.FontType, textBlock.Size);
            int weight = context.Config.GetFontWeight(textBlock.FontType, textBlock.Weight);

            // Not sure where this magic value comes from?
            var lineHeight = fontSize * 1.33;

            var uiTextBlock = new HtmlTag("div", false)
                .AddClass($"ac-{textBlock.Type.Replace(".", "").ToLower()}")
                .Attr("name", textBlock.Id)
                .Style("box-sizing", "border-box")
                .Style("text-align", textBlock.HorizontalAlignment.ToString().ToLower())
                .Style("color", context.GetColor(textBlock.Color, textBlock.IsSubtle, false))
                .Style("line-height", $"{lineHeight.ToString("F")}px")
                .Style("font-size", $"{fontSize}px")
                .Style("font-weight", $"{weight}");

            if (textBlock.Height == AdaptiveHeight.Stretch)
            {
                uiTextBlock.Style("flex", "1 1 100%");
            }

            if (textBlock.Italic)
            {
                uiTextBlock.Style("font-style", "italic");
            }

            if (textBlock.Strikethrough)
            {
                uiTextBlock.Style("text-decoration", "line-through");
            }

            if (textBlock.MaxLines > 0)
                uiTextBlock = uiTextBlock
                    .Style("max-height", $"{lineHeight * textBlock.MaxLines}px")
                    .Style("overflow", "hidden");

            uiTextBlock = textBlock.Wrap ?
                uiTextBlock.Style("word-wrap", "break-word") :
                uiTextBlock.Style("white-space", "nowrap");

            var textTags = MarkdownToHtmlTagConverter.Convert(RendererUtilities.ApplyTextFunctions(textBlock.Text, context.Lang));
            uiTextBlock.Children.AddRange(textTags);

            Action<HtmlTag> setParagraphStyles = null;
            setParagraphStyles = (HtmlTag htmlTag) =>
            {
                if (htmlTag.Element?.ToLowerInvariant() == "p")
                {
                    htmlTag.Style("margin-top", "0px");
                    htmlTag.Style("margin-bottom", "0px");
                    htmlTag.Style("width", "100%");

                    if (!string.IsNullOrEmpty(fontFamily))
                    {
                        htmlTag.Style("font-family", fontFamily);
                    }

                    if (!textBlock.Wrap)
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

        protected static HtmlTag RichTextBlockRender(AdaptiveRichTextBlock richTextBlock, AdaptiveRenderContext context)
        {
            var uiTextBlock = new HtmlTag("div", false)
                .AddClass($"ac-{richTextBlock.Type.Replace(".", "").ToLower()}")
                .Attr("name", richTextBlock.Id)
                .Style("box-sizing", "border-box")
                .Style("text-align", richTextBlock.HorizontalAlignment.ToString().ToLower());

            if (richTextBlock.Height == AdaptiveHeight.Stretch)
            {
                uiTextBlock.Style("flex", "1 1 100%");
            }

            uiTextBlock = uiTextBlock.Style("word-wrap", "break-word");

            var uiParagraph = new HtmlTag("p");
            foreach (var inlineRun in richTextBlock.Inlines)
            {
                AdaptiveTextRun textRun = inlineRun as AdaptiveTextRun;

                var uiInlineRun = TextRunRender(textRun, context);
                uiParagraph.Children.Add(uiInlineRun);
            }
            uiTextBlock.Children.Add(uiParagraph);

            Action<HtmlTag> setParagraphStyles = null;
            setParagraphStyles = (HtmlTag htmlTag) =>
            {
                if (htmlTag.Element?.ToLowerInvariant() == "p")
                {
                    htmlTag.Style("margin-top", "0px");
                    htmlTag.Style("margin-bottom", "0px");
                    htmlTag.Style("width", "100%");
                }

                foreach (var child in htmlTag.Children)
                {
                    setParagraphStyles(child);
                }
            };

            setParagraphStyles(uiTextBlock);

            return uiTextBlock;
        }

        protected static HtmlTag TextRunRender(AdaptiveTextRun textRun, AdaptiveRenderContext context)
        {
            string fontFamily = context.Config.GetFontFamily(textRun.FontType);
            int fontSize = context.Config.GetFontSize(textRun.FontType, textRun.Size);
            int weight = context.Config.GetFontWeight(textRun.FontType, textRun.Weight);

            // Not sure where this magic value comes from?
            var lineHeight = fontSize * 1.33;

            var uiTextRun = new HtmlTag("span", true)
                .AddClass($"ac-{textRun.Type.Replace(".", "").ToLower()}")
                .Style("color", context.GetColor(textRun.Color, textRun.IsSubtle, false))
                .Style("line-height", $"{lineHeight.ToString("F")}px")
                .Style("font-size", $"{fontSize}px")
                .Style("font-weight", $"{weight}");

            uiTextRun.Text = RendererUtilities.ApplyTextFunctions(textRun.Text, context.Lang);

            if (textRun.Italic)
            {
                uiTextRun.Style("font-style", "italic");
            }

            if (textRun.Strikethrough && textRun.Underline)
            {
                uiTextRun.Style("text-decoration", "line-through underline");
            }
            else if (textRun.Strikethrough)
            {
                uiTextRun.Style("text-decoration", "line-through");
            }
            else if (textRun.Underline)
            {
                uiTextRun.Style("text-decoration", "underline");
            }

            if (textRun.Highlight)
            {
                uiTextRun.Style("background-color", context.GetColor(textRun.Color, textRun.IsSubtle, true));
            }

            return uiTextRun;
        }

        protected static HtmlTag ImageRender(AdaptiveImage image, AdaptiveRenderContext context)
        {
            var uiDiv = new DivTag()
                .AddClass($"ac-{image.Type.Replace(".", "").ToLower()}")
                .Attr("name", image.Id)
                .Style("display", "block");

            if (image.Height != AdaptiveHeight.Stretch)
            {
                uiDiv.Style("box-sizing", "border-box");
            }
            else
            {
                uiDiv.Style("align-items", "flex-start")
                    .Style("flex", "1 1 100%");
            }

            // if explicit image size is not used, use Adaptive Image size
            if (image.PixelWidth == 0 && image.PixelHeight == 0)
            {
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
            }

            var uiImage = new HtmlTag("img")
                .Attr("alt", image.AltText ?? "card image")
                .Attr("src", context.Config.ResolveFinalAbsoluteUri(image.Url));

            // if explicit image size is used
            if (image.PixelWidth != 0 || image.PixelHeight != 0)
            {
                if (image.PixelWidth != 0)
                {
                    uiImage = uiImage.Attr("width", $"{image.PixelWidth}px");
                }
                if (image.PixelHeight != 0)
                {
                    uiImage = uiImage.Attr("height", $"{image.PixelHeight}px");
                }
                uiImage = uiImage.Attr("object-fit", "fill");
            }
            else
            {
                uiImage.Style("width", "100%");
            }

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
                    uiDiv = uiDiv.Style("overflow", "hidden");
                    break;
                case AdaptiveHorizontalAlignment.Center:
                    uiDiv = uiDiv.Style("overflow", "hidden")
                        .Style("margin-right", "auto")
                        .Style("margin-left", "auto");
                    break;
                case AdaptiveHorizontalAlignment.Right:
                    uiDiv = uiDiv.Style("overflow", "hidden")
                        .Style("margin-left", "auto");
                    break;
            }

            if (!string.IsNullOrEmpty(image.BackgroundColor))
            {
                uiImage.Style("background-color", context.GetRGBColor(image.BackgroundColor));
            }

            uiDiv.Children.Add(uiImage);

            AddSelectAction(uiDiv, image.SelectAction, context);
            return uiDiv;
        }

        private static List<string> _supportedMimeTypes = new List<string>
        {
            "video/mp4",
            "audio/mp4",
            "audio/mpeg"
        };

        private static List<string> _supportedAudioMimeTypes = new List<string>
        {
            "audio/mp4",
            "audio/mpeg"
        };

        /** Get the first media URI with a supported mime type */
        private static List<AdaptiveMediaSource> GetMediaSources(AdaptiveMedia media, AdaptiveRenderContext context)
        {
            // Check if sources contain an invalid mix of MIME types (audio and video)
            bool? isLastMediaSourceAudio = null;
            foreach (var source in media.Sources)
            {
                if (!isLastMediaSourceAudio.HasValue)
                {
                    isLastMediaSourceAudio = IsAudio(source);
                }
                else
                {
                    if (IsAudio(source) != isLastMediaSourceAudio.Value)
                    {
                        // If there is one pair of sources with different MIME types,
                        // it's an invalid mix and a warning should be logged
                        context.Warnings.Add(new AdaptiveWarning(-1, "A Media element contains an invalid mix of MIME type"));
                        return null;
                    }

                    isLastMediaSourceAudio = IsAudio(source);
                }
            }

            // Return the list of all supported sources with not-null URI
            List<AdaptiveMediaSource> validSources = new List<AdaptiveMediaSource>();
            foreach (var source in media.Sources)
            {
                if (_supportedMimeTypes.Contains(source.MimeType))
                {
                    Uri finalMediaUri = context.Config.ResolveFinalAbsoluteUri(source.Url);
                    if (finalMediaUri != null)
                    {
                        validSources.Add(source);
                    }
                }
            }

            return validSources;
        }

        private static bool IsAudio(AdaptiveMediaSource mediaSource)
        {
            return _supportedAudioMimeTypes.Contains(mediaSource.MimeType);
        }

        protected static HtmlTag MediaRender(AdaptiveMedia media, AdaptiveRenderContext context)
        {
            List<AdaptiveMediaSource> mediaSources = GetMediaSources(media, context);

            // No valid source is found
            if (mediaSources.Count == 0)
            {
                context.Warnings.Add(new AdaptiveWarning(-1, "A Media element does not have any valid source"));
                return null;
            }

            var uiMedia = new DivTag()
                .Style("width", "100%")
                .Attr("alt", media.AltText ?? "card media");

            string posterUrl = null;
            if (!string.IsNullOrEmpty(media.Poster) && context.Config.ResolveFinalAbsoluteUri(media.Poster) != null)
            {
                posterUrl = context.Config.ResolveFinalAbsoluteUri(media.Poster).ToString();
            }
            else if (!string.IsNullOrEmpty(context.Config.Media.DefaultPoster)
                 && context.Config.ResolveFinalAbsoluteUri(context.Config.Media.DefaultPoster) != null)
            {
                // Use the default poster from host
                posterUrl = context.Config.ResolveFinalAbsoluteUri(context.Config.Media.DefaultPoster).ToString();
            }

            var thumbnailImage = new HtmlTag("image", false)
                .Attr("src", posterUrl)
                .Style("width", "100%")
                .Style("height", "100%");

            // If host does not support interactivity, simply return the
            // poster image if present
            if (!context.Config.SupportsInteractivity)
            {
                uiMedia.Children.Add(thumbnailImage);

                return uiMedia;
            }

            #region Thumbnail

            var thumbnailButton = new DivTag()
                .AddClass("ac-media-poster")
                .Attr("role", "button")
                .Attr("tabindex", "0")
                .Attr("aria-label", "Play media")
                .Attr("role", "contentinfo")
                .Style("position", "relative")
                .Style("display", "flex")
                .Style("cursor", "pointer");

            if (posterUrl != null)
            {
                thumbnailButton.Children.Add(thumbnailImage);
            }
            else
            {
                thumbnailButton.AddClass("empty")
                    .Style("height", "200px")
                    .Style("minHeight", "150px")
                    .Style("background-color", "#F2F2F2");
            }

            #region Play button

            // Overlay on top of poster image
            var playButtonContainer = new DivTag()
                .Style("position", "absolute")
                .Style("left", "0")
                .Style("top", "0")
                .Style("width", "100%")
                .Style("height", "100%")
                .Style("display", "flex")
                .Style("justify-content", "center")
                .Style("align-items", "center");

            // If host specifies a play button URL,
            // render that image as the play button
            if (!string.IsNullOrEmpty(context.Config.Media.PlayButton)
                && context.Config.ResolveFinalAbsoluteUri(context.Config.Media.PlayButton) != null)
            {
                var playButtonImage = new HtmlTag("img")
                    .Attr("src", context.Config.ResolveFinalAbsoluteUri(context.Config.Media.PlayButton).ToString())
                    .Style("width", "56px")
                    .Style("height", "56px");

                playButtonContainer.Children.Add(playButtonImage);
            }
            else
            {
                int playButtonArrowWidth = 12;
                int playButtonArrowHeight = 15;

                // Play symbol (black arrow)
                var playButtonInnerElement = new DivTag()
                    .Style("width", playButtonArrowWidth + "px")
                    .Style("height", playButtonArrowHeight + "px")
                    .Style("color", "black")
                    .Style("border-top-width", (playButtonArrowHeight / 2) + "px")
                    .Style("border-bottom-width", (playButtonArrowHeight / 2) + "px")
                    .Style("border-left-width", playButtonArrowWidth + "px")
                    .Style("border-right-width", "0")
                    .Style("border-style", "solid")
                    .Style("border-top-color", "transparent")
                    .Style("border-right-color", "transparent")
                    .Style("border-bottom-color", "transparent");

                // Circle around play symbol
                var playButtonOuterElement = new DivTag()
                    .Style("display", "flex")
                    .Style("align-items", "center")
                    .Style("justify-content", "center")
                    .Style("width", "56px")
                    .Style("height", "56px")
                    .Style("border", "1px solid #EEEEEE")
                    .Style("border-radius", "28px")
                    .Style("box-shadow", "0px 0px 10px #EEEEEE")
                    .Style("background-color", "rgba(255, 255, 255, 0.9)")
                    .Style("color", "black");

                playButtonOuterElement.Children.Add(playButtonInnerElement);

                playButtonContainer.Children.Add(playButtonOuterElement);
            }

            #endregion

            thumbnailButton.Children.Add(playButtonContainer);

            #endregion

            uiMedia.Children.Add(thumbnailButton);

            if (context.Config.Media.AllowInlinePlayback)
            {
                // Media player is only created if inline playback is allowed

                // A unique ID to link the thumbnail button and the media player
                // of the same Media element
                string mediaId = GenerateRandomId();

                thumbnailButton.Attr("data-ac-mediaId", mediaId);

                #region Media Player

                bool isAudio = IsAudio(mediaSources[0]);

                var uiMediaPlayerContainer = new DivTag()
                    .Attr("id", mediaId)
                    .Style("width", "100%")
                    .Style("height", "100%")
                    .Style("display", "none");

                // If an audio has a poster, display the static poster image
                // along with the media player
                if (isAudio && posterUrl != null)
                {
                    var staticPosterImage = new HtmlTag("image", false)
                        .Attr("src", posterUrl)
                        .Style("width", "100%")
                        .Style("height", "100%");

                    uiMediaPlayerContainer.Children.Add(staticPosterImage);
                }

                var uiMediaPlayer = new HtmlTag(isAudio ? "audio" : "video")
                    .Attr("id", mediaId + "-player")
                    .Style("width", "100%")
                    .Attr("controls", "")
                    .Attr("preload", "none")
                    .Attr("poster", posterUrl);

                // Sources
                foreach (var source in mediaSources)
                {
                    var uiSource = new HtmlTag("source")
                        .Attr("src", context.Config.ResolveFinalAbsoluteUri(source.Url))
                        .Attr("type", source.MimeType);

                    uiMediaPlayer.Children.Add(uiSource);
                }

                uiMediaPlayerContainer.Children.Add(uiMediaPlayer);

                #endregion

                uiMedia.Children.Add(uiMediaPlayerContainer);
            }
            else
            {
                // Attach media data to the thumbnail to be sent to host
                thumbnailButton.Attr("data-ac-media-sources", JsonConvert.SerializeObject(media.Sources, Formatting.None));
            }

            return uiMedia;
        }

        protected static HtmlTag ImageSetRender(AdaptiveImageSet imageSet, AdaptiveRenderContext context)
        {
            var uiImageSet = new DivTag()
                .Attr("name", imageSet.Id)
                .AddClass(imageSet.Type.ToLower());

            if (imageSet.Height == AdaptiveHeight.Stretch)
            {
                uiImageSet.Style("display", "flex")
                    .Style("flex", "1 1 100%");
            }

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

        protected static HtmlTag ActionSetRender(AdaptiveActionSet actionSet, AdaptiveRenderContext context)
        {
            var outerContainer = new DivTag()
                .Style("box-sizing", "border-box")
                .Style("width", "100%");
            AddActions(outerContainer, actionSet.Actions, context);
            return outerContainer;
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

                    if (adaptiveChoiceSetInput.Height == AdaptiveHeight.Stretch)
                    {
                        uiSelectElement.Style("flex", "1 1 100%");
                    }

                    var defaultValues = ParseChoiceSetInputDefaultValues(adaptiveChoiceSetInput.Value);

                    // If more than one option is specified, default to not select any option
                    if (defaultValues.Count > 1)
                    {
                        var option = new HtmlTag("option") { Text = "" }
                            .Attr("disabled", string.Empty)
                            .Attr("hidden", string.Empty)
                            .Attr("selected", string.Empty);
                        uiSelectElement.Append(option);
                    }

                    foreach (var choice in adaptiveChoiceSetInput.Choices)
                    {
                        var option = new HtmlTag("option") { Text = choice.Title }
                            .Attr("value", choice.Value);

                        // Select an option only when one option is specified
                        if (defaultValues.Contains(choice.Value) && defaultValues.Count == 1)
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
            var defaultValues = ParseChoiceSetInputDefaultValues(adaptiveChoiceSetInput.Value);

            // render as a series of radio buttons
            var uiElement = new DivTag()
                .AddClass("ac-input")
                .Style("width", "100%")
                .Style("flex", "1 1 100%")
                .Attr("name", adaptiveChoiceSetInput.Id);

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

                // Only select an option if isMultiSelect is true (checkboxes)
                // or there is only one specified value
                if (defaultValues.Contains(choice.Value) && (adaptiveChoiceSetInput.IsMultiSelect || defaultValues.Count == 1))
                {
                    uiInput.Attr("checked", string.Empty);
                }

                var uiLabel = CreateLabel(htmlLabelId, choice.Title, context);

                var compoundInputElement = new DivTag()
                    .Append(uiInput)
                    .Append(uiLabel);

                // text-overflow ellipsis does not work when width is not specified in px
                // when specified relatively such as using %, ellipsis does not work
                if (!adaptiveChoiceSetInput.Wrap)
                {
                    compoundInputElement.Style("white-space", "nowrap");
                    compoundInputElement.Style("overflow", "hidden");
                }

                uiElement.Append(compoundInputElement);
            }

            return uiElement;

        }

        // Default values are specified by a comma separated string
        private static List<string> ParseChoiceSetInputDefaultValues(string value)
        {
            return value?.Split(',').Select(p => p.Trim()).Where(s => !string.IsNullOrEmpty(s)).ToList() ?? new List<string>();
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
// Ignore deprecation warning for FontSizes
#pragma warning disable 0618
            tag.Style("color", context.GetColor(AdaptiveTextColor.Default, false, false))
                .Style("font-size", $"{context.Config.FontSizes.Default}px")
                .Style("display", "inline-block")
                .Style("margin-left", "6px")
                .Style("vertical-align", "middle");
#pragma warning restore 0618
        }

        protected static HtmlTag DateInputRender(AdaptiveDateInput input, AdaptiveRenderContext context)
        {
            var uiDateInput = new HtmlTag("input")
                .Attr("name", input.Id)
                .Attr("type", "date")
                .AddClass("ac-input")
                .AddClass("ac-dateInput")
                .Style("width", "100%")
                .Attr("aria-label", (input.Placeholder ?? "Select date") + " in mm/dd/yyyy format");

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

            if (input.Height == AdaptiveHeight.Stretch)
            {
                uiDateInput.Style("flex", "1 1 100%");
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

            if (input.Height == AdaptiveHeight.Stretch)
            {
                uiNumberInput.Style("flex", "1 1 100%");
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
                .AddClass("ac-input");

            if (input.InlineAction != null)
            {
                uiTextInput.Style("width", "100%");
            }
            else
            {
                if (!input.IsMultiline)
                {
                    uiTextInput.Style("flex", "1 1 auto");
                }
            }

            if (!string.IsNullOrEmpty(input.Placeholder))
            {
                uiTextInput.Attr("placeholder", input.Placeholder);
            }

            if (input.MaxLength > 0)
            {
                uiTextInput.Attr("maxLength", input.MaxLength.ToString());
            }

            if (input.Height == AdaptiveHeight.Stretch)
            {
                uiTextInput.Style("flex", "1 1 100%");
            }

            if (context.Config.SupportsInteractivity && input.InlineAction != null)
            {
                // ShowCard Inline Action Mode is not supported
                if (input.InlineAction.Type == AdaptiveShowCardAction.TypeName &&
                     context.Config.Actions.ShowCard.ActionMode == ShowCardActionMode.Inline)
                {
                    context.Warnings.Add(new AdaptiveWarning(-1, "Inline ShowCard not supported for InlineAction"));
                }
                else
                {
                    var textInputWithInlineActionId = GenerateRandomId();
                    var uiContainer = new DivTag()
                        .AddClass("ac-textinput-inlineaction")
                        .Attr("data-ac-textinput-id", textInputWithInlineActionId)
                        .Style("overflow", "hidden")
                        .Style("display", "flex")
                        .Attr("name", input.Id);

                    if(input.Height == AdaptiveHeight.Stretch)
                    {
                        uiContainer.Style("flex", "1 1 100%");
                    }

                    uiTextInput.Attr("id", textInputWithInlineActionId);

                    uiContainer.Children.Add(uiTextInput);

                    var actionsConfig = context.Config.Actions;

                    var buttonElement = new HtmlTag("button", false)
                        .Attr("type", "button")
                        .Style("overflow", "hidden")
                        .Style("white-space", "nowrap")
                        .Style("text-overflow", "ellipsis")
                        .Style("flex", "0 1 auto")
                        .Style("display", "flex")
                        .Style("align-items", "center")
                        .Style("justify-content", "center");

                    if (input.InlineAction.IconUrl != null)
                    {
                        // Append the icon to the button
                        // NOTE: always using icon size since it's difficult
                        // to match icon's height with text's height
                        var iconElement = new HtmlTag("image", false)
                            .Attr("src", input.InlineAction.IconUrl)
                            .Style("max-height", $"{actionsConfig.IconSize}px");

                        buttonElement.Append(iconElement);
                    }
                    else
                    {
                        var titleElement = new HtmlTag("div", false) { Text = input.InlineAction.Title };
                        buttonElement.Append(titleElement);
                    }

                    AddInlineActionAttributes(input.InlineAction, buttonElement, context);
                    string inlineActionId = GenerateRandomId();
                    uiContainer.Attr("data-ac-inlineaction-id", inlineActionId);
                    buttonElement.Attr("id", inlineActionId);
                    uiContainer.Children.Add(buttonElement);

                    return uiContainer;
                }
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

            if (input.Height == AdaptiveHeight.Stretch)
            {
                uiTimeInput.Style("flex", "1 1 100%");
            }

            return uiTimeInput;
        }

        protected static HtmlTag ToggleInputRender(AdaptiveToggleInput toggleInput, AdaptiveRenderContext context)
        {
            var htmlLabelId = GenerateRandomId();

            var uiElement = new DivTag()
                .AddClass("ac-input")
                .Style("width", "100%")
                .Attr("name", toggleInput.Id);

            if (toggleInput.Height == AdaptiveHeight.Stretch)
            {
                uiElement.Style("flex", "1 1 100%");
            }

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

            uiElement.Append(uiCheckboxInput).Append(uiLabel);

            if (!toggleInput.Wrap)
            {
                uiElement.Style("white-space", "nowrap");
                uiElement.Style("overflow", "hidden");
            }

            return uiElement;
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

        private static void ApplyBackgroundImage(AdaptiveBackgroundImage backgroundImage, HtmlTag uiContainer, AdaptiveRenderContext context)
        {
            switch (backgroundImage.FillMode)
            {
                case AdaptiveImageFillMode.Repeat:
                    uiContainer.Style("background-image", $"url('{context.Config.ResolveFinalAbsoluteUri(backgroundImage.Url)}')")
                            .Style("background-repeat", "repeat");
                    break;
                case AdaptiveImageFillMode.RepeatHorizontally:
                    uiContainer.Style("background-image", $"url('{context.Config.ResolveFinalAbsoluteUri(backgroundImage.Url)}')")
                            .Style("background-repeat", "repeat-x")
                            .Style("background-position", "left " + backgroundImage.VerticalAlignment.ToString());
                    break;
                case AdaptiveImageFillMode.RepeatVertically:
                    uiContainer.Style("background-image", $"url('{context.Config.ResolveFinalAbsoluteUri(backgroundImage.Url)}')")
                            .Style("background-repeat", "repeat-y")
                            .Style("background-position", backgroundImage.HorizontalAlignment.ToString() + " top");
                    break;
                case AdaptiveImageFillMode.Cover:
                default:
                    uiContainer.Style("background-image", $"url('{context.Config.ResolveFinalAbsoluteUri(backgroundImage.Url)}')")
                            .Style("background-repeat", "no-repeat")
                            .Style("background-size", "cover")
                            .Style("background-position", backgroundImage.HorizontalAlignment.ToString().ToLower() + " " + backgroundImage.VerticalAlignment.ToString().ToLower());
                    break;
            }
        }

        private static bool ApplyPadding(HtmlTag uiElement, AdaptiveCollectionElement element, AdaptiveRenderArgs parentRenderArgs, AdaptiveRenderContext context)
        {
            bool canApplyPadding = false;

            // AdaptiveColumn inherits from AdaptiveContainer so only one check is required for both
            if (element is AdaptiveContainer container)
            {
                canApplyPadding = ((container.BackgroundImage != null) || (container.Style.HasValue && (container.Style != parentRenderArgs.ParentStyle)));
            }
            else if (element is AdaptiveColumnSet columnSet)
            {
                canApplyPadding = (columnSet.Style.HasValue && (columnSet.Style != parentRenderArgs.ParentStyle));
            }

            if (canApplyPadding)
            {
                int padding = context.Config.Spacing.Padding;
                uiElement.Style("padding-right", padding + "px")
                    .Style("padding-left", padding + "px")
                    .Style("padding-top", padding + "px")
                    .Style("padding-bottom", padding + "px");

                if (element.Bleed)
                {
                    int leftMargin = 0, rightMargin = 0, topMargin = 0, bottomMargin = 0;
                    if ((parentRenderArgs.BleedDirection & BleedDirection.BleedLeft) != BleedDirection.BleedNone)
                    {
                        leftMargin = -padding;
                    }

                    if ((parentRenderArgs.BleedDirection & BleedDirection.BleedRight) != BleedDirection.BleedNone)
                    {
                        rightMargin = -padding;
                    }

                    if ((parentRenderArgs.BleedDirection & BleedDirection.BleedUp) != BleedDirection.BleedNone)
                    {
                        topMargin = -padding;
                    }

                    if ((parentRenderArgs.BleedDirection & BleedDirection.BleedDown) != BleedDirection.BleedNone)
                    {
                        bottomMargin = -padding;
                    }

                    uiElement.Style("margin-right", rightMargin + "px")
                                .Style("margin-left", leftMargin + "px")
                                .Style("margin-top", topMargin + "px")
                                .Style("margin-bottom", bottomMargin + "px");
                }
            }

            return canApplyPadding;
        }
    }
}
