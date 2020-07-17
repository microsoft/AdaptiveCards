// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Media;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveContainerRenderer
    {
        public static FrameworkElement Render(AdaptiveContainer container, AdaptiveRenderContext context)
        {
            var uiContainer = new Grid();
            uiContainer.Style = context.GetStyle("Adaptive.Container");
            uiContainer.SetBackgroundSource(container.BackgroundImage, context);

            // Keep track of ContainerStyle.ForegroundColors before Container is rendered
            var parentRenderArgs = context.RenderArgs;
            // This is the renderArgs that will be passed down to the children
            var childRenderArgs = new AdaptiveRenderArgs(parentRenderArgs);

            Grid uiOuterContainer = new Grid();

            uiOuterContainer.Children.Add(uiContainer);
            Border border = new Border();
            border.Child = uiOuterContainer;

            RendererUtil.ApplyVerticalContentAlignment(uiContainer, container);
            uiContainer.MinHeight = container.PixelMinHeight;

            bool inheritsStyleFromParent = !container.Style.HasValue;
            bool hasPadding = false;
            if (!inheritsStyleFromParent)
            {
                hasPadding = ApplyPadding(border, uiOuterContainer, container, parentRenderArgs, context);

                // Apply background color
                ContainerStyleConfig containerStyle = context.Config.ContainerStyles.GetContainerStyleConfig(container.Style);
                border.Background = context.GetColorBrush(containerStyle.BackgroundColor);

                childRenderArgs.ForegroundColors = containerStyle.ForegroundColors;
            }

            switch (container.VerticalContentAlignment)
            {
                case AdaptiveVerticalContentAlignment.Center:
                    uiContainer.VerticalAlignment = VerticalAlignment.Center;
                    break;
                case AdaptiveVerticalContentAlignment.Bottom:
                    uiContainer.VerticalAlignment = VerticalAlignment.Bottom;
                    break;
                case AdaptiveVerticalContentAlignment.Top:
                default:
                    break;
            }

            if (hasPadding)
            {
                childRenderArgs.BleedDirection = BleedDirection.BleedAll;
            }

            // Modify context outer parent style so padding necessity can be determined
            childRenderArgs.ParentStyle = (inheritsStyleFromParent) ? parentRenderArgs.ParentStyle : container.Style.Value;
            childRenderArgs.HasParentWithPadding = (hasPadding || parentRenderArgs.HasParentWithPadding);
            context.RenderArgs = childRenderArgs;

            AddContainerElements(uiContainer, container.Items, context);

            // Revert context's value to that of outside the Container
            context.RenderArgs = parentRenderArgs;

            return RendererUtil.ApplySelectAction(border, container, context);
        }

        public static void AddContainerElements(Grid uiContainer, IList<AdaptiveElement> elements, AdaptiveRenderContext context)
        {
            // Keeping track of the index so we don't have to call IndexOf function on every iteration
            int index = 0;
            foreach (var cardElement in elements)
            {
                if (index != 0)
                {
                    // Only the first element can bleed to the top
                    context.RenderArgs.BleedDirection &= ~BleedDirection.BleedUp;
                }

                if (index != elements.Count - 1)
                {
                    // Only the last element can bleed to the bottom
                    context.RenderArgs.BleedDirection &= ~BleedDirection.BleedDown;
                }

                index++;

                // each element has a row
                AdaptiveTypedElement rendereableElement = context.GetRendereableElement(cardElement);
    
                FrameworkElement uiElement = context.Render(rendereableElement);
                if (uiElement != null)
                {
                    TagContent tag = null;
                    Grid separator = null;
                    if (cardElement.Separator && uiContainer.Children.Count > 0)
                    {
                        separator = AddSeparator(context, cardElement, uiContainer);
                    }
                    else if (uiContainer.Children.Count > 0)
                    {
                        separator = AddSpacing(context, cardElement, uiContainer);
                    }

                    tag = new TagContent(separator, uiContainer);

                    uiElement.Tag = tag;

                    // Sets the minHeight property for Container and ColumnSet
                    if (cardElement.Type == "Container" || cardElement.Type == "ColumnSet")
                    {
                        AdaptiveCollectionElement collectionElement = (AdaptiveCollectionElement)cardElement;
                        uiElement.MinHeight = collectionElement.PixelMinHeight;
                    }

                    // If the rendered element is an input element, then add it to the inputs list
                    if (rendereableElement is AdaptiveInput)
                    {
                        context.AddInputToCard(context.RenderArgs.ContainerCardId, rendereableElement.Id);
                    }

                    int rowDefinitionIndex = uiContainer.RowDefinitions.Count;
                    RowDefinition rowDefinition = null;
                    if (cardElement.Height != AdaptiveHeight.Stretch)
                    {
                        rowDefinition = new RowDefinition() { Height = GridLength.Auto };

                        uiContainer.RowDefinitions.Add(rowDefinition);

                        FrameworkElement enclosingElement = EncloseElementInPanel(context, rendereableElement, uiElement);

                        Grid.SetRow(enclosingElement, rowDefinitionIndex);
                        uiContainer.Children.Add(enclosingElement);

                        // Row definition is stored in the tag for containers and elements that stretch
                        // so when the elements are shown, the row can have it's original definition,
                        // while when the element is hidden, the extra space is not reserved in the layout
                        tag.RowDefinition = rowDefinition;
                        tag.ViewIndex = rowDefinitionIndex;

                        enclosingElement.Tag = tag;
                        enclosingElement.Name = cardElement.Id;

                        RendererUtil.SetVisibility(enclosingElement, cardElement.IsVisible, tag);
                    }
                    else
                    {
                        rowDefinition = new RowDefinition() { Height = new GridLength(1, GridUnitType.Star) };
                        
                        uiContainer.RowDefinitions.Add(rowDefinition);

                        // Row definition is stored in the tag for containers and elements that stretch
                        // so when the elements are shown, the row can have it's original definition,
                        // while when the element is hidden, the extra space is not reserved in the layout
                        tag.RowDefinition = rowDefinition;
                        tag.ViewIndex = rowDefinitionIndex;

                        if (cardElement.Type == "Container")
                        {
                            Grid.SetRow(uiElement, rowDefinitionIndex);
                            uiContainer.Children.Add(uiElement);
                            RendererUtil.SetVisibility(uiElement, cardElement.IsVisible, tag);
                        }
                        else
                        {
                            StackPanel panel = new StackPanel();

                            if (!String.IsNullOrEmpty(cardElement.Id))
                            {
                                panel.Name = cardElement.Id;
                            }

                            if (rendereableElement is AdaptiveInput)
                            {
                                panel.Children.Add(EncloseInputForVisualCue(context, rendereableElement as AdaptiveInput, uiElement));
                            }
                            else
                            {
                                panel.Children.Add(uiElement);
                            }
                            panel.Tag = tag;

                            Grid.SetRow(panel, rowDefinitionIndex);
                            uiContainer.Children.Add(panel);
                            RendererUtil.SetVisibility(panel, cardElement.IsVisible, tag);
                        }
                    }
                }
            }

            context.ResetSeparatorVisibilityInsideContainer(uiContainer);
        }
        
        /// <summary>
        /// Adds spacing as a grid element to the container
        /// </summary>
        /// <param name="context">Context</param>
        /// <param name="element">Element to render spacing for</param>
        /// <param name="uiContainer">Container of rendered elements</param>
        /// <returns>Spacing grid</returns>
        public static Grid AddSpacing(AdaptiveRenderContext context, AdaptiveElement element, Panel uiContainer)
        {
            return AddSpacing(context, element.Spacing, uiContainer);
        }

        public static Grid AddSpacing(AdaptiveRenderContext context, AdaptiveSpacing spacing, Panel uiContainer)
        {
            if (spacing == AdaptiveSpacing.None)
            {
                return null;
            }

            var uiSpa = new Grid();
            uiSpa.Style = context.GetStyle($"Adaptive.Spacing");

            int pixelSpacing = context.Config.GetSpacing(spacing);
            uiSpa.SetHeight(pixelSpacing);

            if (uiContainer is Grid)
            {
                Grid uiContainerGrid = uiContainer as Grid;
                uiContainerGrid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                Grid.SetRow(uiSpa, uiContainerGrid.RowDefinitions.Count - 1);
            }

            uiContainer.Children.Add(uiSpa);

            return uiSpa;
        }

        public static Grid AddSeparator(AdaptiveRenderContext context, AdaptiveElement element, Grid uiContainer)
        {
            if (element.Spacing == AdaptiveSpacing.None && !element.Separator)
            {
                return null;
            }

            var uiSep = new Grid();
            uiSep.Style = context.GetStyle($"Adaptive.Separator");
            int spacing = context.Config.GetSpacing(element.Spacing);

            SeparatorConfig sepStyle = context.Config.Separator;

            var margin = (spacing - sepStyle.LineThickness) / 2;
            uiSep.Margin = new Thickness(0, margin, 0, margin);
            uiSep.SetHeight(sepStyle.LineThickness);
            if (!string.IsNullOrWhiteSpace(sepStyle.LineColor))
            {
                uiSep.SetBackgroundColor(sepStyle.LineColor, context);
            }
            uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            Grid.SetRow(uiSep, uiContainer.RowDefinitions.Count - 1);
            uiContainer.Children.Add(uiSep);

            return uiSep;
        }

        private static Thickness GetBleedMargin(AdaptiveRenderArgs parentRenderArgs, int padding)
        {
            Thickness bleedMargin = new Thickness(0);

            if ((parentRenderArgs.BleedDirection & BleedDirection.BleedLeft) != BleedDirection.BleedNone)
            {
                bleedMargin.Left = padding;
            }

            if ((parentRenderArgs.BleedDirection & BleedDirection.BleedRight) != BleedDirection.BleedNone)
            {
                bleedMargin.Right = padding;
            }

            if ((parentRenderArgs.BleedDirection & BleedDirection.BleedUp) != BleedDirection.BleedNone)
            {
                bleedMargin.Top = padding;
            }

            if ((parentRenderArgs.BleedDirection & BleedDirection.BleedDown) != BleedDirection.BleedNone)
            {
                bleedMargin.Bottom = padding;
            }

            return bleedMargin;
        }

        // For applying bleeding, we must know if the element has padding, so both properties are applied in the same method
        public static bool ApplyPadding(Border border, Grid uiElement, AdaptiveCollectionElement element, AdaptiveRenderArgs parentRenderArgs, AdaptiveRenderContext context)
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

            int padding = context.Config.Spacing.Padding;

            if (canApplyPadding)
            {
                uiElement.Margin = new Thickness(padding);

                if (element.Bleed)
                {
                    border.Margin = GetBleedMargin(parentRenderArgs, -padding);
                }
            }

            return canApplyPadding;
        }

        /// <summary>
        /// Encloses the element in a panel to ease the showing/hiding of elements
        /// </summary>
        /// <param name="renderedElement">UIElement</param>
        /// <returns>Panel that encloses the element</returns>
        public static FrameworkElement EncloseElementInPanel(AdaptiveRenderContext context, AdaptiveTypedElement element, FrameworkElement renderedElement)
        {
            FrameworkElement enclosingElement = renderedElement;

            if (element is AdaptiveInput)
            {
                AdaptiveInput inputElement = element as AdaptiveInput;
                enclosingElement = EncloseInputForVisualCue(context, inputElement, renderedElement);

                FrameworkElement elementForAccessibility = renderedElement;

                if (inputElement is AdaptiveChoiceSetInput)
                {
                    if (renderedElement is Grid)
                    {
                        Grid inputContainer = renderedElement as Grid;
                        // ChoiceSet inputs render by returning a Grid. The grid may contain a combobox or a panel that contains the options
                        UIElement choiceSet = inputContainer.Children[0];

                        if (choiceSet is ComboBox)
                        {
                            elementForAccessibility = choiceSet as FrameworkElement;
                        }
                        else if (choiceSet is Panel)
                        {
                            // If it's a choice set, then use the first element as element
                            elementForAccessibility = ((choiceSet as Panel).Children[0] as FrameworkElement) ?? renderedElement;
                        }
                    }
                }

                AutomationProperties.SetIsRequiredForForm(GetVisualElementForAccessibility(context, inputElement), inputElement.IsRequired);

                if ((!String.IsNullOrEmpty(inputElement.Label)) || (!String.IsNullOrEmpty(inputElement.ErrorMessage)))
                {
                    TagContent tag = renderedElement.Tag as TagContent;

                    StackPanel panel = new StackPanel();

                    if (!String.IsNullOrEmpty(inputElement.Label))
                    {
                        panel.Children.Add(RenderLabel(context, inputElement, elementForAccessibility));
                        AddSpacing(context, context.Config.Inputs.Label.InputSpacing, panel);
                    }

                    panel.Children.Add(enclosingElement);
                    enclosingElement = panel;
                    tag.EnclosingElement = panel;

                    if (!String.IsNullOrEmpty(inputElement.ErrorMessage))
                    {
                        Grid errorMessageSpacing = AddSpacing(context, context.Config.Inputs.ErrorMessage.Spacing, panel);

                        TextBlock renderedErrorMessage = RenderErrorMessage(context, inputElement);
                        renderedErrorMessage.Tag = new TagContent(errorMessageSpacing, null);

                        context.InputValues[inputElement.Id].ErrorMessage = renderedErrorMessage;

                        panel.Children.Add(renderedErrorMessage);
                        tag.ErrorMessage = renderedErrorMessage;

                        RendererUtil.SetVisibility(renderedErrorMessage, false, renderedErrorMessage.Tag as TagContent);
                    }
                }
            }

            return enclosingElement;
        }

        /// <summary>
        /// Encloses the element in a panel to ease the showing/hiding of elements
        /// </summary>
        /// <param name="renderedElement">UIElement</param>
        /// <returns>Border that encloses the element or the element if not needed</returns>
        public static FrameworkElement EncloseInputForVisualCue(AdaptiveRenderContext context, AdaptiveInput element, FrameworkElement renderedElement)
        {
            FrameworkElement enclosingElement = renderedElement;

            if (!(element is AdaptiveChoiceSetInput) && !(element is AdaptiveToggleInput))
            {
                AdaptiveTextBoxInputValue inputValue = context.InputValues[element.Id] as AdaptiveTextBoxInputValue;

                if (inputValue != null)
                {
                    Border visualCue = new Border();
                    visualCue.Child = renderedElement;
                    visualCue.BorderBrush = context.GetColorBrush(context.GetForegroundColors(AdaptiveTextColor.Attention).Default);

                    inputValue.VisualErrorCue = visualCue;
                    enclosingElement = visualCue;
                }
            }

            return enclosingElement;
        }

        /// <summary>
        /// Renders the label for an input element
        /// </summary>
        /// <param name="context">AdaptiveRenderContext</param>
        /// <param name="input">AdaptiveInput</param>
        /// <returns>The rendered label</returns>
        public static FrameworkElement RenderLabel(AdaptiveRenderContext context, AdaptiveInput input, FrameworkElement renderedInput)
        {
            TextBlock uiTextBlock = new TextBlock { TextWrapping = TextWrapping.Wrap };

            InputLabelConfig labelConfig = null;
            if (input.IsRequired)
            {
                labelConfig = context.Config.Inputs.Label.RequiredInputs;
            }
            else
            {
                labelConfig = context.Config.Inputs.Label.OptionalInputs;
            }

            Inline labelTextInline = new Run(input.Label);
            labelTextInline.SetColor(AdaptiveTextColor.Default, labelConfig.IsSubtle, context);
            uiTextBlock.Inlines.Add(labelTextInline);

            if (input.IsRequired)
            {
                string hintToRender = " *";
                if (String.IsNullOrWhiteSpace(labelConfig.Suffix))
                {
                    hintToRender = labelConfig.Suffix;
                }

                Inline requiredHintInline = new Run(hintToRender);
                requiredHintInline.SetColor(AdaptiveTextColor.Attention, labelConfig.IsSubtle, context);
                uiTextBlock.Inlines.Add(requiredHintInline);
            }

            uiTextBlock.FontWeight = FontWeight.FromOpenTypeWeight(context.Config.GetFontWeight(AdaptiveFontType.Default, labelConfig.Weight));
            uiTextBlock.FontSize = context.Config.GetFontSize(AdaptiveFontType.Default, labelConfig.Size);

            if (labelConfig.Color != AdaptiveTextColor.Default)
            {
                uiTextBlock.SetColor(labelConfig.Color, labelConfig.IsSubtle, context);
            }

            // For Input.Text we render inline actions inside of a Grid, so we set the property
            AutomationProperties.SetLabeledBy(GetVisualElementForAccessibility(context, input), uiTextBlock);

            return uiTextBlock;
        }

        /// <summary>
        /// Renders the error message for an input element
        /// </summary>
        /// <param name="context">AdaptiveRenderContext</param>
        /// <param name="input">AdaptiveInput</param>
        /// <returns>The rendered error message</returns>
        public static TextBlock RenderErrorMessage(AdaptiveRenderContext context, AdaptiveInput input)
        {
            TextBlock uiTextBlock = new TextBlock() {
                Text = input.ErrorMessage,
                TextWrapping = TextWrapping.Wrap,
                Visibility = Visibility.Collapsed
            };

            // By default the color is set to attention
            uiTextBlock.SetColor(AdaptiveTextColor.Attention, false /* isSubtle */, context);

            // Then we honour size and weight from hostconfig
            uiTextBlock.FontWeight = FontWeight.FromOpenTypeWeight(context.Config.GetFontWeight(AdaptiveFontType.Default, context.Config.Inputs.ErrorMessage.Weight));
            uiTextBlock.FontSize = context.Config.GetFontSize(AdaptiveFontType.Default, context.Config.Inputs.ErrorMessage.Size);

            return uiTextBlock;
        }

        public static UIElement GetVisualElementForAccessibility(AdaptiveRenderContext context, AdaptiveInput input)
        {
            return context.InputValues[input.Id].VisualElementForAccessibility;
        }
    }
}
